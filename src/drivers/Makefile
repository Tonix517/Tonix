# Compilers, and their params
NMAKEFLAGS = /NOLOGO

DRIVER_OBJ = ../../obj/keyboard.o ../../obj/clock.o ../../obj/vesa.o

# nmake treats the 1st Rule as Default
all : 	
	cd $(MAKEDIR)/keyboard
	nmake $(NMAKEFLAGS)
	cd $(MAKEDIR)/clock
	nmake $(NMAKEFLAGS)
	cd $(MAKEDIR)/vesa
	nmake $(NMAKEFLAGS)

clean:
	rm -f $(DRIVER_OBJ)	
