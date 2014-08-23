# Compilers, and their params
ASM  = nasm
CC   = gcc
LD	 = ld
ASMFLAGS = -I ../include/  -f elf	#The last slash is necessary
CFLAGS = -c -fno-builtin -nostdinc -fpack-struct -std=c99
LDFLAGS =

DRIVER_OBJ = ../../../obj/vesa.o

# nmake treats the 1st Rule as Default
all : clean vesa

clean:
	rm -f $(DRIVER_OBJ)
	
vesa : $(DRIVER_OBJ)

../../../obj/vesa.o : vesa.c
	$(CC) $(CFLAGS) -o $@ $?	
