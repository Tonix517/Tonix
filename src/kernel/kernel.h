#ifndef KERNEL_H
#define KERNEL_H

#include "../include/types.h"

/* 描述符类型值说明 */
#define	DA_32			0x4000	/* 32 位段				*/
#define	DA_LIMIT_4K		0x8000	/* 段界限粒度为 4K 字节			*/
#define	DA_DPL0			0x00	/* DPL = 0				*/
#define	DA_DPL1			0x20	/* DPL = 1				*/
#define	DA_DPL2			0x40	/* DPL = 2				*/
#define	DA_DPL3			0x60	/* DPL = 3				*/
/* 存储段描述符类型值说明 */
#define	DA_DR			0x90	/* 存在的只读数据段类型值		*/
#define	DA_DRW			0x92	/* 存在的可读写数据段属性值		*/
#define	DA_DRWA			0x93	/* 存在的已访问可读写数据段类型值	*/
#define	DA_C			0x98	/* 存在的只执行代码段属性值		*/
#define	DA_CR			0x9A	/* 存在的可执行可读代码段属性值		*/
#define	DA_CCO			0x9C	/* 存在的只执行一致代码段属性值		*/
#define	DA_CCOR			0x9E	/* 存在的可执行可读一致代码段属性值	*/
/* 系统段描述符类型值说明 */
#define	DA_LDT			0x82	/* 局部描述符表段类型值			*/
#define	DA_TaskGate		0x85	/* 任务门类型值				*/
#define	DA_386TSS		0x89	/* 可用 386 任务状态段类型值		*/
#define	DA_386CGate		0x8C	/* 386 调用门类型值			*/
#define	DA_386IGate		0x8E	/* 386 中断门类型值			*/
#define	DA_386TGate		0x8F	/* 386 陷阱门类型值			*/

/* 中断向量 */
#define	INT_VECTOR_DIVIDE_ERROR			0x0
#define	INT_VECTOR_SINGLE_STEP			0x1
#define	INT_VECTOR_NMI					0x2
#define	INT_VECTOR_DEBUG_BREAKPOINT		0x3
#define	INT_VECTOR_OVERFLOW				0x4
#define	INT_VECTOR_OVER_BOUNDS			0x5
#define	INT_VECTOR_INVAL_OPCODE			0x6
#define	INT_VECTOR_NO_COPROCESSOR		0x7
#define	INT_VECTOR_DOUBLE_ERROR			0x8
#define	INT_VECTOR_COPROCESSOR_SEG_OVER	0x9
#define	INT_VECTOR_INVAL_TSS			0xA
#define	INT_VECTOR_SEG_NOT_EXIST		0xB
#define	INT_VECTOR_STACK_ERROR			0xC
#define	INT_VECTOR_GENERAL_PROTECTION	0xD
#define	INT_VECTOR_PAGE_ERROR			0xE
#define	INT_VECTOR_X87_FLOAT_ERROR		0x10
#define	INT_VECTOR_ALIGN_CHECK			0x11
#define	INT_VECTOR_MACHINE_CHECK		0x12
#define	INT_VECTOR_SIMD_FLOAT_EXCEPTION 0x13

/* 权限 */
#define	PRIVILEGE_KRNL	0
#define	PRIVILEGE_TASK	1
#define	PRIVILEGE_USER	3

//	Gate Definitions
struct Gate
{
	U16	nOffsetLow;
	U16 selector;
	U8  nDCount;
	U8  nAttr;
	U16 nOffsetHigh;
};

//	Descriptor Definitions
struct Descriptor		/* 共 8 个字节 */
{
	U16	nLimitLow;		/* Limit */
	U16	nBaseLow;		/* Base */
	U8	nBaseMid;		/* Base */
	U8	nAttr1;			/* P(1) DPL(2) DT(1) TYPE(4) */
	U8	nLimitHigh_Attr2;	/* G(1) D(1) 0(1) AVL(1) LimitHigh(4) */
	U8	nBaseHigh;		/* Base */
};

//	GDT Definitions
#define GDT_SIZE 128
U8 gdt_ptr[6]; // 0~15 : Limit	16~47 : Base
struct Descriptor gdt[GDT_SIZE];

//  Kernel Selector Value
//  It's hard-coded. The selector for kernel
//  has to be the first valid selector in GDT
#define KERNEL_SELECTOR 0x8

//	Value Color From http://www.brackeen.com/vga/basics.html
#define BLACK	        0
#define BLUE	        1
#define GREEN	        2
#define CYAN	        3
#define RED		        4
#define MAGENTA		    5
#define BROWN	        6
#define LIGHT_GRAY	    7
#define DARK_GRAY	    8
#define LIGHT_BLUE	    9
#define LIGHT_GREEN	    10
#define LIGHT_CYAN	    11
#define LIGHT_RED	    12
#define LIGHT_MAGENTA	13
#define YELLOW	        14
#define WHITE	        15

#endif
