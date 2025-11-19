#include "kernel.h"

gdt_t *gdt_ptr = (gdt_t *)GDTBASE;


void init_gdt_desc(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t other)
{
    gdt[index].base_low = (base & 0xFFFF);
    gdt[index].base_mid = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;
    gdt[index].limit_low = (limit & 0xFFFF);
    gdt[index].access = access;
    gdt[index].other = (limit >> 16) &0x0F;
    gdt[index].other |= ((other << 4) & 0xF0);
}

void init_gdt()
{
    gdt_ptr->base = (uint32_t)&gdt;
    gdt_ptr->limit = (sizeof(gdt_desc_t) * 7) - 1;
    
    init_gdt_desc(0, 0, 0, 0, 0);

    // kernel segments
    init_gdt_desc(1, 0x0, 0xFFFFF, 0x9A, 0xC); // code segment
    init_gdt_desc(2, 0x0, 0xFFFFF, 0x92, 0xC); // data segment
    init_gdt_desc(3, 0x0, 0xFFFFF, 0x96, 0xC); // stack segment

    // User segments
    init_gdt_desc(4, 0x0, 0xFFFFF, 0xFA, 0xC); //code segment
    init_gdt_desc(5, 0x0, 0xFFFFF, 0xF2, 0xC); // data segment
    init_gdt_desc(6, 0x0, 0xFFFFF, 0xF6, 0xC); // stack segment
    
    gdt_flush((uint32_t)gdt_ptr);
}