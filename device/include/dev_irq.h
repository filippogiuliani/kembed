/**
 *    IRQ Device Library
 *    
 *    This is the header file for the IRQ Device.
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

#ifndef __DEV_IRQ_H
#define __DEV_IRQ_H


/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define DEV_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define DEV_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define DEV_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define DEV_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define DEV_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define DEV_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define DEV_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define DEV_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)

/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef struct {
    vuint32 IRQ_basic_pending;
    vuint32 IRQ_pending_1;
    vuint32 IRQ_pending_2;
    vuint32 FIQ_control;
    vuint32 Enable_IRQs_1;
    vuint32 Enable_IRQs_2;
    vuint32 Enable_Basic_IRQs;
    vuint32 Disable_IRQs_1;
    vuint32 Disable_IRQs_2;
    vuint32 Disable_Basic_IRQs;
} device_irq_controller_t;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function declaration                                        *****
 ******************************************************************************/

device_irq_controller_t* device_getIrqController( void );

#endif /* __DEV_IRQ_H */
