.section .text
.globl _get_stack_pointer	
.globl _enable_interrupts

_get_stack_pointer:
	// Return the stack pointer value
	str   sp,[sp]
	ldr   r0,[sp]

	// Return from the function
	mov   pc,lr

_enable_interrupts:
	mrs   r0, cpsr
	bic   r0, r0, #0x80
	msr   cpsr_c, r0

	mov   pc, lr

