#
#	Interrupt	disable
#
	.global	interruptDisable
interruptDisable:	/*	 IRQ Disable	FIQ 0x40*/
	MRS	R0,	CPSR
	ORR	R0,	R0	,#0x080	/*#CPSR_IRQ*/
	MSR	CPSR_cxsf,	R0
	MOV	PC,	LR		 /*	return */
#
#	Interrupt	enable
#
	.global	interruptEnable
interruptEnable:	/*	 IEQ Enable FIQ ~0x40*/

	MRS	R0,	CPSR
	AND	R0,	R0	,#~0x80	/*#~CPSR_IRQ*/
	MSR	CPSR_cxsf,	r0
	MOV	PC,	LR		 /*	return */

##_enable_interrupts:
##	MRS	R0, CPSR
##	BIC	R0, R0, #0x80
##	MSR	CPSR_C, r0
##	MOV	PC, LR

##########################################################


##########################################################
	.global	readVectorBaseRegister
readVectorBaseRegister:
	MRC	P15,	0, R0, C12, C0, 0 
	MOV	PC,	LR		 /*	return */

##########################################################
	.global	writeVectorBaseRegister
writeVectorBaseRegister:
#	MRC	p15,	0, r0, c12, c0, 0 
#	LDR	r0,#0x20100000
	MCR	P15,	0, R0, C12, C0, 0 
	MOV	PC,	LR		 /*	return */

##########################00################################
	.global	writeVectorBaseRegister00
writeVectorBaseRegister00:
	MRC	p15,	0, r0, c12, c0, 0 
	LDR	r0,=0x00000000
	MCR	P15,	0, R0, C12, C0, 0 
	MOV	PC,	LR		 /*	return */

##########################################################
	.global	setHighVector
setHighVector:
	MRC	P15,	0,R0, C1, C0, 0
	MOV	R1,#0x00002000
	ORR	R0,R1
	MCR	P15,	0,R0, C1, C0, 0
	MOV	PC,	LR		 /*	return */
	
##########################################################
	.global	setLowVector
setLowVector:
	MRC	P15,	0,R0, C1, C0, 0
	MOV	R1,#0xFFFFDFFF
	AND	R0,R1
	MCR	P15,	0,R0, C1, C0, 0
	MOV	PC,	LR		 /*	return */

##########################################################
	.global	readSCTLR
readSCTLR:
	MRC	P15,	0,R0, C1, C0, 0
	MOV	PC,	LR		 /*	return */

#########################################################
	.global disableInstructionCache
disableInstructionCache:
	PUSH	{lr}
	MRC	p15, #0, r0, c1, c0, #0
	BIC	r0,	r0, #0x00001000
	MCR	p15, #0, r0, c1, c0, #0
@	BL	CP15ICacheFlush
	POP	{lr}
	BX	lr

##########################################################
	.global disableDataCache
disableDataCache:
	PUSH	{r4-r11, lr}
	MRC	p15, #0, r0, c1, c0, #0
	BIC	r0,	r0, #0x00000004
	MCR	p15, #0, r0, c1, c0, #0
@	BL	CP15DCacheCleanFlush
	POP	{r4-r11, lr}
	BX	lr

##########################################################
	.global disableMMU
disableMMU:
	MCR	p15, #0, r0, c8, c7, #0	@ Invalidate TLB	
	MRC	p15, #0, r0, c1, c0, #0	
	BIC	r0, r0, #1	
	MCR	p15, #0, r0, c1, c0, #0	@ Clear MMU bit
	BX	lr

##########################################################
	.global	undefInst
undefInst:
	.long	0xE7FFDEFE
	.long	0xE7FFDEFE
	BX	lr


