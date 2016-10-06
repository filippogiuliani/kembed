/**
 *    ARM Timer Device Library
 *    
 *    This is the header file for the ARM Timer Device.
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

#ifndef __DEV_ARMTIMER_H
#define __DEV_ARMTIMER_H


/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/

/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define DEV_ARMTIMER_CTRL_23BIT         ( 1 << 1 )

#define DEV_ARMTIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define DEV_ARMTIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define DEV_ARMTIMER_CTRL_PRESCALE_256  ( 2 << 2 )

#define DEV_ARMTIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define DEV_ARMTIMER_CTRL_INT_DISABLE   ( 0 << 5 )

#define DEV_ARMTIMER_CTRL_ENABLE        ( 1 << 7 )
#define DEV_ARMTIMER_CTRL_DISABLE       ( 0 << 7 )


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef struct {
    vuint32 Load;
    vuint32 Value;
    vuint32 Control;
    vuint32 IRQClear;
    vuint32 RAWIRQ;
    vuint32 MaskedIRQ;
    vuint32 Reload;
    vuint32 PreDivider;
    vuint32 FreeRunningCounter;
} device_arm_timer_t;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function declaration                                        *****
 ******************************************************************************/

device_arm_timer_t* device_getArmTimer(void);

#endif /* __DEV_ARMTIMER_H */
