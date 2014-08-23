#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "kernel.h"

//	8259A Controller Ports
#define INT_MASTER_CTL		0x20
#define INT_MASTER_CTLMASK	0x21
#define INT_SLAVE_CTL		0xA0
#define INT_SLAVE_CTLMASK	0xA1

#define INT_VECTOR_IRQ0	0x20
#define INT_VECTOR_IRQ8	0x28

//	IDT Definitions
#define IDT_SIZE 0x100
U8	idt_ptr[6]; // 0~15 (); Limit		16~47 (); Base
struct Gate idt[IDT_SIZE];

//	In lib.asm
extern void out_port(int port, char value);
extern char in_port(int port);
extern void load_idt(void);

extern void int_divide_error();
extern void int_single_step_exception();
extern void int_nmi();
extern void int_debug_breakpoint();
extern void int_overflow();
extern void int_beyond_bounds();
extern void int_invalid_opcode();
extern void int_no_coprocessor();
extern void int_double_error();
extern void int_coprocessor_seg_overrun();
extern void int_invalid_tss();
extern void int_non_existed_seg();
extern void int_stack_error();
extern void int_general_protect();
extern void int_page_error();
extern void int_x87_float_error();
extern void int_align_check();
extern void int_machine_check();
extern void int_simd_float_exception();

extern void int_hw_irq_0();	
extern void int_hw_irq_1();	
extern void int_hw_irq_2();	
extern void int_hw_irq_3();	
extern void int_hw_irq_4();
extern void int_hw_irq_5();
extern void int_hw_irq_6();
extern void int_hw_irq_7();
extern void int_hw_irq_8();
extern void int_hw_irq_9();
extern void int_hw_irq_10();
extern void int_hw_irq_11();
extern void int_hw_irq_12();
extern void int_hw_irq_13();
extern void int_hw_irq_14();
extern void int_hw_irq_15();

typedef void (*tpIrqHandler)(U32);
extern tpIrqHandler irq_table[16];

void init_8259A(void);
void init_idt(void);
void init_idt_desc(U8 nVecNum, U8 nDescType, void (*pHandler)(), U8 nPrivilige);

void exception_handler(int nVectorNum, int nErrCode, int nEip, int nCs, int nEFlags);
void common_irq_handler(U32 nIRQ);

//	For Hardware
void set_irq_handler(U8 nVecNum, void (*pHandler)(int));
void enable_irq(U8 nIrqNum);

#endif
