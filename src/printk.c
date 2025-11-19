#include "kernel.h"


void put_nbr(int number)
{
    long n;

    n = number;
    if (n < 0)
    {
        n *= -1;
        terminal_putchar('-');
    }
    if (n > 9)
    {
        put_nbr(n / 10);
        put_nbr(n % 10);
    }
    else
    {
        terminal_putchar('0' + n);
    }
}

void print_addr(unsigned long c)
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

void printk(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    for (const char *p = fmt; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            switch (*p) {
                case 'x': {
                    unsigned long val = va_arg(args, unsigned long);
                    print_addr(val);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    terminal_writestring(str);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    terminal_putchar(c);
                    break;
                }
                case 'p': {
                    void *ptr = va_arg(args, void *);
                    terminal_writestring("0x");
                    print_addr((unsigned long)ptr);
                    break;
                }
                case 'd' : {
                    int n = (int)va_arg(args, int);
                    put_nbr(n);
                    break;
                }
                default:
                    terminal_putchar('%');
                    terminal_putchar(*p);
                    break;
            }
        } else {
            terminal_putchar(*p);
        }
    }
    va_end(args);
}