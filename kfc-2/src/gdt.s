.global gdt_flush

gdt_flush:
	movl 4(%esp), %eax
	lgdt (%eax)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %ss
	mov %ax, %gs
	ljmp $0x08, $.flush_label
.flush_label:
	ret
