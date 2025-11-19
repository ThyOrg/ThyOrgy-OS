#include "kernel.h"

void print_addr(uint32_t c)
{
    if (c >= 16)
    {
        print_addr(c / 16);
        print_addr(c % 16);
    }
    else
    {
        terminal_putchar(HEXA_BASE[c]);
    }
}

void printk(uint32_t c)
{
    print_addr(c);
}