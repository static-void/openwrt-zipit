/*
 * Copyright 2007-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 */
#ifndef __CF_VIRTCONVERT__
#define __CF_VIRTCONVERT__

/*
 * Macros used for converting between virtual and physical mappings.
 *
 * Coldfire Specific
 */

#ifdef __KERNEL__

#include <linux/compiler.h>
#include <linux/mmzone.h>
#include <asm/setup.h>
#include <asm/page.h>

/*
 * Change virtual addresses to physical addresses and vv.
 */
static inline unsigned long virt_to_phys(void *address)
{
	return __pa(address);
}

static inline void *phys_to_virt(unsigned long address)
{
	return __va(address);
}

/* Permanent address of a page. */
#ifdef CONFIG_SINGLE_MEMORY_CHUNK
#define page_to_phys(page) \
	__pa(PAGE_OFFSET + (((page) - pg_data_map[0].node_mem_map) << PAGE_SHIFT))
#else
#define page_to_phys(_page) ({						\
	struct page *__page = _page;					\
	struct pglist_data *pgdat;					\
	pgdat = pg_data_table[page_to_nid(__page)];			\
	page_to_pfn(__page) << PAGE_SHIFT;				\
})
#endif

/*
 * IO bus memory addresses are 1:1 with the physical address,
 */
#ifdef CONFIG_PCI
#define virt_to_bus(a) (a + PCI_DMA_BASE)
#define bus_to_virt(a) (a - PCI_DMA_BASE)
#else
#define virt_to_bus(a) (a)
#define bus_to_virt(a) (a)
#endif

#endif	/* __KERNEL__ */
#endif	/* __CF_VIRTCONVERT__ */
