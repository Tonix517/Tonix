#include "interrupt.h"
#include "lib.h"

char* ExceptionInfo[] =
{
	"Divide Error",
	"Debug Exception",
	"NMI",
	"Debug BreakPoint",
	"Overflow",
	"Beyond the boundary",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Error",
	"Coprocessor Beyond the boundary"
	"Invalid TSS",
	"Non-existed Segment",
	"Stack Error",
	"General Protection Error",
	"Page Error",
	"X87 Float Error",
	"Alignment Error",
	"Machine Error",
	"SIMD Float Error"
};

tpIrqHandler irq_table[16];

void init_8259A()
{
	//	ICW1 = 0x11
	out_port(INT_MASTER_CTL, 0x11);
	out_port(INT_SLAVE_CTL, 0x11);

	//	IRQ0 -> Interrupt Vector INT_VECTOR_IRQ0
	out_port(INT_MASTER_CTLMASK, INT_VECTOR_IRQ0);

	//	IRQ8 -> Interrupt Vector INT_VECTOR_IRQ8
	out_port(INT_SLAVE_CTLMASK, INT_VECTOR_IRQ8);

	//	ICW3 : IR2 Cascade
	out_port(INT_MASTER_CTLMASK, 0x4);
	out_port(INT_SLAVE_CTLMASK, 0x2);

	//	ICW4 : 0x1
	out_port(INT_MASTER_CTLMASK, 0x1);
	out_port(INT_SLAVE_CTLMASK, 0x1);

	//	OCW1 : Close All Master Interrupts 
	out_port(INT_MASTER_CTLMASK, 0xFF);

	//	OCW1 : Close All Slave Interrupts
	out_port(INT_SLAVE_CTLMASK, 0xFF);

	for(int i = 0; i<16; i++)
	{
		irq_table[i] = common_irq_handler;
	}
}

void init_idt()
{

	U16* pIDT_Limit = (U16*)(&idt_ptr[0]);
	U32* pIDT_Base  = (U32*)(&idt_ptr[2]);
	*pIDT_Limit = IDT_SIZE  * sizeof(struct Gate);
	*pIDT_Base  = (U32)&idt;

	init_idt_desc(INT_VECTOR_DIVIDE_ERROR,			DA_386IGate, int_divide_error,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_SINGLE_STEP,			DA_386IGate, int_single_step_exception,		PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_NMI,					DA_386IGate, int_nmi,						PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_DEBUG_BREAKPOINT,		DA_386IGate, int_debug_breakpoint,			PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_OVERFLOW,				DA_386IGate, int_overflow,					PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_OVER_BOUNDS,			DA_386IGate, int_beyond_bounds,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_INVAL_OPCODE,			DA_386IGate, int_invalid_opcode,			PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_NO_COPROCESSOR,		DA_386IGate, int_no_coprocessor,			PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_DOUBLE_ERROR,			DA_386IGate, int_double_error,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_COPROCESSOR_SEG_OVER,	DA_386IGate, int_coprocessor_seg_overrun,	PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_INVAL_TSS,				DA_386IGate, int_invalid_tss,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_SEG_NOT_EXIST,			DA_386IGate, int_non_existed_seg,			PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_STACK_ERROR,			DA_386IGate, int_stack_error,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_GENERAL_PROTECTION,	DA_386IGate, int_general_protect,			PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_PAGE_ERROR,			DA_386IGate, int_page_error,				PRIVILEGE_KRNL);
	//	Int 15 is reserved by Intel
	init_idt_desc(INT_VECTOR_X87_FLOAT_ERROR,		DA_386IGate, int_x87_float_error,			PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_ALIGN_CHECK,			DA_386IGate, int_align_check,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_MACHINE_CHECK,			DA_386IGate, int_machine_check,				PRIVILEGE_KRNL);
	init_idt_desc(INT_VECTOR_SIMD_FLOAT_EXCEPTION,	DA_386IGate, int_simd_float_exception,		PRIVILEGE_KRNL);	

	init_idt_desc(INT_VECTOR_IRQ0,		DA_386IGate, int_hw_irq_0,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 1,	DA_386IGate, int_hw_irq_1,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 2,	DA_386IGate, int_hw_irq_2,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 3,	DA_386IGate, int_hw_irq_3,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 4,	DA_386IGate, int_hw_irq_4,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 5,	DA_386IGate, int_hw_irq_5,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 6,	DA_386IGate, int_hw_irq_6,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ0 + 7,	DA_386IGate, int_hw_irq_7,		PRIVILEGE_KRNL);	

	init_idt_desc(INT_VECTOR_IRQ8,		DA_386IGate, int_hw_irq_8,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 1,	DA_386IGate, int_hw_irq_9,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 2,	DA_386IGate, int_hw_irq_10,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 3,	DA_386IGate, int_hw_irq_11,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 4,	DA_386IGate, int_hw_irq_12,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 5,	DA_386IGate, int_hw_irq_13,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 6,	DA_386IGate, int_hw_irq_14,		PRIVILEGE_KRNL);	
	init_idt_desc(INT_VECTOR_IRQ8 + 7,	DA_386IGate, int_hw_irq_15,		PRIVILEGE_KRNL);

	load_idt();
}

