@ startup
	.global _start
	.align
_start:

#
#.ifdef	HYPER
	mrs r0,cpsr
	bic r0,r0,#0x1F
	orr r0,r0,#0x13
	msr spsr_cxsf,r0

	ldr r0,=.L000
	msr ELR_hyp,r0
	eret
.L000:
#.endif
#
	// Set Stack pointer in IRQ mode 
	// IRQ,FIQ disable, Thumb disable, IRQ mode
	ldr	r0, =0x000000d2
	msr	cpsr_c, r0
	ldr	sp, =0x00008000

	// Set Stack pointer in SVC mode
	// IRQ,FIQ disable, Thumb disable, SVC mode 
	ldr	r0, =0x000000d3
	msr	CPSR_c, r0
	ldr	sp, =0x06400000

	BL	initializeMemory
	//  Call main
	bl main

	//  End(Infinity loop)
	b .

.global _hangup
_hangup:
	// IRQ,FIQ disable, Thumb disable, SVC mode 
	ldr	r0, =0x000000d3
	msr	cpsr, r0
//	bl 	print01
	b .


_IRQ_iterrupt:
	// Save the register contents to the stack
	stmfd	r13!, {r0-r12,lr}
	// Call interrupt handler (C language)
	bl	interruptServiceRoutine
	//bl	IRQ_handler
	//bl	print09
	// Restore the contents of register from stack
	ldmfd	r13!, {r0-r12,lr}
	//  Correct return address(IRQ is lr-4),and return to original execution program address
	subs	pc,lr, #4


// Enable IRQ(set CPSR)
	.global enable_IRQ
enable_IRQ:
	mrs	r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c,r0
	bx lr

// Disable IRQ(set CPSR)
	.global disable_IRQ
disable_IRQ:
	mrs	r0, cpsr
	ldr	r1,	=0x80
	orr r0, r0, r1
	msr	cpsr_c, r0
	bx lr

// Get CPSR value, and return( r0 is used as return value)
	.global getmode
getmode:
	mrs	r0, cpsr
	bx lr


// for Vector table setting
	.global  _initial_vector_start
_initial_vector_start:
	ldr	pc, _vec_Reset
	ldr	pc, _vec_Undef
	ldr	pc, _vec_SWI
	ldr	pc, _vec_PrefAbort
	ldr	pc, _vec_DataAbort
	ldr	pc, _vec_Reserved
	ldr	pc, _vec_IRQ
	ldr	pc, _vec_FIQ
_vec_Reset:		.word	_start
_vec_Undef:		.word	_hangup
_vec_SWI:		.word	_hangup
_vec_PrefAbort:	.word	_hangup
_vec_DataAbort:	.word	_hangup
_vec_Reserved:	.word	_hangup
_vec_IRQ:		.word	_IRQ_iterrupt
_vec_FIQ:		.word	_hangup
	.global  _initial_vector_end
_initial_vector_end:
	mov r0,r0
// "mov r0 r0" is only for keeping _initial_vector_end label
