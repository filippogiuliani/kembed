/**
 *    IRQ Device Library
 *    
 *    This is the header file for the IRQ Device.
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

#ifndef __DEV_GPIO_H
#define __DEV_GPIO_H


/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef enum { GPIO_OFF = 0, GPIO_ON = 1 } device_gpio_state;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function declaration                                        *****
 ******************************************************************************/


sint32 device_gpioSetFunction ( const uint32 gpio, const uint32 function );
sint32 device_gpioSetValue ( const uint32 gpio, const device_gpio_state state );


#endif /* __DEV_GPIO_H */
