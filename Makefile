# Compilers, and their params
ASM  = nasm
ASMFLAGS = -I ./		#The last slash is necessary
NMAKEFLAGS = /NOLOGO

# Binaries
DEMO_BOOT = bin/boot.img bin/loader.img
DEMO_KERNEL = bin/kernel.img

# nmake treats the 1st Rule as Default
all : clean bootloader kernel

bootloader : $(DEMO_BOOT)

kernel : $(DEMO_KERNEL)

clean : 
	echo "Cleaning"

	cd $(MAKEDIR)/src/bootloader
	nmake $(NMAKEFLAGS) clean

	cd $(MAKEDIR)/src/kernel
	nmake $(NMAKEFLAGS) clean
	
	cd $(MAKEDIR)/src/drivers
	nmake $(NMAKEFLAGS) clean 
	
# Binary Dependancies

$(DEMO_BOOT):
	echo "[Making Bootloader]"
	cd $(MAKEDIR)/src/bootloader
	nmake $(NMAKEFLAGS)

# Now kernel depends on drivers. So drivers has to be 
# made first. I'll rearrange the makefile structure
$(DEMO_KERNEL):	
	echo "[Making Drivers]"	
	cd $(MAKEDIR)/src/drivers
	nmake $(NMAKEFLAGS)	
	
	echo "[Making Kernel]"	
	cd $(MAKEDIR)/src/kernel
	nmake $(NMAKEFLAGS)		
	