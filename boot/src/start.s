.section .init
.globl _start

_start:
	// Set the stack pointer, which progresses downwards through memory
        ldr   pc, [pc, #24] // =_reset_h
        ldr   pc, [pc, #24] // =_undefined_instruction_vector_h
        ldr   pc, [pc, #24] // =_software_interrupt_vector_h
        ldr   pc, [pc, #24] // =_prefetch_abort_vector_h
        ldr   pc, [pc, #24] // =_data_abort_vector_h
        ldr   pc, [pc, #24] // =_unused_handler_h
        ldr   pc, [pc, #24] // =_interrupt_vector_h
        ldr   pc, [pc, #24] // =_fast_interrupt_vector_h

_reset_h:                       	.word   _reset    
_undefined_instruction_vector_h:	.word   _undefined_instruction_vector	
_software_interrupt_vector_h:		.word   _software_interrupt_vector	
_prefetch_abort_vector_h:		.word   _prefetch_abort_vector
_data_abort_vector_h:			.word   _data_abort_vector
_unused_handler_h:			.word	_unused_handler_h
_interrupt_vector_h:			.word   _interrupt_vector		
_fast_interrupt_vector_h:		.word   _fast_interrupt_vector

	
_reset:
	mov   r0,#0x8000
	mov   r1,#0x0000
	ldmia r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
	stmia r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
	ldmia r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
	stmia r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
	
	ldr   sp, =(64 * 1024 * 1024)

	// This function should not return
	b     _cstartup

	
loop$:
	b     loop$
