/**
 *    Kernel Main
 *    
 *    This file implement the main part of the kernel such as:
 *        - scheduler
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
#include <blib_utils.h>
#include <device.h>
#include <kernel.h>

/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define SCREEN_WIDTH    1680
#define SCREEN_HEIGHT   1050
#define SCREEN_DEPTH    16      /* 16 or 32-bit */

#define COLOUR_DELTA    0.05    /* Float from 0 to 1 incremented by this amount */


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef struct {
    float r;
    float g;
    float b;
    float a;
    } colour_t;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/

extern void _enable_interrupts ( void);


/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void kernel_main ( uint32 r0, uint32 r1, uint32 r2 )
{
    device_mailbox_property_t* mp;

    device_propertyInit();
    device_propertyAddTag( DEV_TAG_GET_BOARD_MODEL );
    device_propertyAddTag( DEV_TAG_GET_BOARD_REVISION );
    device_propertyAddTag( DEV_TAG_GET_FIRMWARE_VERSION );
    device_propertyAddTag( DEV_TAG_GET_BOARD_MAC_ADDRESS );
    device_propertyAddTag( DEV_TAG_GET_BOARD_SERIAL );
    // OK
    device_propertyAddTag( DEV_TAG_ALLOCATE_BUFFER );
    device_propertyAddTag( DEV_TAG_SET_PHYSICAL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT );
    device_propertyAddTag( DEV_TAG_SET_VIRTUAL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT * 2 );
    device_propertyAddTag( DEV_TAG_SET_DEPTH, SCREEN_DEPTH );
    device_propertyAddTag( DEV_TAG_GET_PITCH );
    device_propertyAddTag( DEV_TAG_GET_PHYSICAL_SIZE );
    device_propertyAddTag( DEV_TAG_GET_DEPTH );
    device_propertyProcess();

    mp = device_propertyGet( DEV_TAG_ALLOCATE_BUFFER );
    
    device_initializeMonitor ( (uint8*)(mp->buffer[0]), 0x1111, 0xCCCC );

    DPRINT ("Enter main..\n");

    device_gpioSetFunction ( 47U, 1U );

    device_getIrqController ()->Enable_Basic_IRQs = DEV_BASIC_ARM_TIMER_IRQ;

    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    device_getArmTimer ()->Load = 0x400;

    /* Setup the ARM Timer */
    device_getArmTimer ()->Control =
	DEV_ARMTIMER_CTRL_23BIT |
	DEV_ARMTIMER_CTRL_ENABLE |
	DEV_ARMTIMER_CTRL_INT_ENABLE |
	DEV_ARMTIMER_CTRL_PRESCALE_256;

    DPRINT ("Enabling Interrupts..\n");
    _enable_interrupts ();

    mp = device_propertyGet( DEV_TAG_GET_BOARD_MODEL );

    DPRINT ( "Board Model: ");

    if( mp )
	DPRINTNUM ( mp->buffer[0], FMT_DEC );
    else
        DPRINT ( "NULL" );

    DPRINT ("\r\n");

    mp = device_propertyGet( DEV_TAG_GET_BOARD_REVISION );

    DPRINT ( "Board Revision: ");

    if( mp )
	DPRINTNUM ( mp->buffer[0], FMT_HEX32 );
    else
        DPRINT ( "NULL" );

    DPRINT ("\r\n");

    mp = device_propertyGet( DEV_TAG_GET_FIRMWARE_VERSION );

    DPRINT ( "Firmware Version: ");

    if( mp )
	DPRINTNUM ( mp->buffer[0], FMT_HEX32 );
    else
        DPRINT ( "NULL" );

    DPRINT ("\r\n");

    mp = device_propertyGet( DEV_TAG_GET_BOARD_MAC_ADDRESS );

    DPRINT ( "MAC Address: ");

    if( mp )
    {	
    	DPRINTNUM ( mp->buffer[0] & 0xFF, FMT_HEX8 );
    	DPRINT( ":" );
    	DPRINTNUM ( (mp->buffer[0] >> 8) & 0xFF, FMT_HEX8 );
    	DPRINT( ":" );
    	DPRINTNUM ( (mp->buffer[0] >> 16) & 0xFF, FMT_HEX8 );
    	DPRINT( ":" );
    	DPRINTNUM ( (mp->buffer[0] >> 24) & 0xFF, FMT_HEX8 );
    	DPRINT( ":" );
    	DPRINTNUM ( mp->buffer[1] & 0xFF, FMT_HEX8 );
    	DPRINT( ":" );
    	DPRINTNUM ( (mp->buffer[2] >> 8) & 0xFF, FMT_HEX8 );
    }
    else
        DPRINT ( "NULL" );

    DPRINT ("\r\n");

    mp = device_propertyGet( DEV_TAG_GET_BOARD_SERIAL );

    DPRINT ( "Serial Number: ");

    if( mp )
    {
	DPRINTNUM ( mp->buffer[0], FMT_HEX32 );
	DPRINTNUM ( mp->buffer[1], FMT_HEX32 );
    }
    else
        DPRINT ( "NULL" );

    DPRINT ("\r\n");

    device_printLine ("Hello World!\n");
    
    while (1U);
}


/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/
