%include	"pm.inc"	
%include	"bootloader.inc"

EXTERN _main

ORG LoaderStartAddr
	jmp loader_main

; Handling Kernel Loading Error	
LoadError:
	mov ax, ErrorMessage
	mov bp, ax
	mov cx, 17
	mov ax, 01301h
	mov bx, 0009h
	mov dl, 0
	mov dh, 3
	int 10h
	jmp $
	ErrorMessage: db "Load Kernel Error"

; Func. Read Sectors
;	directly use Tinix's code for I don't like 
;	pure asm programming.
;
;\note	Due to Real mode constraint, the kernel cannot be 
;		greater than 1MB. I know there's a hack, but it's
;		far from my current skill level.
;
;\param AX		From which sector to read
;\param CL		How many sectors to read
;\param ES:BX	The mem addr to read to
;
ReadSector:	
	; push the sectors to read to stack
	push bp
	mov bp, sp
	sub sp, 2
	mov byte [bp - 2], cl
	
	push bx

	; Calc Disk Pos : head no., cylinder no., sec. no.
	mov bl, [DiskParamAddr + 2]	; Spt
	div bl	
	cmp ah, 0
	jz .IsMaxSecNo

	mov cl, ah			; Start Sec Num. Got -> CL
	mov ah, 0
	jmp .CalcCylinderNum

.IsMaxSecNo :
	mov cl, [DiskParamAddr + 2]	
	dec al

.CalcCylinderNum : 

	; I assume that the kernel will not cover more than 1 head.
	; So I cannot promise it works if the kernel is large enough
	; that one head cannot contain. Kernel should be small.

	mov bx, [DiskParamAddr + 3] ; Max Cylinder Num. per head		
	mov dx, 0
	div bx
	mov ch, dl			; Cylinder Num. Got	-> CH
	
	; TODO - Bochs 2.3.6 Bug
	; Bochs 2.3.6 has a bug : Cyl. No 0 is mapped to the right
	; cyl. in disk(cyl. 0). But Cyl. 1 is mapped to Cyl. 2 in 
	; disk. It is to say that the actual Cyl. 1 is missed to map.
	dec ch
	
	mov dh, al			; Header Num Got -> DH		More than 2 heads isn't supported
	
	; Now every parameter is got.
	pop bx
	
	; Drive Num. 80h for 1st hard disk. Hard-coded for now
	mov dl, 0x80	
	
.GoOnReading:
	mov ah, 2
	mov al, byte [bp-2]
	int 13h
	jc .GoOnReading
	
	add esp, 2
	pop bp
	
	ret
;;;;;;;;;;;;;;;;; Func ReadSector End ;;;;;;;;;;;;;;;;;;;;
	
KernelSeg	dw 0

; Get Ready for Entering the Protected Mode
loader_main:
	mov	ax, cs
	mov	ds, ax
	mov	es, ax
	mov	ss, ax
	mov	sp, LoaderStartAddr

    ; Start to Loade Kernel
	mov word [KernelSeg], KERNEL_SEG_NUM
	mov ax, 0
	mov es, ax
	mov bx, KERNEL_START_ADDR
	mov ax, KernelStartSector		

    ; I read the kernel by one segment(64K) per time,
    ; for there's something really weird in Bochs 2.3.6.
    ; Doing so can ease debugging.
.ReadNextSeg:	
	
	mov cl, 128
	push ax
	call ReadSector	
	pop ax

	; Move the next Seg
	push ax
	mov ax, es	
	add ax, 0x1000
	mov es, ax
	pop ax

    ; TODO - Bochs 2.3.6 Bug
    ; Bochs 2.3.6 seems to have treated one sector
    ; 1K, instead of 512B.
	add ax, 64
	
	dec word [KernelSeg]
	cmp word [KernelSeg], 0	
	jnz .ReadNextSeg			
		
	; Reset Disk after loading
	mov ah, 0
	mov dl, 0x80	; First Hard Disk, hard coded now
	int 13h
	
	; Set VESA Mode
	mov ax , 0x4f02
    mov bx , 0x4114     ;800 * 600 ( 5:6:5 )    ; TODO : Why 0x114 cannot work while 0x4114 works?
    int 10h
	
	; Get set VESA Mode Info
    mov bx , 0x0
	mov es , bx  
    mov di , VESA_VIDEO_MEM_ADDR_PTR 
    mov ax , 0x4f01
    mov cx , 0x114
    int 0x10  
    mov eax , [ es : VESA_VIDEO_MEM_ADDR_PTR + 0x28 ]
    mov [ VESA_VIDEO_MEM_ADDR_PTR ] , eax
	
	; Enter Protected Mode	
	lgdt	[GDT_Ptr]

	cli

	;	Open A20
	mov	ax , 0x2401
	int 0x15
	
	;	Turn the switch for PM open
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax
	
	mov ax, SelectorVideo
	mov gs, ax
	
	; GCC will never consider that you use him to write kernel. :P
	mov ax, SelectorKernelData
	mov	ds, ax
	mov	es, ax
	mov	fs, ax
	mov	ss, ax
	mov esp,KERNEL_START_ADDR 	; The kernel stack is just atop itself
	jmp dword SelectorKernel:KERNEL_START_ADDR			

; Segment for GDT
[SECTION .gdt]
                                   
GDT_DESC_START :        Descriptor	0,	0,	0
GDT_DESC_KERNEL:	    Descriptor	0,	0fffffh, DA_CR  | DA_32 | DA_LIMIT_4K			; 0 ~ 4G   
GDT_DESC_KERNEL_DATA:	Descriptor  0,  0fffffh, DA_DRW | DA_32 | DA_LIMIT_4K			; 0 ~ 4G
GDT_DESC_VIDEO :		Descriptor	0B8000h, 0ffffh, DA_DRW
GDT_DESC_REAL_MODEL     Descriptor  0,  0ffffh,     DA_CR | DA_DRW

GDT_Len		equ	$ - GDT_DESC_START	
GDT_Ptr		dw	GDT_Len			; GDT Limit	
		    dd	GDT_DESC_START	; GDT Base Addr

SelectorKernel		equ	GDT_DESC_KERNEL - GDT_DESC_START
SelectorKernelData	equ	GDT_DESC_KERNEL_DATA - GDT_DESC_START		    
SelectorVideo		equ GDT_DESC_VIDEO - GDT_DESC_START	
