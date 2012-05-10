srcs = *.h *.c *.s
objects = boot.o console.o main.o string.o

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -g -O0
LDFLAGS = -melf_i386 -T link.ld
ASFLAGS = -f elf

depend: .depend

.depen: $(srcs)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend

all: kernel img

kernel: $(objects) link

clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(objects)

.s.o:
	nasm $(ASFLAGS) $<

img: 
	sudo losetup /dev/loop0 floppy.img
	sudo mount /dev/loop0 /mnt
	sudo cp kernel /mnt/kernel
	sudo umount /dev/loop0
	sudo losetup -d /dev/loop0

run:
	sudo /sbin/losetup /dev/loop0 floppy.img
	sudo bochs -f bochsrc.txt
	sudo /sbin/losetup -d /dev/loop0

