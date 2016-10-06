/**
 *    Entry point
 *    
 *    This file implement the entry point of the system. The symbol _start
 *    will be placed in the entry point by the linker script. After the
 *    interrupt initialization, the software jump to _cstartup function.
 *
 *
 *    @file:      $File$
 *    @author:    $Author$
 *    @date:      $Date$
 *    @version:   $Revision$
 *
 *    $Id$
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
