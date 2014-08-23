global _load_idt

extern _idt_ptr
extern _exception_handler
extern _common_irq_handler
extern _irq_table

INT_MASTER_CTL		equ	0x20
INT_MASTER_CTLMASK	equ 0x21
INT_SLAVE_CTL		equ 0xA0
INT_SLAVE_CTLMASK	equ 0xA1
EOI					equ 0x20

; Internal Exceptions
global _int_divide_error
global _int_single_step_exception
global _int_nmi
global _int_debug_breakpoint
global _int_overflow
global _int_beyond_bounds
global _int_invalid_opcode
global _int_no_coprocessor
global _int_double_error
global _int_coprocessor_seg_overrun
global _int_invalid_tss
global _int_non_existed_seg
global _int_stack_error
global _int_general_protect
global _int_page_error
; _intel preserved _int15
global _int_x87_float_error
global _int_align_check
global _int_machine_check
global _int_simd_float_exception

; External Interrupts
global _int_hw_irq_0
global _int_hw_irq_1
global _int_hw_irq_2
global _int_hw_irq_3
global _int_hw_irq_4
global _int_hw_irq_5
global _int_hw_irq_6
global _int_hw_irq_7
global _int_hw_irq_8
global _int_hw_irq_9
global _int_hw_irq_10
global _int_hw_irq_11
global _int_hw_irq_12
global _int_hw_irq_13
global _int_hw_irq_14
global _int_hw_irq_15

%macro int_hw_irq_handler_master 1
	
	in	al, INT_MASTER_CTLMASK	    ; ┓
	or	al, (1 << %1)				; ┣ 屏蔽当前中断
	out	INT_MASTER_CTLMASK, al	    ; ┛		
	
	push	%1			            ; ┓
	call	[_irq_table + 4 * %1]	; ┣ 中断处理程序
	pop		ecx			            ; ┛
	
	in	al, INT_MASTER_CTLMASK	    ; ┓
	and	al, ~(1 << %1)				; ┣ 恢复接受当前中断
	out	INT_MASTER_CTLMASK, al	    ; ┛
	
	mov al, EOI				; ┓SET EOI
	out INT_MASTER_CTL, al	; ┛

	iretd
	
%endmacro

%macro int_hw_irq_handler_slave 1

	in	al, INT_SLAVE_CTLMASK	    ; ┓
	or	al, (1 << (%1 - 8))			; ┣ 屏蔽当前中断
	out	INT_SLAVE_CTLMASK, al	    ; ┛		
	
	push	%1			            ; ┓
	call	[_irq_table + 4 * %1]	; ┣ 中断处理程序
	pop	    ecx			            ; ┛
	
	in	al, INT_SLAVE_CTLMASK	    ; ┓
	and	al, ~(1 << (%1 - 8))		; ┣ 恢复接受当前中断
	out	INT_SLAVE_CTLMASK, al	    ; ┛
	
	mov al, EOI				; ┓SET EOI
	out INT_SLAVE_CTL, al	; ┛
	
	iretd
	
%endmacro

; Load IDT
_load_idt:
	lidt [_idt_ptr]
	ret
	
_int_divide_error:
	push	0xffffffff
	push	0
	jmp		exception
	
_int_single_step_exception:
	push	0xffffffff
	push	1
	jmp		exception
	
_int_nmi:
	push	0xffffffff
	push	2
	jmp		exception
	
_int_debug_breakpoint:
	push	0xffffffff
	push	3
	jmp		exception
	
_int_overflow:
	push	0xffffffff
	push	4
	jmp		exception
	

_int_beyond_bounds:
	push	0xffffffff
	push	5
	jmp		exception
	

_int_invalid_opcode:
	push	0xffffffff
	push	6
	jmp		exception
	

_int_no_coprocessor:
	push	0xffffffff
	push	7
	jmp		exception
	

_int_double_error:
	push	8
	jmp		exception
	

_int_coprocessor_seg_overrun:
	push	0xffffffff
	push	9
	jmp		exception
	

_int_invalid_tss:
	push	10
	jmp		exception
	

_int_non_existed_seg:
	push	11
	jmp		exception
	

_int_stack_error:
	push	12
	jmp		exception
	

_int_general_protect:
	push	13
	jmp		exception
	

_int_page_error:
	push	14
	jmp		exception
	

; _intel preserved _int15
_int_x87_float_error:
	push	0xffffffff
	push	16
	jmp		exception


_int_align_check:
	push	0xffffffff
	push	18
	jmp		exception
	

_int_machine_check:
	push	0xffffffff
	push	19
	jmp		exception
	

_int_simd_float_exception:
	push	0xffffffff
	push	20
	jmp		exception
	


exception:
	call _exception_handler
	add  esp, 4 * 2	; pop the params nVectorNum, nErrCode
					; PC will pop eip, cs, eflags itself
	hlt

_int_hw_irq_0:
	int_hw_irq_handler_master 0		
_int_hw_irq_1:
	int_hw_irq_handler_master 1
_int_hw_irq_2:
	int_hw_irq_handler_master 2
_int_hw_irq_3:
	int_hw_irq_handler_master 3
_int_hw_irq_4:
	int_hw_irq_handler_master 4
_int_hw_irq_5:
	int_hw_irq_handler_master 5
_int_hw_irq_6:
	int_hw_irq_handler_master 6
_int_hw_irq_7:
	int_hw_irq_handler_master 7
_int_hw_irq_8:
	int_hw_irq_handler_slave 8
_int_hw_irq_9:
	int_hw_irq_handler_slave 9
_int_hw_irq_10:
	int_hw_irq_handler_slave 10
_int_hw_irq_11:
	int_hw_irq_handler_slave 11
_int_hw_irq_12:
	int_hw_irq_handler_slave 12
_int_hw_irq_13:
	int_hw_irq_handler_slave 13
_int_hw_irq_14:
	int_hw_irq_handler_slave 14
_int_hw_irq_15:
	int_hw_irq_handler_slave 15