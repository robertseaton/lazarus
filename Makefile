objects = boot.o console.o main.o string.o

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -g -O0
LDFLAGS = -melf_i386 -T link.ld
ASFLAGS = -f elf

kernel: $(objects) link

clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(objects)

.s.o:
	nasm $(ASFLAGS) $<

qemu:
	qemu-system-i386 -kernel kernel
