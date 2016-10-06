/**
 *    Baselib Utils Library
 *    
 *    This is the header file for the utils library.
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


#ifndef __BLIB_UTILS_H
#define __BLIB_UTILS_H


/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#ifdef DEBUG

#define DPRINT(args)           (device_printLine (args))
#define DPRINTNUM(arg, format) (device_printNum (arg, format))

#else

#define DPRINT(args)
#define DPRINTNUM(arg, format)

#endif


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function declaration                                        *****
 ******************************************************************************/


void blib_uwait( uint32 us );
uint32 blib_memcpy ( void * destination, const void * source, const uint32 size );


#endif /* __BLIB_UTILS_H */
