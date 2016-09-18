.section .init
.globl _start
_start:
	mov sp,#0x8000		/* Set the stack pointer                   */
	b main			/* Branch to main                          */


.section .text
/*
 * Main functions: Blink a LED
 */
main:
	pinNum .req r0		/* Configure the GPIO Function for GPIO 15 */
	pinFunc .req r1
	mov pinNum,#47
	mov pinFunc,#1
	bl SetGpioFunction
	.unreq pinNum
	.unreq pinFunc
loop:
	pinNum .req r0		/* Set on the LED                          */
	pinVal .req r1
	mov pinNum,#47
	mov pinVal,#0
	bl SetGpio
	.unreq pinNum
	.unreq pinVal
	microsec .req r0	/* Wait for some time                      */
	ldr microsec,=1000000
	bl uWaitFor
	.unreq microsec
	pinNum .req r0		/* Set on the LED                          */
	pinVal .req r1
	mov pinNum,#47
	mov pinVal,#1
	bl SetGpio
	.unreq pinNum
	.unreq pinVal
	microsec .req r0	/* Wait for some time                      */
	ldr microsec,=1000000
	bl uWaitFor
	.unreq microsec
	b loop

/*
 * This function loop for r0 cycles
 * : void wait$ (uint32_t cycles)
 */
wait$:
	cycles .req r0
	sub cycles,#1
	cmp cycles,#0
	bne wait$
	mov pc,lr
