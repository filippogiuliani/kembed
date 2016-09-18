/************************************************************************
 *	gpio.s			
 *	 by Filippo Giuliani
 *
 *	Assembly code implementation of the kembed operating system.
 *	See main.s for details.
 *
 *	gpio.s contains the rountines for manipulation of the GPIO ports.
 ************************************************************************/

/*
 * This function returns the base address of the GPIO Controller as a physical address
 * in register r0
 * : void* GetGpioAddress ()
 */
.globl GetGpioAddress
GetGpioAddress:
	ldr r0,=0x20200000
	mov pc,lr


/* 
 * This function sets the function of the GPIO register address by r0 to the low 3 bits
 * of r1.
 * : void SetGpioFunction (uint32_t gpioRegister, uint32_t function)
 */
.globl SetGpioFunction
SetGpioFunction:
	cmp r0,#53 		/* Check the gpioRegister                             */
	cmpls r1,#7		/* Check the function                                 */
	movhi pc,lr		/* Return if one or both the input are invalid	      */
	push {r0,r1,lr}		/* Push the var into the stack			      */
	bl GetGpioAddress	/* Get the GPIO Controller physical base address      */
	mov r2,r0		/* Save the result				      */
	pop {r0,r1}		/* Pop the var from the stack			      */
functionLoop$:			/* Get the register address (the GPIO functions are   */
	cmp r0,#9		/* stored in blocks of 10)                            */
	subhi r0,#10
	addhi r2,#4
	bhi functionLoop$
	add r0,r0,lsl #1	/* Multiply r0 by 3                                   */
	lsl r1,r0		/* Shift the function to his position in the register */
	bitMask .req r3		/* Prepare a bitmask to write correctly the register  */
	mov bitMask,#7
	lsl bitMask,r0
	mvns bitMask,bitMask
	ldr r0,[r2]		/* Get the function register value		      */
	and r0,bitMask		/* Clean the function for the gpioRegister from the   */
				/* register value				      */
	orr r1,r0		/* Insert the function for the gpioRegister in the    */
				/* register value				      */
	str r1,[r2]		/* Write the function register			      */
	pop {pc}		/* Return                                             */


/* 	
 *  This function sets a the GPIO number r0 at the value of r1
 *  : void SetGpio (uint32_t pinNum, uint32_t pinVal)
*/
.globl SetGpio
SetGpio:
	pinNum .req r0
	pinVal .req r1
	cmp pinNum,#53		/* Check the pinNum                                   */
	movhi pc,lr		/* Return if the pinNum is invalid		      */
	push {pinNum,pinVal,lr} /* Push the var into the stack			      */
	.unreq pinNum
	.unreq pinVal
	bl GetGpioAddress	/* Get the GPIO Controller physical base address      */
	pinNum .req r1
	pinVal .req r2
	gpioAddr .req r0
	pinBank .req r3	
	pop {pinNum,pinVal} 	/* Pop the var from the stack			      */
	lsr pinBank,pinNum,#5	/* Divide the pin number by 32			      */
	lsl pinBank,#2		/* Multiply by 4 (to be addedd to the address)	      */
	add gpioAddr,pinBank
	.unreq pinBank
	and pinNum,#31
	setBit .req r3
	mov setBit,#1
	lsl setBit,pinNum
	.unreq pinNum
	teq pinVal,#0          	/* test equal					      */
	.unreq pinVal
	streq setBit,[gpioAddr,#40] 	/* Store to 40 if pinVal is equal to zero     */
	strne setBit,[gpioAddr,#28] 	/* Store to 28 if pinVal is not equal to zero */
	.unreq setBit
	.unreq gpioAddr
	pop {pc}		/* return                                             */
