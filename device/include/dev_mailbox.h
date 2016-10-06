/**
 *    Mailbox Device Library
 *    
 *    This is the header file for the Mailbox Device.
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

#ifndef __DEV_MAILBOX_H
#define __DEV_MAILBOX_H

/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/

#include <stdarg.h>

/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef enum
{
    /* Videocore */
    DEV_TAG_GET_FIRMWARE_VERSION = 0x1,

    /* Hardware */
    DEV_TAG_GET_BOARD_MODEL = 0x10001,
    DEV_TAG_GET_BOARD_REVISION,
    DEV_TAG_GET_BOARD_MAC_ADDRESS,
    DEV_TAG_GET_BOARD_SERIAL,
    DEV_TAG_GET_ARM_MEMORY,
    DEV_TAG_GET_VC_MEMORY,
    DEV_TAG_GET_CLOCKS,

    /* Config */
    DEV_TAG_GET_COMMAND_LINE = 0x50001,

    /* Shared resource management */
    DEV_TAG_GET_DMA_CHANNELS = 0x60001,

    /* Power */
    DEV_TAG_GET_POWER_STATE = 0x20001,
    DEV_TAG_GET_TIMING,
    DEV_TAG_SET_POWER_STATE = 0x28001,

    /* Clocks */
    DEV_TAG_GET_CLOCK_STATE = 0x30001,
    DEV_TAG_SET_CLOCK_STATE = 0x38001,
    DEV_TAG_GET_CLOCK_RATE = 0x30002,
    DEV_TAG_SET_CLOCK_RATE = 0x38002,
    DEV_TAG_GET_MAX_CLOCK_RATE = 0x30004,
    DEV_TAG_GET_MIN_CLOCK_RATE = 0x30007,
    DEV_TAG_GET_TURBO = 0x30009,
    DEV_TAG_SET_TURBO = 0x38009,

    /* Voltage */
    DEV_TAG_GET_VOLTAGE = 0x30003,
    DEV_TAG_SET_VOLTAGE = 0x38003,
    DEV_TAG_GET_MAX_VOLTAGE = 0x30005,
    DEV_TAG_GET_MIN_VOLTAGE = 0x30008,
    DEV_TAG_GET_TEMPERATURE = 0x30006,
    DEV_TAG_GET_MAX_TEMPERATURE = 0x3000A,
    DEV_TAG_ALLOCATE_MEMORY = 0x3000C,
    DEV_TAG_LOCK_MEMORY = 0x3000D,
    DEV_TAG_UNLOCK_MEMORY = 0x3000E,
    DEV_TAG_RELEASE_MEMORY = 0x3000F,
    DEV_TAG_EXECUTE_CODE = 0x30010,
    DEV_TAG_GET_DISPMANX_MEM_HANDLE = 0x30014,
    DEV_TAG_GET_EDID_BLOCK = 0x30020,

    /* Framebuffer */
    DEV_TAG_ALLOCATE_BUFFER = 0x40001,
    DEV_TAG_RELEASE_BUFFER = 0x48001,
    DEV_TAG_BLANK_SCREEN = 0x40002,
    DEV_TAG_GET_PHYSICAL_SIZE = 0x40003,
    DEV_TAG_TEST_PHYSICAL_SIZE = 0x44003,
    DEV_TAG_SET_PHYSICAL_SIZE = 0x48003,
    DEV_TAG_GET_VIRTUAL_SIZE = 0x40004,
    DEV_TAG_TEST_VIRTUAL_SIZE = 0x44004,
    DEV_TAG_SET_VIRTUAL_SIZE = 0x48004,
    DEV_TAG_GET_DEPTH = 0x40005,
    DEV_TAG_TEST_DEPTH = 0x44005,
    DEV_TAG_SET_DEPTH = 0x48005,
    DEV_TAG_GET_PIXEL_ORDER = 0x40006,
    DEV_TAG_TEST_PIXEL_ORDER = 0x44006,
    DEV_TAG_SET_PIXEL_ORDER = 0x48006,
    DEV_TAG_GET_ALPHA_MODE = 0x40007,
    DEV_TAG_TEST_ALPHA_MODE = 0x44007,
    DEV_TAG_SET_ALPHA_MODE = 0x48007,
    DEV_TAG_GET_PITCH = 0x40008,
    DEV_TAG_GET_VIRTUAL_OFFSET = 0x40009,
    DEV_TAG_TEST_VIRTUAL_OFFSET = 0x44009,
    DEV_TAG_SET_VIRTUAL_OFFSET = 0x48009,
    DEV_TAG_GET_OVERSCAN = 0x4000A,
    DEV_TAG_TEST_OVERSCAN = 0x4400A,
    DEV_TAG_SET_OVERSCAN = 0x4800A,
    DEV_TAG_GET_PALETTE = 0x4000B,
    DEV_TAG_TEST_PALETTE = 0x4400B,
    DEV_TAG_SET_PALETTE = 0x4800B,
    DEV_TAG_SET_CURSOR_INFO = 0x8010,
    DEV_TAG_SET_CURSOR_STATE = 0x8011
} device_mailbox_tag_t;


typedef struct
{
    sint32 tag;
    sint32 bufferLength;
    sint32 valueLength;
    sint32 indicator;
    uint32 buffer[256];
} device_mailbox_property_t;



/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void device_propertyInit( void );
void device_propertyAddTag( device_mailbox_tag_t tag, ... );
sint32 device_propertyProcess( void );
device_mailbox_property_t* device_propertyGet( device_mailbox_tag_t tag );


#endif /* __DEV_MAILBOX_H */