void init_idt_desc(U8 nVecNum, U8 nDescType, void (*pHandler)(), U8 nPrivilige)
{
	struct Gate* pGate	= &idt[nVecNum];

	U32 nBase			= (U32)pHandler;
	pGate->nOffsetLow	= nBase & 0xFFFF;
	pGate->selector		= KERNEL_SELECTOR;		
	pGate->nDCount		= 0;
	pGate->nAttr		= nDescType | (nPrivilige << 5);
	pGate->nOffsetHigh	= (nBase >> 16) & 0xFFFF;
}

void exception_handler(int nVectorNum, int nErrCode, int nEip, int nCs, int nEFlags)
{    

	c_print("Exception : ", 0, 0, LIGHT_RED);
	c_print(ExceptionInfo[nVectorNum], 12, 0, LIGHT_RED);

	char zU32Data[11];

	memset(zU32Data, 0, 11);
	int nErrCodeLen = hex2a(nErrCode, zU32Data);
	c_print(zU32Data, 0, 1, LIGHT_RED);

	memset(zU32Data, 0, 11);
	int nEipLen = hex2a(nEip, zU32Data);
	c_print(zU32Data, nErrCodeLen + 2, 1, LIGHT_RED);

	memset(zU32Data, 0, 11);
	int nCsLen = hex2a(nCs, zU32Data);
	c_print(zU32Data, nEipLen + nErrCodeLen + 4, 1, LIGHT_RED);

	memset(zU32Data, 0, 11);
	int nEFlagsLen = hex2a(nEFlags, zU32Data);
	c_print(zU32Data, nCsLen + nEipLen + nErrCodeLen + 6, 1, LIGHT_RED);

}

void common_irq_handler(U32 nIRQ)
{
	char buf[12];
	memset(buf, 0 ,12);

	hex2a(nIRQ, buf);
	static int x = 0;
	c_print(buf, x++, 15, LIGHT_GREEN);
}

void set_irq_handler(U8 nIrqNum, void (*pHandler)())
{
	__asm("cli");

	irq_table[nIrqNum] = pHandler;

	__asm("sti");
}

void enable_irq(U8 nIrqNum)
{
	//	Master
	if(nIrqNum < 8)
	{
		U8 nMask = 1 << nIrqNum;
		out_port(INT_MASTER_CTLMASK, ~nMask);
	}
	//	Slave
	else
	{
		U8 nMask = 1 << (nIrqNum - 8);
		out_port(INT_SLAVE_CTLMASK, ~nMask);
	}
}
