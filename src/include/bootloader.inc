;============ Constants ===========
; Num. of Drives		- byte [0x7D00]
; Max Head Num.			- byte [0x7D01]
; Max Sec. Num.			- byte [0x7D02]
; Max Cylinder Num.		- word [0x7D03]
DiskParamAddr		equ		0x7D00

LoaderStartSector  	equ 	2
LoaderTakenSectors 	equ 	1
LoaderStartAddr  	equ 	0x9000

; Don't forget to update kernel's makefile ld param
%define KERNEL_START_ADDR	0xA000
%define KERNEL_LENGTH		(KERNEL_SECTOR * 512)
%define KERNEL_SEG_NUM	    8

; Sec. 33 is the 1st sec. of cylinder 2
KernelStartSector	equ		33

%define VESA_VIDEO_MEM_ADDR_PTR 0x7F00
;==================================
