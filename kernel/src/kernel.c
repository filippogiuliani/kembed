
#include <blib_types.h>
#include <blib_utils.h>
#include <device.h>
#include <kernel.h>

extern void _enable_interrupts ( void);

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_DEPTH    16      /* 16 or 32-bit */

#define COLOUR_DELTA    0.05    /* Float from 0 to 1 incremented by this amount */

typedef struct {
    float r;
    float g;
    float b;
    float a;
    } colour_t;


void kernel_main ( uint32 r0, uint32 r1, uint32 r2 )
{
    device_mailbox_property_t* mp;
    uint32 width = 0U, height = 0U, bpp = 0U, pitch = 0U;
    unsigned char* fb = NULL;
    colour_t current_colour;
    uint32 pixel_offset, x, y;
    uint32 r, g, b, a;
    float cd = COLOUR_DELTA;
    /* uint32 frame_count = 0; */
    /* vuint32 calculate_frame_count; */

    DPRINT ("Enter main.. \n");

    device_gpioSetFunction ( 47U, 1U );

    device_getIrqController ()->Enable_Basic_IRQs = DEV_BASIC_ARM_TIMER_IRQ;

    /* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    device_getArmTimer ()->Load = 0x400;

    /* Setup the ARM Timer */
    device_getArmTimer ()->Control =
	DEV_ARMTIMER_CTRL_23BIT |
	DEV_ARMTIMER_CTRL_ENABLE |
	DEV_ARMTIMER_CTRL_INT_ENABLE |
	DEV_ARMTIMER_CTRL_PRESCALE_256;

    DPRINT ("Enabling Interrupts..");
    _enable_interrupts ();

    while (1U);
    
    /* Initialise a framebuffer... */
    DPRINT ("Initialize Mailbox..");
    device_propertyInit();
    device_propertyAddTag( DEV_TAG_ALLOCATE_BUFFER );
    device_propertyAddTag( DEV_TAG_SET_PHYSICAL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT );
    device_propertyAddTag( DEV_TAG_SET_VIRTUAL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT * 2 );
    device_propertyAddTag( DEV_TAG_SET_DEPTH, SCREEN_DEPTH );
    device_propertyAddTag( DEV_TAG_GET_PITCH );
    device_propertyAddTag( DEV_TAG_GET_PHYSICAL_SIZE );
    device_propertyAddTag( DEV_TAG_GET_DEPTH );
    device_propertyProcess();

    if( ( mp = device_propertyGet( DEV_TAG_GET_PHYSICAL_SIZE ) ) )
    {
        width = mp->data.buffer_32[0];
        height = mp->data.buffer_32[1];

        /* printf( "Initialised Framebuffer: %dx%d ", width, height ); */
    }

    if( ( mp = device_propertyGet( DEV_TAG_GET_DEPTH ) ) )
    {
        bpp = mp->data.buffer_32[0];
        /* printf( "%dbpp\r\n", bpp ); */
    }

    if( ( mp = device_propertyGet( DEV_TAG_GET_PITCH ) ) )
    {
        pitch = mp->data.buffer_32[0];
        /* printf( "Pitch: %d bytes\r\n", pitch ); */
    }

    if( ( mp = device_propertyGet( DEV_TAG_ALLOCATE_BUFFER ) ) )
    {
        fb = (unsigned char*)mp->data.buffer_32[0];
        /* printf( "Framebuffer address: %8.8X\r\n", (unsigned int)fb ); */
    }

    /* Never exit as there is no OS to exit to! */
    current_colour.r = 0;
    current_colour.g = 0;
    current_colour.b = 0;
    current_colour.a = 1.0;

    while( 1 )
    {
        current_colour.r = 0;

        /* Produce a colour spread across the screen */
        for( y = 0; y < height; y++ )
        {
            current_colour.r += ( 1.0 / height );
            current_colour.b = 0;

            for( x = 0; x < width; x++ )
            {
                pixel_offset = ( x * ( bpp >> 3 ) ) + ( y * pitch );

                r = (uint32)( current_colour.r * 0xFF ) & 0xFF;
                g = (uint32)( current_colour.g * 0xFF ) & 0xFF;
                b = (uint32)( current_colour.b * 0xFF ) & 0xFF;
                a = (uint32)( current_colour.b * 0xFF ) & 0xFF;

                if( bpp == 32 )
                {
                    /* Four bytes to write */
                    fb[ pixel_offset++ ] = r;
                    fb[ pixel_offset++ ] = g;
                    fb[ pixel_offset++ ] = b;
                    fb[ pixel_offset++ ] = a;
                }
                else if( bpp == 24 )
                {
                    /* Three bytes to write */
                    fb[ pixel_offset++ ] = r;
                    fb[ pixel_offset++ ] = g;
                    fb[ pixel_offset++ ] = b;
                }
                else if( bpp == 16 )
                {
                    /* Two bytes to write */
                    /* Bit pack RGB565 into the 16-bit pixel offset */
                    *(uint16*)&fb[pixel_offset] = ( (r >> 3) << 11 ) | ( ( g >> 2 ) << 5 ) | ( b >> 3 );
                }
                else
                {
                    /* Palette mode. TODO: Work out a colour scheme for
                       packing rgb into an 8-bit palette! */
                }

                current_colour.b += ( 1.0 / width );
            }
        }

        /* Scroll through the green colour */
        current_colour.g += cd;
        if( current_colour.g > 1.0 )
        {
            current_colour.g = 1.0;
            cd = -COLOUR_DELTA;
        }
        else if( current_colour.g < 0.0 )
        {
            current_colour.g = 0.0;
            cd = COLOUR_DELTA;
        }

        /* frame_count++; */
        /* if( calculate_frame_count ) */
        /* { */
        /*     calculate_frame_count = 0; */

        /*     /\* Number of frames in a minute, divided by seconds per minute *\/ */
        /*     /\* float fps = (float)frame_count / 60; *\/ */
        /*     /\* printf( "FPS: %.2f\r\n", fps ); *\/ */

        /*     frame_count = 0; */
        /* } */
    }
}
