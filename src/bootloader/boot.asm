%include "bootloader.inc"

org 07c00h

	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7c00	
	
	;
	; Get Hard Disk Info 
	;
	mov ah, 08h
	mov dl, 80h
	int 13h
	cmp ah, 0
	jnz LoadError

	; The returned value for Num. of drives is 0 based.
	inc dh
	mov [DiskParamAddr], dl		; Num. of drives
	mov [DiskParamAddr + 1], dh	; Max Head Num.
	mov al, cl
	and al, 0x3f
	
	mov [DiskParamAddr + 2], al	; Max Sec. Num.
	mov al, ch
	mov bl, cl
	shr bl, 6
	mov ah, bl

	; According to Ralf Brown's"Interrupt List, part 2 of 18",
	; the returned value for Max Cylinder. Num is 2 less than actual.
	add ax, 2
	mov [DiskParamAddr + 3], ax	; Max Cylinder Num.
	
	;
	; Load Loader
	;
	mov bx,LoaderStartAddr		; bx是数据存储的位置
	mov cl, LoaderStartSector	; (CL)0~5= 扇区号
	mov ch, 0					; (CH)0~7=柱面/磁道号	
	mov dx, 0080h				; dh 磁头, dl=80h 代表第一个硬盘
	mov ah, 02h        
	mov al, LoaderTakenSectors  ; ah=02h 读扇区, al代表读扇区的数量
	int 13h                     ; 调用中断
	jc LoadError	
	
	jmp LoaderStartAddr

LoadError:
	mov ax, ErrorMessage
	mov bp, ax
	mov cx, 10
	mov ax, 01301h
	mov bx, 0004h
	mov dl, 0
	mov dh, 3
	int 10h
	jmp $
ErrorMessage			: db "Load Error"

	; MBR Tail
	times	510-($-$$) db 0
	dw 0xaa55
