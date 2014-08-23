# Compilers, and their params
ASM  = nasm
CC   = gcc
LD	 = ld
ASMFLAGS = -I ../include/  -f elf	#The last slash is necessary
CFLAGS = -c -fno-builtin -nostdinc -fpack-struct -std=c99
LDFLAGS =

DRIVER_OBJ = ../../../obj/keyboard.o

# nmake treats the 1st Rule as Default
all : clean keyboard

clean:
	rm -f $(DRIVER_OBJ)
	
keyboard : $(DRIVER_OBJ)

../../../obj/keyboard.o : keyboard.c
	$(CC) $(CFLAGS) -o $@ $?	