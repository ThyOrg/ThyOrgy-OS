#ifndef KERNEL_H
#define KERNEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kputnbr(int n);
char *kstrjoin(char const *s1, char const *s2);
size_t ksrtlen(const char *str);
void kputstr(char *str);
void kputchar(char c);
void terminal_writestring(const char *data);
void terminal_write(const char *data, size_t size);
void terminal_putchar(char c);


#endif
