#include "v3s.h"
#include "spi.h"

void __attribute__((naked)) _boot (void)
{
  __asm__ __volatile__ (
    /* Loader structure */
    "b      _res\n"                   // [00] jump to reset vector
    ".long  0x4E4F4765\n"             // [04] eGON
    ".long  0x3054422E\n"             // [08] .BT0
    ".long  0x00000000\n"             // [12] checksum for boot0
    ".long  __spl_size\n"             // [16] length for boot0
    ".long  0x024c5053\n"             // [20] SPL
    ".long  0, 0\n"                   // [24], [28]
    ".long  0, 0, 0, 0, 0, 0, 0, 0\n" // [32]..[60]
    ".long  0, 0, 0, 0\n"             // [64]..[76]
    /* Save boot params */
    "_res:  mov r0, #64\n"
    "mrc    p15, 0, r1, c1, c0, 0\n"  // [64] = CP15 SCTLR Register
    "mrc    p15, 0, r2, c1, c0, 0\n"  // [68] = CP15 Control Register
    "stmia  r0, {r1-r2, sp, lr}\n"    // [72] = SP, [76] = LR
    /* Enable SMP mode for dcache, by setting bit 6 of auxiliary ctl reg */
    "mrc p15, 0, r0, c1, c0, 1\n"
    "orr r0, r0, #(1 << 6)\n"
    "mcr p15, 0, r0, c1, c0, 1\n"
    /* Enable neon/vfp unit */
    "mrc p15, 0, r0, c1, c0, 2\n"
    "orr r0, r0, #(0xf << 20)\n"
    "mcr p15, 0, r0, c1, c0, 2\n"
    "isb\n"
    "mov r0, #0x40000000\n"
    "vmsr fpexc, r0\n"
    "bl     boot\n"
    /* Return to FEL */
    "mov    r0, #64\n"
    "ldmia  r0, {r1-r4}\n"
    "mov    lr, r4\n"
    "mov    sp, r3\n"
    "mcr    p15, 0, r2, c1, c0, 0\n"
    "mcr    p15, 0, r1, c1, c0, 0\n"
    "bx     lr\n"
    );
}

static inline void sdelay(int loops)
{
  __asm__ __volatile__ (
    "1:subs %0, %1, #1\n"
    "bne    1b":"=r" (loops):"0"(loops));
}

void put_char (char c)
{
  if(c == '\n') put_char('\r');
  while((UART0->LSR & 64) == 0);
  UART0->THR = c;
}

void put_string (char *ptr)
{
  while(*ptr != 0) put_char(*ptr++);
}

void put_num (unsigned int num)
{
  int i;
  char str[16];
  if(num)
  {
    for(i = 0; num; num /= 10) str[i++] = num % 10 + '0';
    while(i) put_char(str[--i]);
  }
  else put_char('0');
  put_char('\n');
}

void sys_dram_init(void);

void boot (void)
{
  /* System clock initialization */
  CCU->PLL_STABLE0 = 0x1FF;
  CCU->PLL_STABLE1 = 0x1FF;
  CCU->CPU_AXI_CFG = 0x10012;
  sdelay(800);
  for(CCU->PLL_CPU_CTRL = 0x80001410; !(CCU->PLL_CPU_CTRL & (1 << 28));) {}; // CPU:1008MHz
  CCU->CPU_AXI_CFG = 0x20012;
  for(CCU->PLL_PERIPH0_CTRL = 0x80041711; !(CCU->PLL_PERIPH0_CTRL & (1 << 28));) {}; // PERIPH: 576MHz
  CCU->AHB1_APB1_CFG = 0x00003180;  // AHB1=PLL_PERIPH/3=192MHz, APB1=AHB1/2 = 96MHz
  CCU->MBUS_CLK = 0x81000003;
  CCU->DRAM_GATING &= ~(1 << 31);
  /* DDR initialization */
  sys_dram_init();
  /* UART initialization */
  CCU->APB2_CFG = 0x02010002;
  PB->CFG1 = 0x77777733;            // PB8-UART0_TX, PB9-UART0_RX
  CCU->BUS_CLK_GATING3 |= (1 << 16);
  CCU->BUS_SOFT_RST4 |= (1 << 16);
  UART0->THR = 0;
  UART0->FCR = 0xF7;
  UART0->MCR = 0;
  UART0->LCR = 0x83;
  #if 0
  UART0->DLL = 2;                   // 3000000bps @ 576MHz
  #else
  UART0->DLL = 52;                  // 115200bps @ 576MHz
  #endif
  UART0->DLH = 0;
  UART0->LCR = 3;
  /* Firmware loading */
  if(*(unsigned int*)8 != 0x4c45462e)
  {
    /* SPI NOR initialization */
    put_string("\n\n\033[36mSPI-boot\033[0m\nImage size: ");
    spi_init();
    spi_flash_read(32768, (void*)0x40000000, 32);
    put_num(*(int*)0x40000014);
    spi_flash_read(32768 , (void*)0x40000000, *(int*)0x40000014);
    ((void(*)())0x40000000)();
  }
  else put_string("\n\n\033[36mUSB-boot\033[0m\n");
}
