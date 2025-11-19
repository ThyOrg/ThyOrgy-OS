CC = i686-elf-gcc
ASEMBLER = i686-elf-as
LD = ld
FLAGS = -Wall -Wextra -Werror -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -std=gnu99 -ffreestanding -O2
LDFLAGS = -lgcc
QEMU = qemu-system-i386 

# Directories
SRC_FOLDER = src
OBJ_FOLDER = obj
BIN_FOLDER = bin

# Source files
ASM_SRC = $(SRC_FOLDER)/boot.s $(SRC_FOLDER)/gdt.s
C_SRC = $(SRC_FOLDER)/kernel.c $(SRC_FOLDER)/segmentation.c

# Object files
ASM_OBJ = $(OBJ_FOLDER)/boot.o $(OBJ_FOLDER)/gdt.o
C_OBJ = $(OBJ_FOLDER)/kernel.o $(OBJ_FOLDER)/segmentation.o

# Output binary
OS = $(BIN_FOLDER)/kfs-1.bin

# Linker script
LINKER = linker/linker.ld

ISO = isodir/boot/kfs-1.iso

SCRIPT = ./script/script.sh

.PHONY: run_script

# Default target
all: $(OS)


run_script:
	sh $(SCRIPT)	

boot:
	$(QEMU) -cdrom $(ISO)

# Link the final binary
$(OS): $(C_OBJ) $(ASM_OBJ)
	$(CC) $(FLAGS) -T $(LINKER) -o $@ $^ $(LDFLAGS)

# Compile C source files into object files
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(SRC_FOLDER)/kernel.h
	$(CC) $(FLAGS) -c $< -o $@

# Assemble the ASM source into object file
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.s $(SRC_FOLDER)/kernel.h
	$(ASEMBLER) -o $@ $<

# Clean object files
clean:
	rm -f $(OBJ_FOLDER)/*.o

# Clean all (object files and the final binary)
fclean: clean
	rm -f $(OS) 

# Rebuild everything
re: fclean all

