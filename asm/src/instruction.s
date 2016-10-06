/**
 *    asm instruction
 *    
 *    This file implement all the asm function needed by the kernel
 *
 *
 *    $LastChangedDate: 2016-07-22 21:42:37 -0700 (Sat, 22 Jul 2006) $
 *    $Revision: 144 $
 *    $Author: harry $
 *    $Id: calc.c 148 2006-07-28 21:30:43Z sally $
 *
 *
 *    (C) Copyright 2016 Filippo Giuliani <mail@filippogiuliani.it>
 *
 *    This file is part of kembed.
 *
 *    kembed is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    kembed is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with kembed.  If not, see <http://www.gnu.org/licenses/>.
 */
	
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

