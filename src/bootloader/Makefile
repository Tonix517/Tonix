# Compilers, and their params
ASM  = nasm
CC   = gcc
LD	 = ld
ASMFLAGS = -I ../include/	#The last slash is necessary
CFLAGS = -I ../include/ -c -fno-builtin
LDFLAGS =

# Binaries
DEMO_BOOT = ../../bin/boot.img ../../bin/loader.img

# Default entry
everything : $(DEMO_BOOT)

clean : 
	rm -f $(DEMO_BOOT)

# Binary Dependancies
../../bin/boot.img : boot.asm
	$(ASM) $(ASMFLAGS) -o $@ $?

../../bin/loader.img : loader.asm
	$(ASM) $(ASMFLAGS) -o $@ $?



