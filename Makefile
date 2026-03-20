# By Ember2819, google, and random people on the internet.... What are we doing????

# C compiler
CC = gcc
# Assembler (for boot.s)
AS = nasm
# Linker
LD = ld

CC_FLAGS = -m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -c

AS_FLAGS = -f bin

LD_FLAGS = -m elf_i386 -T linker.ld

KERNEL_OBJECTS = kernel/kernel.o kernel/drivers/vga.o

# Builds the final disk image
all: os.img

%.o: %.c
	$(CC) $(CC_FLAGS) $< -o $@

# Assemble the bootloader
bootloader/boot.bin: bootloader/boot.s
	$(AS) $(AS_FLAGS) $< -o $@

# Link all kernel objects 
kernel.bin: $(KERNEL_OBJECTS)
	$(LD) $(LD_FLAGS) $(KERNEL_OBJECTS) -o kernel.bin

os.img: bootloader/boot.bin kernel.bin
	cat bootloader/boot.bin kernel.bin > os.img

# Launch the image in QEMU
run: os.img
	qemu-system-i386 -drive format=raw,file=os.img

clean:
	rm -f $(KERNEL_OBJECTS) kernel.bin bootloader/boot.bin os.img

.PHONY: all run clean
