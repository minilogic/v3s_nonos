#include "arm32.h"

static inline uint32_t get_cache(void)
{
	uint32_t cache;

	__asm__ __volatile__("mrc p15, 0, %0, c0, c0, 1" : "=r" (cache));
	return cache;
}

static inline void __v5_cache_inv_range(uint32_t start, uint32_t stop, uint32_t line)
{
	uint32_t mva;

	start &= ~(line - 1);
	if(stop & (line - 1))
		stop = (stop + line) & ~(line - 1);
	for(mva = start; mva < stop; mva = mva + line)
	{
		__asm__ __volatile__("mcr p15, 0, %0, c7, c6, 1" : : "r" (mva));
	}
}

/*
 * Invalidate range, affects the range [start, stop - 1]
 */
void cache_inv_range(unsigned long start, unsigned long stop)
{
	uint32_t cache;
	uint32_t line;

	cache = get_cache();
	line = 1 << ((cache & 0x3) + 3);
	__v5_cache_inv_range(start, stop, line);
	//dsb();
  __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10,  4" : : "r" (0) : "memory");
}

#define MB (1U << 20)

enum {
	MAP_TYPE_NCNB	= 0x0,
	MAP_TYPE_NCB	= 0x1,
	MAP_TYPE_CNB	= 0x2,
	MAP_TYPE_CB		= 0x3,
};

static uint32_t __mmu_ttb[4096] __attribute__((aligned(0x4000)));
//uint32_t *__mmu_ttb = (uint32_t*)0;//x4000;

static inline void mmu_ttb_set(uint32_t base)
{
	__asm__ __volatile__("mcr p15, 0, %0, c2, c0, 0" : : "r" (base) : "memory");
}

static inline void mmu_domain_set(uint32_t domain)
{
	__asm__ __volatile__("mcr p15, 0, %0, c3, c0, 0" : : "r" (domain) : "memory");
}

static inline void mmu_inv_tlb(void)
{
	__asm__ __volatile__("mcr p15, 0, %0, c8, c7, 0" : : "r" (0));
	__asm__ __volatile__("mcr p15, 0, %0, c8, c6, 0" : : "r" (0));
	__asm__ __volatile__("mcr p15, 0, %0, c8, c5, 0" : : "r" (0));
	//dsb();
	//isb();
  __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10,  4" : : "r" (0) : "memory");
  __asm__ __volatile__ ("" : : : "memory");
}

static void map_l1_section(uint32_t virt, uint32_t phys, uint32_t size, int type)
{
	uint32_t i;

	virt >>= 20;
	phys >>= 20;
	size >>= 20;
	type &= 0x3;

	for(i = size; i > 0; i--, virt++, phys++)
		__mmu_ttb[virt] = (phys << 20) | (1 << 16) | (0x3 << 10) | (0x0 << 5) | (type << 2) | (0x2 << 0);
}

void mmu_setup(void)
{
	//extern unsigned char __dma_start;
	//extern unsigned char __dma_end;
	map_l1_section(0x00000000, 0x00000000, 2048*MB, 0);//SZ_2G, 0);
	map_l1_section(0x40000000, 0x40000000, 2048*MB, 0);//SZ_2G, 0);
	map_l1_section(0x40000000, 0x40000000, 64*MB, MAP_TYPE_CB);// SZ_32M, MAP_TYPE_CB);
//	map_l1_section(&__dma_start, &__dma_start, &__dma_end - &__dma_start, MAP_TYPE_NCNB);
}

void mmu_enable(void)
{
	mmu_ttb_set((uint32_t)(__mmu_ttb));
	cache_inv_range(0, ~0);
	//outer_cache_enable();
	//outer_cache_inv_range(0, ~0);
	mmu_inv_tlb();
	mmu_domain_set(0x3);
	arm32_mmu_enable();
	arm32_icache_enable();
	arm32_dcache_enable();
}
