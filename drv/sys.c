#include <stdio.h>
#include "sys.h"

void __attribute__((section(".vectors"))) __attribute__((naked)) _vectors (void)
{
  __asm__ __volatile__ (
    /* System vectors */
    "b      _reset\n"                 // Reset
    "ldr    pc, addr_undef\n"         // Undefined instruction
    "ldr    pc, addr_swi\n"           // Software interrupt
    "ldr    pc, addr_pabt\n"          // Prefetch abort
    "ldr    pc, addr_dabt\n"          // Data abort
    ".word  image_size\n"             // Reserved
    "ldr    pc, addr_irq\n"           // Interrupt
    "ldr    pc, addr_fiq\n"           // Fast interrupt
    "addr_undef:.word err_handler\n"
    "addr_swi:  .word swi_handler\n"
    "addr_pabt: .word err_handler\n"
    "addr_dabt: .word err_handler\n"
    "addr_irq:  .word err_handler\n"
    "addr_fiq:  .word err_handler\n"
    ".balignl   16,0xdeadbeef\n"
    "_reset:"
    /* Stack initialization */
    "msr    cpsr_c, #0xDB\n"          // Undefined Instruction Mode
    "ldr    sp, =stack_und\n"
    "msr    cpsr_c, #0xD7\n"          // Abort Processing memory Faults Mode
    "ldr    sp, =stack_abt\n"
    "msr    cpsr_c, #0xD2\n"          // IRQ Standard Interrupts Mode
    "ldr    sp, =stack_irq\n"
    "msr    cpsr_c, #0xD1\n"          // FIQ Fast Interrupts Mode
    "ldr    sp, =stack_fiq\n"
    "msr    cpsr_c, #0xDF\n"          // System Running in Priviledged Operating Mode
    "ldr    sp, =stack_usr\n"
    "msr    cpsr_c, #0xD3\n"          // Supervisor Interrupts Mode (SVC)
    "ldr    sp, =stack_srv\n"
    /* Set vector base address register */
    "ldr     r0, =_vectors\n"
    "mcr     p15, 0, r0, c12, c0, 0\n"
    "mrc     p15, 0, r0, c1, c0, 0\n"
    "bic     r0, #(1 << 13)\n"
    "mcr     p15, 0, r0, c1, c0, 0\n"
    /* Clear bss section */
    "mov     r0, #0\n"
    "ldr     r1, =bss_start\n"
    "ldr     r2, =bss_end\n"
    "bss_clr:cmp     r1, r2\n"
    "strlo   r0, [r1], #4\n"
    "blo     bss_clr\n"
     /* SOC init & jump to main */
    "bl      sys_init\n"
    "ldr     pc, addr_main\n"
    "addr_main:  .word  main\n"
    "b       .\n"
   );
}

/******************************************************************************/
/*                                 Exceptions                                 */
/******************************************************************************/
void __attribute__((interrupt)) err_handler (void)
{
  while(1);
}

#ifndef _SWI_
void __attribute__((interrupt("SWI"))) swi_handler (void)
{
}
#endif

#ifndef _IRQ_
void __attribute__((interrupt("IRQ"))) irq_handler (void)
{
}
#endif

/******************************************************************************/
/*                                 Retargets                                  */
/******************************************************************************/
void uart_putc (char c)
{
  if(c == '\n') uart_putc('\r');
  while((UART0->LSR & 64) == 0);
  UART0->THR = c;
}

int kbhit(void)
{
  return UART0->LSR & 1;
}

int _write (int fd, char *ptr, int len)
{
  int i = len;
  while(i--) uart_putc(*ptr++);
  return len;
}

int _read (int fd, char *ptr, int len)
{
  while(!kbhit());
  *ptr = UART0->RBR;
  return 1;
}

void dump (void *ptr, uint16_t len)
{
  u8  *dat = ptr;
  u16 i = 0, j;
  if(len)
  {
    printf(" 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F | 0123456789ABCDEF\n");
    do
    {
      for(j = i; j < len && j < (i + 16); j++)
        printf("%02X ", dat[j]);
      printf("| ");
      for(j = i; j < len && j < (i + 16); j++)
        printf("%c", dat[j] < 32 ? '.' : dat[j]);
      printf("\n");
      i = j;
    } while(i < len);
  }
}

/******************************************************************************/
/*                                   System                                   */
/******************************************************************************/
void mmu_setup(void);
void mmu_enable(void);

void sys_init (void)
{
  TIM->WDOG_MODE = 0; // turn off the watchdog
  mmu_setup();
  mmu_enable();
 CCU->USBPHY_CFG &= ~3;
 CCU->BUS_CLK_GATING0 &= ~(1 << 24);
 CCU->BUS_SOFT_RST0 &= ~(1 << 24);
  CCU->AVS_CLK = (1U << 31);
  TIM->AVS_CTRL = 3;
  TIM->AVS_DIV = (11999 << 16) | 11;  // AVS1:1mS, AVS0:1uS
  setbuf(stdout, NULL);
}

void udelay (u32 us) { for(ctr_us = 0; ctr_us < us; ) {}; }

void delay (u32 ms) { udelay(ms * 1000); }
