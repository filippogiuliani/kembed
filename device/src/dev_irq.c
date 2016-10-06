/**
 *    IRQ Device
 *    
 *    This file implement the entry point of the irq.
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

#define DEV_INTERRUPT_CONTROLLER_BASE   ( DEV_PERIPHERAL_BASE + 0xB200 )

/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/

static device_irq_controller_t* device_IRQController =
    (device_irq_controller_t*)DEV_INTERRUPT_CONTROLLER_BASE;


/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void __attribute__((interrupt("ABORT"))) reset_vector(void)
{
    DPRINT("ABORT HANDLER\n");
}

void __attribute__((interrupt("UNDEF"))) _undefined_instruction_vector(void)
{
    DPRINT("UNDEFINED INSTRUCTION HANDLER\n");
    while( 1 )
    {
        /* Do Nothing! */
    }
}


void __attribute__((interrupt("SWI"))) _software_interrupt_vector(void)
{
    DPRINT("SOFTWARE INTERRUPT HANDLER");
    while( 1 )
    {
        /* Do Nothing! */
    }
}


void __attribute__((interrupt("ABORT"))) _prefetch_abort_vector(void)
{
    DPRINT("PREFETCH ABORT HANDLER\n");
}


void __attribute__((interrupt("ABORT"))) _data_abort_vector(void)
{
    DPRINT("DATA ABORT HANDLER\n");
}


void __attribute__((interrupt("IRQ"))) _interrupt_vector(void)
{
    static sint32 lit = 0;

    /* Clear the ARM Timer interrupt - it's the only interrupt we have
       enabled, so we want don't have to work out which interrupt source
       caused us to interrupt */
    device_getArmTimer()->IRQClear = 1;

    /* Flip the LED */
    if( lit )
    {
	device_gpioSetValue ( 47U, GPIO_ON );
	lit = 0;
    }
    else
    {
	device_gpioSetValue ( 47U, GPIO_OFF );
	lit = 1;
    }
}



void __attribute__((interrupt("FIQ"))) _fast_interrupt_vector(void)
{
    DPRINT("FIQ INTERRUPT HANDLER\n");
}


device_irq_controller_t* device_getIrqController( void )
{
    return device_IRQController;
}


/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/



