/************************************************************************
 *	timer.s			
 *	 by Filippo Giuliani
 *
 *	Assembly code implementation of the kembed operating system.
 *	See main.s for details.
 *
 *	timer.s contains the rountines for manipulation of the timer.
 ************************************************************************/

/*
 * This function returns the BA of the System Timer
 * : void* GetSystemTimerBase
 */
	.globl GetSystemTimerBase
GetSystemTimerBase:	
	ldr r0,=0x20003000
	mov pc,lr


/*
 * This function returns the TimeStamp of the System Timer
 * : uint32_t GetTimeStamp (void *)
 */
	.globl GetTimeStamp
GetTimeStamp:
	push {lr}
	bl GetSystemTimerBase
	ldrd r0,r1,[r0,#4]
	pop {pc}
	
/*
 * This function waits for r0 us
 * : void uWaitFor (uint32_t microsec)
 */
	.globl uWaitFor
uWaitFor:
	push {r0,lr}
	bl GetSystemTimerBase
	push {r0}
	bl GetTimeStamp
	timeStamp .req r0
	timerBA .req r1
	microsec .req r2
	pop {timerBA,microsec}
	add timeStamp,microsec
	.unreq microsec
	str timeStamp,[timerBA,#0xC]	/* Load the comparator value */
	.unreq timeStamp
	status .req r0
loop1$:
	ldr status,[timerBA]
	and status,#1
	teq status,#0
	beq loop1$
	pop {pc}

/*
 * This function waits for r0 s and r1 us
 * : void WaitFor (timeval_t delay)
 */
	.globl WaitFor
WaitFor:
	push {r4,r5,lr}
	mov r4,r0
	mov r5,r1
uWaitFor1$:
	cmp r4,#0
	ldr r0,=1000000
	blhi uWaitFor
	sub r4,#1
	bhi uWaitFor1$
	cmp r5,#0
	mov r0,r5
	blhi uWaitFor
	pop {r4,r5,pc}
