#ifndef __V3S_H__
#define __V3S_H__

#include <stdint.h>

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s8  int8_t
#define s16 int16_t
#define s32 int32_t

#define __I volatile const
#define __O volatile
#define __IO volatile

#define OK 0
#define KO ~OK

#define PACKED __attribute__ ((packed))

/* CCU */
typedef struct {
  __IO  u32 PLL_CPU_CTRL;     // 0x00 PLL_CPU Control Register
  __IO  u32 RES0;
  __IO  u32 PLL_AUDIO_CTRL;   // 0x08 PLL_AUDIO Control Register
  __IO  u32 RES1;
  __IO  u32 PLL_VIDEO_CTRL;   // 0x10 PLL_VIDEO Control Register
  __IO  u32 RES2;
  __IO  u32 PLL_VE_CTRL;      // 0x18 PLL_VE Control Register
  __IO  u32 RES3;
  __IO  u32 PLL_DDR0_CTRL;    // 0x20 PLL_DDR Control Register
  __IO  u32 RES4;
  __IO  u32 PLL_PERIPH0_CTRL; // 0x28 PLL_PERIPH0 Control Register
  __IO  u32 RES5[9];

  __IO  u32 CPU_AXI_CFG;      // 0x50 CPU Clock Source Register
  __IO  u32 AHB1_APB1_CFG;    // 0x54 AHB/APB/HCLKC Configuration Register
  __IO  u32 APB2_CFG;         // 0x58
  __IO  u32 AHB2_CFG;         // 0x5C

  __IO  u32 BUS_CLK_GATING0;    // 0x60 Bus Clock Gating Register 0
  __IO  u32 BUS_CLK_GATING1;    // 0x64 Bus Clock Gating Register 0
  __IO  u32 BUS_CLK_GATING2;    // 0x68 Bus Clock Gating Register 0
  __IO  u32 BUS_CLK_GATING3;    // 0x6C Bus Clock Gating Register 0
  __IO  u32 BUS_CLK_GATING4;    // 0x70 Bus Clock Gating Register 0

  __IO  u32 RES7[5];
  __IO  u32 SDMMC0_CLK;       // 0x88 SDMMC0 Clock Register
  __IO  u32 SDMMC1_CLK;       // 0x8C SDMMC0 Clock Register
  __IO  u32 RES8[4];
  __IO  u32 SPI0_CLK;           // 0xA0
  __IO  u32 RES8_[3];


  __IO  u32 DAUDIO_CLK;       // 0xB0 DAUDIO Clock Register
  __IO  u32 OWA_CLK;          // 0xB4 OWA Clock Register
  __IO  u32 CIR_CLK;          // 0xB8 CIR Clock Register
  __IO  u32 RES9[4];
  __IO  u32 USBPHY_CFG;       // 0xCC USBPHY Clock Register
  __IO  u32 RES10[12];
  __IO  u32 DRAM_GATING;      // 0x100 DRAM GATING Register
  __IO  u32 DE_CLK;           // 0x104 BE Clock Register
  __IO  u32 RES12[4];
  __IO  u32 TCON_CLK;         // 0x118 TCON Clock Register
  __IO  u32 DI_CLK;           // 0x11C De-interlacer Clock Register
  __IO  u32 TVE_CLK;          // 0x120 TVE Clock Register
  __IO  u32 TVD_CLK;          // 0x124 TVD Clock Register
  __IO  u32 RES13[3];
  __IO  u32 CSI_CLK;          // 0x134 CSI Clock Register
  __IO  u32 RES14;
  __IO  u32 VE_CLK;           // 0x13C VE Clock Register
  __IO  u32 AC_DIG_CLK;       // 0x140 Audio Codec Clock Register
  __IO  u32 AVS_CLK;          // 0x144 AVS Clock Register

  __IO  u32 RES15[5];

  __IO  u32 MBUS_CLK;         // 0x15C
  __IO  u32 RES15_[40];


  __IO  u32 PLL_STABLE0;    // 0x200 PLL stable time 0
  __IO  u32 PLL_STABLE1;    // 0x204 PLL stable time 1
  __IO  u32 RES16[6];
  __IO  u32 PLL_CPU_BIAS;   // 0x220 PLL CPU Bias Register
  __IO  u32 PLL_AUDIO_BIAS; // 0x224 PLL Audio Bias Register
  __IO  u32 PLL_VIDEO_BIAS; // 0x228 PLL Video Bias Register
  __IO  u32 PLL_VE_BIAS;    // 0x22c PLL VE Bias Register
  __IO  u32 PLL_DDR_BIAS;   // 0x230 PLL DDR Bias Register
  __IO  u32 PLL_PERIPH_BIAS;// 0x234 PLL PERIPH Bias Register
  __IO  u32 RES17[6];
  __IO  u32 PLL_CPU_TUNING; // 0x250 PLL CPU Tuning Register
  __IO  u32 RES18[3];
  __IO  u32 PLL_DDR_TUNING; // 0x260 PLL DDR Tuning Register
  __IO  u32 RES19[8];
  __IO  u32 PLL_AUDIO_PAT;  // 0x284 PLL Audio Pattern Control Register
  __IO  u32 PLL_VIDEO_PAT;  // 0x288 PLL Video Pattern Control Register
  __IO  u32 RES20;
  __IO  u32 PLL_DDR_PAT;    // 0x290 PLL DDR Pattern Control Register
  __IO  u32 RES21[11];
  __IO  u32 BUS_SOFT_RST0;  // 0x2C0 Bus Software Reset Register 0
  __IO  u32 BUS_SOFT_RST1;  // 0x2C4 Bus Software Reset Register 1
  __IO  u32 BUS_SOFT_RST2;  // 0x2C8 Bus Software Reset Register 1
  __IO  u32 RES22;
  __IO  u32 BUS_SOFT_RST3;  // 0x2D0 Bus Software Reset Register 2
  __IO  u32 RES23;
  __IO  u32 BUS_SOFT_RST4;  // 0x2D8 Bus Software Reset Register 2

} CCU_T;
#define CCU ((CCU_T*)0x01C20000)

