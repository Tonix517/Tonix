#include "logo.h"
#include "interrupt.h"
#include "kernel.h"
#include "lib.h"
#include "../drivers/keyboard/keyboard.h"
#include "../drivers/clock/clock.h"
#include "../drivers/vesa/vesa.h"

//		This method name cannot be main because GCC in Win32 
//		will treat it as the main and will add __main and _alloca 
//		into it automatically.
void kernel_main()
{
	//
	//	Initialization
	//
	init_8259A();
	init_idt();

	//	Setup Keyboard Handler
	init_keyboard();
	
	//	Setup Clock
	//init_clock();
	
	//  Set Background Color
	fill_square(0, 0, VESA_X_MAX, VESA_Y_MAX, rgb(0, 0, 10));

	
    //  Draw Logos
    display_pic(20, 100, 240, 320, LogoCat);
    display_pic(280, 100, 240, 320, LogoMain);
    display_pic(540, 100, 240, 320, LogoMe);

    while(1);
}

   
