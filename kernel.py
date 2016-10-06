#!/usr/bin/python
#
#   Linker Script Generator
#   
#   This script generate the linker script to link kembed
#
#
#   $LastChangedDate: 2016-07-22 21:42:37 -0700 (Sat, 22 Jul 2006) $
#   $Revision: 144 $
#   $Author: filippogiuliani $
#   $Id: makefile 148 2006-07-28 21:30:43Z sally $
#
#
#   (C) Copyright 2016 Filippo Giuliani <mail@filippogiuliani.it>
#
#   This file is part of kembed.
#
#   kembed is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   kembed is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with kembed.  If not, see <http://www.gnu.org/licenses/>.


import sys

print ('/**                                                                            \n' 
       ' *    Linker Script for kembed                                                 \n'
       ' *                                                                             \n'
       ' *    This is the linker script to link kembed system. This file is auto       \n'
       ' *    generate by kernel.py (invoked by the makefile).                         \n'
       ' *                                                                             \n'
       ' *                                                                             \n'
       ' *    $LastChangedDate: 2016-07-22 21:42:37 -0700 (Sat, 22 Jul 2006) $         \n'
       ' *    $Revision: 144 $                                                         \n'
       ' *    $Author: harry $                                                         \n'
       ' *    $Id: calc.c 148 2006-07-28 21:30:43Z sally $                             \n'
       ' *                                                                             \n'
       ' *                                                                             \n'
       ' *    (C) Copyright 2016 Filippo Giuliani <mail@filippogiuliani.it>            \n'
       ' *                                                                             \n'
       ' *    This file is part of kembed.                                             \n'
       ' *                                                                             \n'
       ' *    kembed is free software: you can redistribute it and/or modify           \n'
       ' *    it under the terms of the GNU General Public License as published by     \n'
       ' *    the Free Software Foundation, either version 3 of the License, or        \n'
       ' *    (at your option) any later version.                                      \n'
       ' *                                                                             \n'
       ' *    kembed is distributed in the hope that it will be useful,                \n'
       ' *    but WITHOUT ANY WARRANTY; without even the implied warranty of           \n'
       ' *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            \n'
       ' *    GNU General Public License for more details.                             \n'
       ' *                                                                             \n'
       ' *    You should have received a copy of the GNU General Public License        \n'
       ' *    along with kembed.  If not, see <http://www.gnu.org/licenses/>.          \n'
       ' */                                                                            \n'
       '                                                                               \n'
       '                                                                               \n'
       'OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",                               \n'
       '          "elf32-littlearm")                                                   \n'
       '                                                                               \n'
       'OUTPUT_ARCH(arm)                                                               \n'
       '                                                                               \n'
       'ENTRY(_start)                                                                  \n'
       '                                                                               \n'
       'SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");   \n'
       '                                                                               \n'
       'ENTRYPOINT = 0x8000;                                                           \n'
       '                                                                               \n'
       'SECTIONS {                                                                     \n'
       '	/*                                                                     \n'
       '	* First and formost we need the .text.startup section, containing the  \n'
       '	* code to be run first. We allow room for the ATAGs and stack and      \n'
       '	* conform to the bootloader\'s expectation by putting this code at     \n'
       '	* 0x8000.                                                              \n'
       '	*/                                                                     \n'
       '	. = ENTRYPOINT;                                                        \n'
       '	__sCode = .;                                                           \n'
       '	.init :                                                                \n'
       '	{                                                                      \n'
       '		*(.init)                                                       \n'
       '	}                                                                      \n');


di="obj/"
alignmodule=sys.argv[1]
alignsection=sys.argv[2]

def element ( name, lista ):
    mname = name[0].upper() + name[1:];
    print ('	__s' + mname + ' = .;                                                  \n'
           '	.' + name + ' :                                                        \n'
           '	{                                                                      \n');

    if name == "bss":
        name = "bss* COMMON"
    elif name == "text":
        name = "text*"
    elif name == "rodata":
        name = "rodata*"
        
    for el in lista:
           elmname = el[0].upper() + el[1:];
           print ('		__s' + elmname + mname + ' = .;                        \n'
                  '		' + el + '/' + di + el + '.o(.' + name + ');            \n'
                  '		. += __s' + elmname + mname + ' == . ? ' + alignmodule + ' : 0x0;\n'
                  '		. = ALIGN (' + alignmodule + ');                       \n'
                  '		__e' + elmname + mname + ' = .;                        \n');
    print ('	}                                                                      \n'
           '	__e' + mname + ' = .;                                                  \n'
           '	. = ALIGN (' + alignsection + ');                                      \n');
    return


element ( "text", sys.argv[3:]);
element ( "data", sys.argv[3:]);
element ( "rodata", sys.argv[3:]);
element ( "bss", sys.argv[3:]);


print ('	. = ALIGN(32 / 8);                                                     \n'
       '	. = ALIGN(32 / 8);                                                     \n'
       '                                                                               \n'
       '	__eCode = .;                                                           \n'
       '                                                                               \n'
       '	.stack         0x80000 :                                               \n'
       '	{                                                                      \n'
       '		_stack = .;                                                    \n'
       '		*(.stack)                                                      \n'
       '	}                                                                      \n'
       '                                                                               \n'
       '	/*                                                                     \n'
       '	* Finally comes everything else. A fun trick here is to put all other  \n'
       '	* sections into this section, which will be discarded by default.      \n'
       '	*/                                                                     \n'
       '	/DISCARD/ : {                                                          \n'
       '		*(*)                                                           \n'
       '	}                                                                      \n'
       '}                                                                              \n');
