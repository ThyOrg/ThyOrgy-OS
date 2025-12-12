#ifndef GDT_H
#define GDT_H
#include <stdint.h>

#define KERNEL_STACK_SIZE 0x4000
#define GDT_ADDRESS 0x00000800

struct gdt_entry
{
	uint16_t	limit_low;
	uint16_t	base_low;
	uint8_t		base_mid;
	uint8_t		access_byte;
	uint8_t		granularity;
	uint8_t		base_high;
} __attribute__((packed));

struct gdt_ptr_struct
{
	uint16_t	 size;
	uint32_t	 address;
} __attribute__((packed));

void    fill_gdt(int index, uint32_t base_addr, uint32_t limit, uint8_t access_byte, uint8_t gran);
void	init_gdt(void);

#endif
