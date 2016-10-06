/**
 *    C entry point.
 *    
 *    This file implement the C entry point of kembed. After first asm
 *    boot the system jump to _cstartup function. This function do the first
 *    initialization of the CPU.
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

/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/

#include <blib_types.h>

/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/

extern vuint32 __sBss;
extern vuint32 __eBss;
extern void kernel_main ( uint32 r0, uint32 r1, uint32 r2 );


/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void _cstartup (uint32 r0, uint32 r1, uint32 r2)
{
    vuint32* bss = &__sBss;
    vuint32* bss_end = &__eBss;

    while ( bss < bss_end )
	*bss++ = 0;

    kernel_main ( r0, r1, r2 );

    while (1);
}

void _exit ( int code )
{
    while (1)
	;
}


/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/
