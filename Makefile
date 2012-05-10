objects = boot.o console.o main.o string.o

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -melf_i386 -T link.ld
ASFLAGS = -f elf

all: $(objects) link

clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(objects)

.s.o:
	nasm $(ASFLAGS) $<

