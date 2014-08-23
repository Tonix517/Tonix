# Compilers, and their params
ASM  = nasm
CC   = gcc
LD	 = ld
ASMFLAGS = -I ../include/  -f elf	#The last slash is necessary
CFLAGS = -c -fno-builtin -nostdinc -fpack-struct -std=c99
LDFLAGS =

# Binaries
DEMO_KERNEL = ../../bin/kernel.img
DEMO_KERNEL_OBJ = ../../obj/main.o ../../obj/lib.o ../../obj/start.o \
				  ../../obj/interr.o ../../obj/interr.asmo ../../obj/libc.o
DEMO_KERNEL_DRIVER = ../../obj/keyboard.o ../../obj/clock.o ../../obj/vesa.o 

# Default entry
everything : $(DEMO_KERNEL)

clean : 
	rm -f $(DEMO_KERNEL) $(DEMO_KERNEL_OBJ) ../../obj/kernel.tmp

# Binary Dependancies
../../bin/kernel.img : $(DEMO_KERNEL_OBJ) $(DEMO_KERNEL_DRIVER)
	ld -e kernel_start -Ttext 0xA000 -o ../../obj/kernel.tmp $? 
	objcopy -R .note -R .comment -S -O binary ../../obj/kernel.tmp $@

../../obj/main.o : main.c
	$(CC) $(CFLAGS) -o $@ $?	

../../obj/lib.o : lib.asm
	$(ASM) $(ASMFLAGS) -o $@ $?

../../obj/start.o : start.asm
	$(ASM) $(ASMFLAGS) -o $@ $?

../../obj/interr.o : interrupt.c
	$(CC) $(CFLAGS) -o $@ $?

../../obj/interr.asmo : interrupt.asm
	$(ASM) $(ASMFLAGS) -o $@ $?


../../obj/libc.o : lib.c
    $(CC) $(CFLAGS) -o $@ $?

