/**
 *    Baselib Utils
 *    
 *    This file implement the utils functionality of the baselib module 
 *    such as:
 *      - time
 *      - memory
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
#include <blib_utils.h>


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define RPI_SYSTIMER_BASE (0x20003000)


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef struct
{
    vuint32 control_status;
    vuint32 counter_lo;
    vuint32 counter_hi;
    vuint32 compare0;
    vuint32 compare1;
    vuint32 compare2;
    vuint32 compare3;
} rpi_sys_timer_t;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/

static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;

/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void blib_uwait ( uint32 us )
{
    vuint32 ts = rpiSystemTimer->counter_lo;

    while( ( rpiSystemTimer->counter_lo - ts ) < us )
    {
        /* BLANK */
    }
}


uint32 blib_memcpy ( void * destination, const void * source, const uint32 size )
{
    ASSERT (destination != NULL && source != NULL);
    
    uint32 i;
    uint8* __dst = (uint8 *)destination;
    uint8* __src = (uint8 *)source;

    for (i = 0U; i < size; i++)
	*__dst++ = *__src++;

    return 0;
}

/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/

