AS_SRC = ./src/boot.s
C_SRC = ./src/kernel.c
LINKER = linker.ld
AS_OBJ = $(AS_SRC:.s=.o)
C_OBJ = $(C_SRC:.c=.o)

CC = i686-elf-gcc
AC = i686-elf-as

NAME = kfc-1

all: build

build: fclean
	mkdir -p build
	$(AC) $(AS_SRC) -o ./build/boot.o
	$(CC) -c $(C_SRC) -o ./build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC) -T ./src/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib ./build/boot.o ./build/kernel.o -lgcc

iso: build
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp src/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

run: iso
	qemu-system-i386 -cdrom myos.iso

fclean:
	rm -rf ./build/*
