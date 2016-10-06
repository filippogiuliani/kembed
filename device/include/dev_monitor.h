/**
 *    Monitor Device Library
 *    
 *    This is the header file for the Monitor Device.
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

#ifndef __DEV_MONITOR_H
#define __DEV_MONITOR_H

/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/



/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/



/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void device_clearMonitor ( void);
void device_initializeMonitor ( uint8* frameBufferAddr, uint16 fgColor, uint16 fontColor );
void device_drawChar ( char character);
void device_printLine ( char * string );
void device_printNum ( uint32 num, format_t format);

#endif /* __DEV_MONITOR_H */
