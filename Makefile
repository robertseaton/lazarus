OBJECTS = boot.o console.o main.o string.o

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -g -O0 -Wall -Wextra
LDFLAGS = -melf_i386 -T link.ld
ASFLAGS = -f elf

kernel: $(OBJECTS) link

clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(OBJECTS)

.s.o:
	nasm $(ASFLAGS) $<

qemu:
	qemu-system-i386 -kernel kernel

# tests

TESTS = console_test

test: $(TESTS)

console_test:
	$(CC) -o tests/console_test.o -c tests/console_test.c
	$(CC) -o tests/console_test tests/console_test.o -latf-c
