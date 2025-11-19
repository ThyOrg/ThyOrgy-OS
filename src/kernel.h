#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

#define GDTBASE 0x00000800

#define HEXA_BASE "0123456789ABCDEF"

#define DESC_CODE 0x9A
#define DESC_DATA 0x92
#define DESC_STACK 0x96

#define DESC_UCODE 0xFA
#define DESC_UDATA 0xF2
#define DESC_USTACK 0xF6


extern void gdt_flush(uint32_t gdt_ptr);

struct gdtr {
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));

struct gdtdesc {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t other;
    uint8_t base_high;
} __attribute__ ((packed));

typedef struct gdtdesc gdt_desc_t;
typedef struct gdtr gdt_t;

gdt_desc_t gdt[7];

void init_gdt_desc(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t other);

void init_gdt();


// Printing
void terminal_putchar(char c);
void printk(uint32_t c);

#endif