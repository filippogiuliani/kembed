#!/usr/bin/python

import sys

print ('/******************************************************************************\n'
       '*	kernel.ld                                                              \n'
       '*	 by Filippo Giuliani                                                   \n'
       '*                                                                              \n'
       '*	A linker script for generation of raspberry pi kernel images.          \n'
       '******************************************************************************/\n'
       'OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",                               \n'
       '          "elf32-littlearm")                                                   \n'
       'OUTPUT_ARCH(arm)                                                               \n'
       'ENTRY(_start)                                                                  \n'
       'SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");   \n'
       'ENTRYPOINT = 0x8000;                                                           \n'
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


index = range(3, len(sys.argv))

di=sys.argv[1]
alignmodule=sys.argv[2]
alignsection=sys.argv[3]

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
                  '		' + el + '/' + di + el + '.o(.' + name + ')            \n'
                  '		. = ALIGN (' + alignmodule + ');                       \n'
                  '		__e' + elmname + mname + ' = .;                        \n');
    print ('	}                                                                      \n'
           '	__e' + mname + ' = .;                                                  \n'
           '	. = ALIGN (' + alignsection + ');                                      \n');
    return


element ( "text", sys.argv[4:]);
element ( "data", sys.argv[4:]);
element ( "rodata", sys.argv[4:]);
element ( "bss", sys.argv[4:]);


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
