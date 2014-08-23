; We can't write the first instruction of kernel by C.
; Because GCC in Win32 will treat the first methods as the 
; heading area of text section. Say you defined a method
; foo() before kernel_main() in you c file, then GCC LD will 
; put the foo() as the first instruction of the whole text 
; section. Actually you can solve it by always putting 
; kernel_main() at the very beginning of you c file. But it
; is stupid.

[BITS 32]

extern _kernel_main

global kernel_start

kernel_start:
    
    call _kernel_main

    ; It should never be here
    jmp $