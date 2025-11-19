.global gdt_flush

gdt_flush:
        movl 4(%esp), %eax
        lgdt (%eax)

        mov $0x10, %ax        # Data segment selector (index 2)
        mov %ax, %ds
        mov %ax, %es
        mov %ax, %fs
        mov %ax, %gs
        mov %ax, %ss

        # Far jump to reload CS
        ljmp $0x08, $.flush

.flush:
    ret
