OBJECTS = boot.o console.o main.o string.o

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -g -O0 -Wall -Wextra
LDFLAGS = -melf_i386 -T link.ld
ASFLAGS = -f elf

.s.o:
	nasm $(ASFLAGS) $<

clean:
	rm *.o kernel; \
	make -C tests clean

gdb: kernel
	qemu-system-i386 -S -s -kernel kernel

kernel: $(OBJECTS) link

link:
	ld $(LDFLAGS) -o kernel $(OBJECTS)

qemu: kernel
	qemu-system-i386 -kernel kernel

test: kernel
	make -C tests test
