/**
 *    ARM Timer Device
 *    
 *    This file implement the ARM Timer Handler.
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
#include <device.h>
#include <dev_private.h>

/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define DEV_ARMTIMER_BASE               ( DEV_PERIPHERAL_BASE + 0xB400 )


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/

static device_arm_timer_t* dev_rpiArmTimer = (device_arm_timer_t*)DEV_ARMTIMER_BASE;

/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

device_arm_timer_t* device_getArmTimer(void)
{
    return dev_rpiArmTimer;
}

/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/