/* PIO */
typedef struct {
  __IO  u32 CFG0;           // 0x00 Configure Register 0
  __IO  u32 CFG1;           // 0x04 Configure Register 1
  __IO  u32 CFG2;           // 0x08 Configure Register 2
  __IO  u32 CFG3;           // 0x0C Configure Register 3
  __IO  u32 DAT;            // 0x10 Data Register
  __IO  u32 DRV0;           // 0x14 Multi-Driving Register 0
  __IO  u32 DRV1;           // 0x18 Multi-Driving Register 1
  __IO  u32 PUL0;           // 0x1C Pull Register 0
  __IO  u32 PUL1;           // 0x20 Pull Register 1
} PIO_T;
#define PB  ((PIO_T*)0x01C20824)
#define PC  ((PIO_T*)0x01C20848)
#define PE  ((PIO_T*)0x01C20890)
#define PF  ((PIO_T*)0x01C208B4)
#define PG  ((PIO_T*)0x01C208D8)

/* TCON */
typedef struct {
  __IO  u32 CTRL;           // 0x00 TCON Control
  __IO  u32 INT0;           // 0x04 Interrupt_0
  __IO  u32 INT1;           // 0x08 Interrupt_1
  __IO  u32 RES0;
  __IO  u32 FRM_CTRL;       // 0x10 FRM Control
  __IO  u32 FRM_SEED[6];    // 0x14..0x28 TCON FRM Seed0 RGB, Seed1 RGB
  __IO  u32 FRM_TBL[4];     // 0x2C..0x38 TCON FRM Table 0..3
  __IO  u32 RES1;
  __IO  u32 T0_CTRL;        // 0x40 TCON0 Control
  __IO  u32 T0_CLK;         // 0x44 TCON0 Clock Control
  __IO  u32 T0_TIMING[4];   // 0x48..0x54 TCON0 Basic Timing 0..3
  __IO  u32 T0_HV_TIMING;   // 0x58 TCON0 HV Timing
  __IO  u32 RES2;
  __IO  u32 T0_CPU_IF;      // 0x60 TCON0 CPU Interface Control
  __IO  u32 T0_CPU_WR;      // 0x64 TCON0 CPU Write Data
  __IO  u32 T0_CPU_RD;      // 0x68 TCON0 CPU Read Data
  __IO  u32 T0_CPU_RDNX;    // 0x6C TCON0 CPU Read Back Data
  __IO  u32 T0_TTL_TIMING[5]; // 0x70..0x80 TCON0 TTL Timing
  __IO  u32 T0_LVDS_IF;       // 0x84
  __IO  u32 T0_IO_CTRL[2];  // 0x88..0x8C TCON0 IO Control 0..1

  __IO  u32 T1_CTRL;        // 0x90 TCON1 Control
  __IO  u32 T1_TIMING[6];   // 0x94..0xA8 TCON1 Basic Timing 0..5
  __IO  u32 RES4[17];
  __IO  u32 T1_IO_CTRL[2];  // 0xF0..0xF4 TCON1 IO Control 0..1
//  __IO  u32 RES5;
//  __IO  u32 DBG_INFO;       // 0xFC TCON Debug Information
//	u8_t res4[0x108];			/* 0xf8 */
//	u32_t mux_ctrl;				/* 0x200 */
//	u8_t res5[0x1c];			/* 0x204 */
//	u32_t lvds_ana0;			/* 0x220 */
//	u32_t lvds_ana1;			/* 0x224 */
} TCON_T;
#define TCON ((TCON_T*)0x01C0C000)

