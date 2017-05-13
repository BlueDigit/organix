# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o monitor.o common.o stdlib.o string.o interrupt.o \
		gdt.o isr.o descriptor_tables.o timer.o
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-melf_i386 -TLink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o *.gch kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
