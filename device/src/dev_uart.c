/**
 *    ARM Timer Device
 *    
 *    This file implement the ARM Timer Handler.
 *
 *
 *    File:       <FILE>
 *    Author:     <AUTHORNAME>
 *    Mail:       <AUTHORMAIL>
 *    Date:       <COMMITTERDATEISO8601>
 *    Ident:      <COMMITHASH>
 *    Branch:     <BRANCH>
 *
 *    <CHANGELOG:--reverse --grep "^tags.*relevant":-1:%an : %ai : %s>
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
#include <baselib.h>
#include <device.h>
#include <dev_private.h>


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define DEV_UART0_BASE    ( 0x101f1000 )


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/

volatile unsigned int * const UART0DR = (unsigned int *)DEV_UART0_BASE;

/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/


void device_print_uart0
(
    const char *s
    )
{
    while(*s != '\0')
    {
	/* Loop until end of string */
	*UART0DR = (unsigned int)(*s); /* Transmit char */
	s++; /* Next char */
    }
}

/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/
