global _print
global _in_port
global _out_port

; print(char *pData, int nPos, int nColor)
; Hidden Param : gs - Video Memory Selector
_print:
	
	; Get Params
	mov eax, [esp + 12]	;color
	mov edi, [esp + 8]	;start position
	mov ecx, [esp + 4]	;char*
	
	; Set Params
	mov ah, al	; Color
		
PUT_CHAR:
	; Get a char
	mov al, byte [ecx]
	cmp al, 0
	jz BACK

	; Print the char
	mov [gs:edi], ax
	add edi, 2
	inc ecx

	jmp PUT_CHAR
	
BACK:
	ret

; void out_port(int port, char value)	
_out_port:
	mov	edx, [esp + 4]
	mov al, byte [esp + 8]
	out dx, al
	nop			; some delay waiting for IO complete
	nop
	ret
	
; char in_port(int port)
_in_port:
	mov edx, [esp + 4]
	xor eax, eax
	in  al, dx
	nop			; some delay waiting for IO complete
	nop
	ret
	
