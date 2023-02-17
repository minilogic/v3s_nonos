#include <string.h>
#include <malloc.h>
#include "sys.h"

struct LAY layer[4];
struct DISP *display;

struct DISP TFT_800x480 = { 800, 480, 2, 23, 4, 46, 0x81004107, 5, 0, 2 }; // 198 / 6 = 33.0MHz
//struct DISP TFT_800x480 = { 800, 480, 3, 45, 48, 152, 0x81004107, 8, 0 }; // 198 / 8 = 33MHz

int disp_init (struct DISP *cfg, u32 bg)
{
	u32 size = (((cfg->height - 1) << 16) | (cfg->width - 1));
  if(cfg == NULL) return KO;
  display = cfg;
  for(CCU->PLL_VIDEO_CTRL = cfg->pll; !(CCU->PLL_VIDEO_CTRL & (1 << 28));) {};
  CCU->DE_CLK = 1UL << 31;
  CCU->TCON_CLK = 1UL << 31;
  CCU->BUS_CLK_GATING1 |= (1 << 12) | (1 << 4);
  CCU->BUS_SOFT_RST1 &= ~((1 << 12) | (1 << 4));
  CCU->BUS_SOFT_RST1 |= (1 << 12) | (1 << 4);
  PE->CFG0 = 0x33333333;  // PD0..PD7: LCD D2..D7, D10, D11
  PE->CFG1 = 0x33333333;  // PD8..PD15: LCD D12..D15, D18..D21
  PE->CFG2 = 0x30003333;  // PD16..PD21: LCD D22..D23, CLK, DE, HS, VS
  PE->CFG3 = 0x00000003;  // PD16..PD21: LCD D22..D23, CLK, DE, HS, VS
  PE->DRV0 = 0xFFFFFFFF;  // Drive strong (level 3)
  PE->DRV1 = 0x00000FFF;
  PE->PUL0 = 0;           // Pull-up/down disable
  PE->PUL1 = 0;
  TCON->CTRL = 0;
  TCON->INT0 = 0;
  TCON->T0_CLK &= 0x0FFFFFFF;
  TCON->T0_IO_CTRL[1] = 0xFFFFFFFF;
  TCON->T1_IO_CTRL[1] = 0xFFFFFFFF;
  DE_CTRL->RST_CFG |= 1;
  DE_CTRL->GATE_CFG |= 1;
  DE_CTRL->BUS_CFG |= 1;
  DE_CTRL->SEL_CFG &= ~1;
  DE_GLB->CTRL = 1;
  DE_GLB->STAT = 0;
  DE_GLB->DBUF = 0;//1;
  DE_GLB->SIZE = size;
  memset(DE_OVL_V, 0, sizeof(DE_OVL_V_T));
  memset(DE_OVL_UI0, 0, sizeof(DE_OVL_UI_T));
  memset(DE_OVL_UI1, 0, sizeof(DE_OVL_UI_T));
  memset(DE_OVL_UI2, 0, sizeof(DE_OVL_UI_T));
  memset(DE_BLD, 0, sizeof(DE_BLD_T));
  DE_BLD->FCOL_CTRL = 0x101;
  DE_BLD->ROUTE = 2;
  DE_BLD->PREMULT = 0;
  DE_BLD->BCOL = bg;//0xFF000000;
  DE_BLD->MODE[0] = 0x03010301;
  DE_BLD->MODE[1] = 0x03010301;
  DE_BLD->OUTSIZE = size;
  DE_BLD->OUTCTRL = 0;
  DE_BLD->KEY_CTRL = 0;
  for(int i = 0; i < 4; i++)
  {
    DE_BLD->ATTR[i].FCOL = 0xFF000000;
    DE_BLD->ATTR[i].INSIZE = size;
  }
  V3S_DE_MUX_VSU  = 0;
  V3S_DE_MUX_GSU1 = 0;
  V3S_DE_MUX_GSU2 = 0;
  V3S_DE_MUX_GSU3 = 0;
  V3S_DE_MUX_FCE  = 0;
  V3S_DE_MUX_BWS  = 0;
  V3S_DE_MUX_LTI  = 0;
  V3S_DE_MUX_PEAK = 0;
  V3S_DE_MUX_ASE  = 0;
  V3S_DE_MUX_FCC  = 0;
  V3S_DE_MUX_DCSC = 0;
  TCON->T0_CTRL = (1UL << 31) | (1UL << 21) | ((cfg->vbp + cfg->vsp) << 4);
  TCON->T0_CLK = (1UL << 28) | cfg->div;
  TCON->T0_TIMING[0] = ((cfg->width - 1) << 16) | (cfg->height - 1);
  TCON->T0_TIMING[1] = ((cfg->width + cfg->hbp + cfg->hsp - 1) << 16) | (cfg->hbp - 1); // ??????
  TCON->T0_TIMING[2] = ((cfg->height + cfg->vbp + cfg->vsp) << 17) | (cfg->vbp - 1);
  TCON->T0_TIMING[3] = ((cfg->hsp - 1) << 16) | (cfg->vsp - 1);
  TCON->T0_HV_TIMING = 0;
  TCON->T0_CPU_IF = 0;
  TCON->T0_IO_CTRL[0] = cfg->inv << 24;
  TCON->T0_IO_CTRL[1] = 0;
  TCON->CTRL = 0x80000000;
  while(TCON->T0_CTRL & (1 << 21));
  return OK;
}

u8 disp_backlight (u8 x)
{
  PB->CFG0 = 0x77717777;
  PB->DAT = 0b10000;
  return x;
}

void lay_config (int i, int width, int height, int posx, int posy, int stride,
                void *addr, int attr0, int attr1)
{
  layer[i].width = width;
  layer[i].height = height;
  layer[i].posx = posx;
  layer[i].posy = posy;
  layer[i].stride = width * stride;
  layer[i].addr = addr;
  layer[i].attr0 = attr0;
  layer[i].attr1 = attr1;
}

void lay_update (int i)
{
	u32 size = (((layer[i].height - 1) << 16) | (layer[i].width - 1));
  DE_OVL_UI0->CFG[0].ATTR = (1 << 0) | (10 << 8);
  DE_OVL_UI0->CFG[0].SIZE = size;
  DE_OVL_UI0->CFG[0].COORD = 0;
  DE_OVL_UI0->CFG[0].PITCH = 2 * layer[i].width;
  DE_OVL_UI0->CFG[0].TOP_LADDR = (u32)layer[i].addr;
  DE_OVL_UI0->OVL_SIZE = size;
  DE_OVL_UI1->CFG[0].ATTR = (1 << 0) | (10 << 8);
  DE_OVL_UI1->CFG[0].SIZE = size;
  DE_OVL_UI1->CFG[0].COORD = 0;
  DE_OVL_UI1->CFG[0].PITCH = 2 * layer[i].width;
  DE_OVL_UI1->CFG[0].TOP_LADDR = (u32)layer[i].addr;
  DE_OVL_UI1->OVL_SIZE = size;
  DE_GLB->CTRL = 1;
  DE_GLB->STAT = 0;
  DE_GLB->DBUF = 1;
  DE_GLB->SIZE = size;
}

void *fb_alloc (int width, int height, int stride)
{
  int size = width * height * stride / 8;
  void *ptr = memalign(4096, size);
  if(ptr) memset(ptr, 0, size);
  return ptr;
}
