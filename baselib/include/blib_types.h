/**
 *    Baselib Types Library
 *    
 *    This file implement the basic types used by kembed.
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


#ifndef __BLIB_TYPES_H
#define __BLIB_TYPES_H


/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define ASSERT(cond)				\
    do {					\
	if (!(cond))				\
	    return -1;				\
    } while (0);
    

#define NULL      ((void*)(0x0))

/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/

typedef enum { FALSE = 0, TRUE = 1 } bool;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef signed int sint32;
typedef signed short sint16;
typedef signed char sint8;

typedef volatile unsigned int vuint32;
typedef volatile unsigned short vuint16;
typedef volatile unsigned char vuint8;

typedef volatile signed int vsint32;
typedef volatile signed short vsint16;
typedef volatile signed char vsint8;

typedef enum
{
    FMT_DEC,
    FMT_0xHEX32,
    FMT_0xHEX16,
    FMT_0xHEX8,
    FMT_HEX32,
    FMT_HEX16,
    FMT_HEX8,
    FMT_NULL
} format_t;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/******************************************************************************
 ***** Public function declaration                                        *****
 ******************************************************************************/


#endif /* __BLIB_TYPES_H */
