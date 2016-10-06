/**
 *    Mailbox Device
 *    
 *    This file implement the Mailbox Handler.
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


/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/

#include <blib_types.h>
#include <baselib.h>
#include <device.h>
#include <dev_private.h>
#include <dev_font.h>


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/



/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/

static uint8* dev_frameBufferAddr = NULL;
static uint16 dev_fgColor;
static uint16 dev_fontColor;

static uint32 dev_cursorPositionX = 0U;
static uint32 dev_cursorPositionY = 0U;

/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/

static void drawPixel ( uint16 color, uint32 x, uint32 y);
static void drawHex (uint8 hex);    

/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void device_clearMonitor ( void)
{
    uint16* framebuffer = NULL;
    uint32 x,y;

    framebuffer = (uint16 *)dev_frameBufferAddr;

    for (y = 0U; y < 1050U; y++)
    {
	for (x = 0U; x < 1680U; x++)
	{
	    *framebuffer++ = dev_fgColor;
	}
    }

    dev_cursorPositionX = 0U;
    dev_cursorPositionY = 0U;
}

void device_initializeMonitor ( uint8* frameBufferAddr, uint16 fgColor, uint16 fontColor )
{
    dev_frameBufferAddr = frameBufferAddr;
    dev_fgColor = fgColor;
    dev_fontColor = fontColor;

    device_clearMonitor ();
}

void device_drawChar ( char character)
{
    if (character > 0 && character <= 0x1F )
    {
	switch (character)
	{
	case 0x8:
	    if (dev_cursorPositionX == 0)
	    {
		dev_cursorPositionX = 1680;
		dev_cursorPositionY -= 16;
	    }

	    dev_cursorPositionX -= 8;
	    device_drawChar (0);
	    
	    if (dev_cursorPositionX == 0)
	    {
		dev_cursorPositionX = 1680;
		dev_cursorPositionY -= 16;
	    }

	    dev_cursorPositionX -= 8;	    
	    break;

	case 0x9:
	    device_drawChar (0);
	    device_drawChar (0);
	    device_drawChar (0);
	    device_drawChar (0);	    
	    break;

	case 0xA: // LF
	    dev_cursorPositionX = 0;
	    dev_cursorPositionY += 16;	    
	    break;

	case 0xD:
	    dev_cursorPositionX = 0;	    
	    break;
	    
	default:
	    break;
	}
    }
    else if (character < 0x7F)
    {
	uint8 i, j, line;

	for (i = 0U; i < 16U; i++)
	{
	    line = dev_font[(uint8)character][i];

	    for (j = 0U; j < 8U; j++)
	    {
		if (line & 0x1)
		    drawPixel (dev_fontColor, dev_cursorPositionX + j, dev_cursorPositionY + i);
		else
		    drawPixel (dev_fgColor, dev_cursorPositionX + j, dev_cursorPositionY + i);
	    
		line = line >> 1;
	    }
	}
    
	dev_cursorPositionX += 8;

	if (dev_cursorPositionX + 8 >= 1680)
	{
	    dev_cursorPositionX = 0;
	    dev_cursorPositionY += 16;
	}
    }
}

void device_printLine ( char * string )
{
    while (*string != '\0')
	device_drawChar (*(string++));
}

void device_printNum ( uint32 num, format_t format)
{
    switch (format)
    {
    case FMT_DEC:
	if (num >= 10)
	{
	    device_printNum (num / 10, FMT_DEC);
	}
	device_drawChar ((num % 10) + 0x30);
	break;

    case FMT_0xHEX32:
	device_printLine ("0x");
	device_printNum (num, FMT_HEX32);
	break;
	
    case FMT_0xHEX16:
	device_printLine ("0x");
	device_printNum (num, FMT_HEX16);
	break;
	
    case FMT_0xHEX8:
	device_printLine ("0x");
	device_printNum (num, FMT_HEX8);
	break;
	
    case FMT_HEX32:
	drawHex ((num >> 28) & 0xF);
	drawHex ((num >> 24) & 0xF);
	drawHex ((num >> 20) & 0xF);
	drawHex ((num >> 16) & 0xF);
	drawHex ((num >> 12) & 0xF);
	drawHex ((num >> 8) & 0xF);
	drawHex ((num >> 4) & 0xF);
	drawHex (num & 0xF);
	break;
	
    case FMT_HEX16:
	drawHex ((num >> 12) & 0xF);
	drawHex ((num >> 8) & 0xF);
	drawHex ((num >> 4) & 0xF);
	drawHex (num & 0xF);
	break;
	
    case FMT_HEX8:
	drawHex ((num >> 4) & 0xF);
	drawHex (num & 0xF);
	break;

    case FMT_NULL:
	break;
    }
}


/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/

static void drawHex (uint8 hex)
{
    if (hex >= 10)
	device_drawChar (hex + 0x37);
    else
	device_drawChar (hex + 0x30);
}

static void drawPixel ( uint16 color, uint32 x, uint32 y)
{
    // FixMe!: Gestire la profondita di colore
    // FixMe!: Gestire il numero di colonne
    ((uint16 *)(dev_frameBufferAddr))[x + y * 1680] = color;
}