/* DE */
typedef struct {
  __IO  u32 GATE_CFG;
  __IO  u32 BUS_CFG;
  __IO  u32 RST_CFG;
  __IO  u32 DIV_CFG;
  __IO  u32 SEL_CFG;
} DE_CTRL_T;
#define DE_CTRL ((DE_CTRL_T*)0x01000000)

typedef struct {
  __IO  u32 CTRL;
  __IO  u32 STAT;
  __IO  u32 DBUF;
  __IO  u32 SIZE;
} DE_GLB_T;
#define DE_GLB ((DE_GLB_T*)0x01100000)

typedef struct {
  __IO  u32 FCOL_CTRL;
  struct {
    __IO  u32 FCOL;
    __IO  u32 INSIZE;
    __IO  u32 OFFSET;
    __IO  u32 DUM;
  } ATTR[4];
  __IO  u32 DUM0[15];
  __IO  u32 ROUTE;
  __IO  u32 PREMULT;
  __IO  u32 BCOL;
  __IO  u32 OUTSIZE;
  __IO  u32 MODE[4];
  __IO  u32 DUM1[4];
  __IO  u32 KEY_CTRL;
  __IO  u32 KEY_CFG;
  __IO  u32 DUM2[2];
  __IO  u32 KEY_MAX[4];
  __IO  u32 DUM3[4];
  __IO  u32 KEY_MIN[4];
  __IO  u32 DUM4[3];
  __IO  u32 OUTCTRL;
} DE_BLD_T;
#define DE_BLD ((DE_BLD_T*)0x01101000)

typedef struct {
  struct {
    __IO  u32 ATTR;
    __IO  u32 SIZE;
    __IO  u32 COORD;
    __IO  u32 PITCH[3];
    __IO  u32 TOP_LADDR[3];
    __IO  u32 BOT_LADDR[3];
  } CFG[4];
  __IO  u32 FCOL[4];
  __IO  u32 TOP_HADDR[3];
  __IO  u32 BOT_HADDR[3];
  __IO  u32 OVL_SIZE[2];
  __IO  u32 HORI[2];
  __IO  u32 VERT[2];
} DE_OVL_V_T;
#define DE_OVL_V ((DE_OVL_V_T*)0x01102000)

typedef struct {
  struct {
    __IO  u32 ATTR;
    __IO  u32 SIZE;
    __IO  u32 COORD;
    __IO  u32 PITCH;
    __IO  u32 TOP_LADDR;
    __IO  u32 BOT_LADDR;
    __IO  u32 FCOL;
    __IO  u32 DUM;
  } CFG[4];
  __IO  u32 TOP_HADDR;
  __IO  u32 BOT_HADDR;
  __IO  u32 OVL_SIZE;
} DE_OVL_UI_T;
#define DE_OVL_UI0 ((DE_OVL_UI_T*)0x01103000)
#define DE_OVL_UI1 ((DE_OVL_UI_T*)0x01104000)
#define DE_OVL_UI2 ((DE_OVL_UI_T*)0x01105000)

#define V3S_DE_MUX_VSU  (*(__IO u32*)0x01120000)
#define V3S_DE_MUX_GSU1 (*(__IO u32*)0x01130000)
#define V3S_DE_MUX_GSU2 (*(__IO u32*)0x01140000)
#define V3S_DE_MUX_GSU3 (*(__IO u32*)0x01150000)
#define V3S_DE_MUX_FCE  (*(__IO u32*)0x011A0000)
#define V3S_DE_MUX_BWS  (*(__IO u32*)0x011A2000)
#define V3S_DE_MUX_LTI  (*(__IO u32*)0x011A4000)
#define V3S_DE_MUX_PEAK (*(__IO u32*)0x011A6000)
#define V3S_DE_MUX_ASE  (*(__IO u32*)0x011A8000)
#define V3S_DE_MUX_FCC  (*(__IO u32*)0x011AA000)
#define V3S_DE_MUX_DCSC (*(__IO u32*)0x011B0000)

