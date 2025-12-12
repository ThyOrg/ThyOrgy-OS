#include "gdt.h"

extern void gdt_flush(uint32_t);

struct gdt_entry gdt_entries[7];
struct gdt_ptr_struct *gdt_ptr = (struct gdt_ptr_struct *)GDT_ADDRESS;

void	fill_gdt(int index, uint32_t base_addr, uint32_t limit, uint8_t access_byte, uint8_t gran)
{
	gdt_entries[index].base_low = base_addr & 0xFFFF;
	gdt_entries[index].base_mid = (base_addr >> 16) & 0xFF;
	gdt_entries[index].base_high = (base_addr >> 24) & 0xFF;
	gdt_entries[index].limit_low = limit & 0xFFFF;
	gdt_entries[index].access_byte = access_byte;
	gdt_entries[index].granularity = (limit >> 16) & 0x0F;
	gdt_entries[index].granularity |= ((gran << 4) & 0xF0);
}

void	init_gdt()
{
	gdt_ptr->size = ( (sizeof(struct gdt_entry) * 7) - 1);
	gdt_ptr->address = (uint32_t)&gdt_entries;

	fill_gdt(0, 0, 0, 0, 0); // NULL entry
	/* Kernel descriptors */
	fill_gdt(1, 0, 0xFFFFF, 0x9A, 0xCF); // Kernel Code
	fill_gdt(2, 0, 0xFFFFF, 0x92, 0xCF); // Kernel Data
	fill_gdt(3, 0, 0xFFFFF, 0x92, 0xCF); // Kernel Stack

	/* User descriptors */
	fill_gdt(4, 0, 0xFFFFF, 0xFA, 0xCF); // User code
	fill_gdt(5, 0, 0xFFFFF, 0xF2, 0xCF); // User data
	fill_gdt(6, 0, 0xFFFFF, 0xF2, 0xCF); // User stack

	gdt_flush((uint32_t)gdt_ptr);
}
