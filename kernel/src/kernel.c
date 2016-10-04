
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
    /* device_mailbox_property_t* mp; */
    unsigned short* fb = NULL;

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

    /* Initialise a framebuffer... */
    DPRINT ("Initialize Mailbox..");

    /* device_propertyInit(); */
    /* device_propertyAddTag( DEV_TAG_ALLOCATE_BUFFER ); */
    /* device_propertyAddTag( DEV_TAG_SET_PHYSICAL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT ); */
    /* device_propertyAddTag( DEV_TAG_SET_VIRTUAL_SIZE, SCREEN_WIDTH, SCREEN_HEIGHT ); */
    /* device_propertyAddTag( DEV_TAG_SET_DEPTH, SCREEN_DEPTH ); */
    /* /\* device_propertyAddTag( DEV_TAG_GET_PITCH ); *\/ */
    /* /\* device_propertyAddTag( DEV_TAG_GET_PHYSICAL_SIZE ); *\/ */
    /* /\* device_propertyAddTag( DEV_TAG_GET_DEPTH ); *\/ */
    /* device_propertyProcess(); */

    /* if( ( mp = device_propertyGet( DEV_TAG_GET_PHYSICAL_SIZE ) ) ) */
    /* { */
    /*     width = mp->buffer[0]; */
    /*     height = mp->buffer[1]; */

    /*     /\* printf( "Initialised Framebuffer: %dx%d ", width, height ); *\/ */
    /* } */

    /* if( ( mp = device_propertyGet( DEV_TAG_GET_DEPTH ) ) ) */
    /* { */
    /*     bpp = mp->buffer[0]; */
    /*     /\* printf( "%dbpp\r\n", bpp ); *\/ */
    /* } */

    /* if( ( mp = device_propertyGet( DEV_TAG_GET_PITCH ) ) ) */
    /* { */
    /*     pitch = mp->buffer[0]; */
    /*     /\* printf( "Pitch: %d bytes\r\n", pitch ); *\/ */
    /* } */

    /* if( ( mp = device_propertyGet( DEV_TAG_ALLOCATE_BUFFER ) ) ) */
    /* { */
    /*     fb = (unsigned short*)mp->buffer[0]; */
    /* 	fblen = mp->buffer[1]; */
    /*     /\* printf( "Framebuffer address: %8.8X\r\n", (unsigned int)fb ); *\/ */
    /* } */
    
    /* while( 1 ) */
    /* {	 */
    /* 	for (i = 0U; i < fblen / 2; i++) */
    /* 	{ */
    /* 	    *(fb + i) = 0xCCC0; */
    /* 	}	 */
    /* } */

    fb = device_prova ();

    device_initializeMonitor ( (uint8*)fb, 0x1111, 0xCCCC );

    device_printLine ("Hello World!");
    
    while (1U);
}