/* UART */
typedef struct {
  union {
  __I   u32 RBR;            // 0x00 Receive Buffer Register
  __O   u32 THR;            // 0x00 Transmit Holding Register
  __IO  u32 DLL;            // 0x00 Divisor Latch Low Register
  };
  union {
  __IO  u32 IER;            // 0x04 Interrupt Enable Register
  __IO  u32 DLH;            // 0x04 Divisor Latch High Register
  };
  union {
  __I   u32 IIR;            // 0x08 Interrupt Identify Register
  __O   u32 FCR;            // 0x08 FIFO Control Register
  };
  __IO  u32 LCR;            // 0x0C Line Control Register
  __IO  u32 MCR;            // 0x10 Modem Control Register
  __I   u32 LSR;            // 0x14 Line Status Register
  __I   u32 MSR;            // 0x18 Modem Status Register
  __I   u32 SCH;            // 0x1C Scratch Register
  __I   u32 RES1[23];
  __I   u32 USR;            // 0x7C Status register
  __I   u32 TFL;            // 0x80 Transmit FIFO Level Register
  __I   u32 RFL;            // 0x84 Receive FIFO Level Register
  __I   u32 RES2[7];
  __I   u32 HALT;           // 0xA4 Halt TX Register
} UART_T;
#define UART0 ((UART_T*)0x01C28000)
#define UART1 ((UART_T*)0x01C28400)
#define UART2 ((UART_T*)0x01C28800)

/* SPI */
typedef struct {
  __I   u32 RES1;           // 0x000
  __IO  u32 GC;             // 0x004 Global Control Register
  __IO  u32 TC;             // 0x008 Transfer Control Register
  __I   u32 RES2;           // 0x00C
  __IO  u32 IE;             // 0x010 Interrupt Control Register
  __IO  u32 IS;             // 0x014 Interrupt Status Register
  __IO  u32 FC;             // 0x018 FIFO Control Register
  __IO  u32 FS;             // 0x01C FIFO Status Register
  __IO  u32 WC;             // 0x020 Wait Clock Counter Register
  __IO  u32 CC;             // 0x024 Clock Rate Control Register
  __I   u32 RES3[2];        // 0x028..0x2C
  __IO  u32 MBC;            // 0x030 Burst Counter Register
  __IO  u32 MTC;            // 0x034 Transmit Counter Register
  __IO  u32 BCC;            // 0x038 Burst Control Register
  __I   u32 RES4[113];
  union {                   // 0x200 TX Data Register
    __O u8  byte;
    __O u32 word;
  } TX;
  __I   u32 RES5[63];
  union {                   // 0x300 RX Data Register
    __I u8  byte;
    __I u16 sword;
    __I u32 word;
  } RX;
} SPI_T;
#define SPI0 ((SPI_T*)0x01C68000)

/* TIMER */
typedef struct {
  __IO  u32 IE;             // 0x00 IRQ Enable Register
  __IO  u32 IS;             // 0x04 IRQ Status Register
  __IO  u32 RES0[2];
  __IO  u32 T0_CTRL;        // 0x10 Timer 0 Control Register
  __IO  u32 T0_INTV;        // 0x14 Timer 0 Interval Value Register
  __IO  u32 T0_CURV;        // 0x18 Timer 0 Current Value Register
  __IO  u32 RES1;
  __IO  u32 T1_CTRL;        // 0x20 Timer 1 Control Register
  __IO  u32 T1_INTV;        // 0x24 Timer 1 Interval Value Register
  __IO  u32 T1_CURV;        // 0x28 Timer 1 Current Value Register
  __IO  u32 RES2;
  __IO  u32 T2_CTRL;        // 0x30 Timer 2 Control Register
  __IO  u32 T2_INTV;        // 0x34 Timer 2 Interval Value Register
  __IO  u32 T2_CURV;        // 0x38 Timer 2 Current Value Register
  __IO  u32 RES3[17];
  __IO  u32 AVS_CTRL;       // 0x80 AVS Control Register
  __IO  u32 AVS_CNT0;       // 0x84 AVS Counter 0 Register
  __IO  u32 AVS_CNT1;       // 0x88 AVS Counter 1 Register
  __IO  u32 AVS_DIV;        // 0x8C AVS Divisor Register
  __IO  u32 RES4[4];
  __IO  u32 WDOG_IE;        // 0xA0 Watchdog IRQ Enable Register
  __IO  u32 WDOG_IS;        // 0xA4 Watchdog IRQ Status Register
  __IO  u32 RES5[2];
  __IO  u32 WDOG_CTRL;      // 0xB0 Watchdog 0 Control Register
  __IO  u32 WDOG_CFG;       // 0xB4 Watchdog 0 Configuration Register
  __IO  u32 WDOG_MODE;      // 0xB8 Watchdog 0 Mode Register
  __IO  u32 RES6;
  __IO  u32 CNT64_TEST;     // 0xD0 64-bit Counter Test Mode
  __IO  u32 CNT64_CTRL;     // 0xD4 64-bit Counter Test Mode
  __IO  u32 CNT64_LOW;      // 0xD8 64-bit Counter Test Mode
  __IO  u32 CNT64_HIGH;     // 0xDC 64-bit Counter Test Mode
} TIM_T;
#define TIM ((TIM_T*)0x01C20C00)

#endif