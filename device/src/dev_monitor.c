

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

void device_printLine ( char * string )
{
    while (*string != '\0')
	device_drawChar (*(string++));
}


static void drawPixel ( uint16 color, uint32 x, uint32 y)
{
    // FixMe!: Gestire la profondita di colore
    // FixMe!: Gestire il numero di colonne
    ((uint16 *)(dev_frameBufferAddr))[x + y * 1680] = color;
}
