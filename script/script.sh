#!/bin/bash

if grub-file --is-x86-multiboot bin/kfs-1.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi

cp bin/kfs-1.bin isodir/boot/kfs-1.bin

grub-mkrescue -o isodir/boot/kfs-1.iso isodir
