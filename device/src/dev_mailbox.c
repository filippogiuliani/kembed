

/******************************************************************************
 ***** Include                                                            *****
 ******************************************************************************/

#include <blib_types.h>
#include <baselib.h>
#include <device.h>
#include <dev_private.h>


/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#define DEV_MAILBOX0_BASE    ( DEV_PERIPHERAL_BASE + 0xB880 )


/******************************************************************************
 ***** Type definitions                                                   *****
 ******************************************************************************/


/* The available mailbox channels in the BCM2835 Mailbox interface.
   See https://github.com/raspberrypi/firmware/wiki/Mailboxes for
   information */
typedef enum
{
    MB0_POWER_MANAGEMENT = 0,
    MB0_FRAMEBUFFER,
    MB0_VIRTUAL_UART,
    MB0_VCHIQ,
    MB0_LEDS,
    MB0_BUTTONS,
    MB0_TOUCHSCREEN,
    MB0_UNUSED,
    MB0_TAGS_ARM_TO_VC,
    MB0_TAGS_VC_TO_ARM,
} device_mailbox0_channel_t;


/* Define a structure which defines the register access to a mailbox.
   Not all mailboxes support the full register set! */
typedef struct
{
    vuint32 Read;
    vuint32 reserved1[((0x90 - 0x80) / 4) - 1];
    vuint32 Poll;
    vuint32 Sender;
    vuint32 Status;
    vuint32 Configuration;
    vuint32 Write;
} device_mailbox_t;


/* These defines come from the Broadcom Videocode driver source code, see:
   brcm_usrlib/dag/vmcsx/vcinclude/bcm2708_chip/arm_control.h */
enum device_mailbox_status_reg_bits
{
    DEV_ARM_MS_FULL  = 0x80000000,
    DEV_ARM_MS_EMPTY = 0x40000000,
    DEV_ARM_MS_LEVEL = 0x400000FF,
};


typedef enum
{
    TAG_STATE_REQUEST = 0,
    TAG_STATE_RESPONSE = 1,
} device_tag_state_t;


typedef enum
{
    PT_OSIZE = 0,
    PT_OREQUEST_OR_RESPONSE = 1,
} device_tag_buffer_offset_t;


typedef enum
{
    T_OIDENT = 0,
    T_OVALUE_SIZE = 1,
    T_ORESPONSE = 2,
    T_OVALUE = 3,
} device_tag_offset_t;


/******************************************************************************
 ***** Vars definitions                                                   *****
 ******************************************************************************/


/* Mailbox 0 mapped to it's base address */
static device_mailbox_t* dev_rpiMailbox0 = (device_mailbox_t*)DEV_MAILBOX0_BASE;


/* Make sure the property tag buffer is aligned to a 16-byte boundary because
   we only have 28-bits available in the property interface protocol to pass
   the address of the buffer to the VC. */
static sint32 dev_pt[8192] __attribute__((aligned(16)));
static sint32 dev_pt_index = 0;


/******************************************************************************
 ***** Private function declaration                                       *****
 ******************************************************************************/

static void device_mailbox0Write( device_mailbox0_channel_t channel, sint32 value );

static sint32 device_mailbox0Read( device_mailbox0_channel_t channel );
    

/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void device_propertyInit( void )
{
    /* Fill in the size on-the-fly */
    dev_pt[PT_OSIZE] = 12;

    /* Process request (All other values are reserved!) */
    dev_pt[PT_OREQUEST_OR_RESPONSE] = 0;

    /* First available data slot */
    dev_pt_index = 2;

    /* NULL tag to terminate tag list */
    dev_pt[dev_pt_index] = 0;
}

/**
   @brief Add a property tag to the current tag list. Data can be included. All data is uint32_t
   @param tag
*/
void device_propertyAddTag( device_mailbox_tag_t tag, ... )
{
    va_list vl;
    va_start( vl, tag );

    dev_pt[dev_pt_index++] = tag;

    switch( tag )
    {
    case DEV_TAG_GET_FIRMWARE_VERSION:
    case DEV_TAG_GET_BOARD_MODEL:
    case DEV_TAG_GET_BOARD_REVISION:
    case DEV_TAG_GET_BOARD_MAC_ADDRESS:
    case DEV_TAG_GET_BOARD_SERIAL:
    case DEV_TAG_GET_ARM_MEMORY:
    case DEV_TAG_GET_VC_MEMORY:
    case DEV_TAG_GET_DMA_CHANNELS:
	/* Provide an 8-byte buffer for the response */
	dev_pt[dev_pt_index++] = 8;
	dev_pt[dev_pt_index++] = 0; /* Request */
	dev_pt_index += 2;
	break;

    case DEV_TAG_GET_CLOCKS:
    case DEV_TAG_GET_COMMAND_LINE:
	/* Provide a 256-byte buffer */
	dev_pt[dev_pt_index++] = 256;
	dev_pt[dev_pt_index++] = 0; /* Request */
	dev_pt_index += 256 >> 2;
	break;

    case DEV_TAG_ALLOCATE_BUFFER:
	dev_pt[dev_pt_index++] = 8;
	dev_pt[dev_pt_index++] = 0; /* Request */
	dev_pt[dev_pt_index++] = va_arg( vl, int );
	dev_pt_index += 1;
	break;

    case DEV_TAG_GET_PHYSICAL_SIZE:
    case DEV_TAG_SET_PHYSICAL_SIZE:
    case DEV_TAG_TEST_PHYSICAL_SIZE:
    case DEV_TAG_GET_VIRTUAL_SIZE:
    case DEV_TAG_SET_VIRTUAL_SIZE:
    case DEV_TAG_TEST_VIRTUAL_SIZE:
    case DEV_TAG_GET_VIRTUAL_OFFSET:
    case DEV_TAG_SET_VIRTUAL_OFFSET:
	dev_pt[dev_pt_index++] = 8;
	dev_pt[dev_pt_index++] = 0; /* Request */

	if( ( tag == DEV_TAG_SET_PHYSICAL_SIZE ) ||
	    ( tag == DEV_TAG_SET_VIRTUAL_SIZE ) ||
	    ( tag == DEV_TAG_SET_VIRTUAL_OFFSET ) ||
	    ( tag == DEV_TAG_TEST_PHYSICAL_SIZE ) ||
	    ( tag == DEV_TAG_TEST_VIRTUAL_SIZE ) )
	{
	    dev_pt[dev_pt_index++] = va_arg( vl, int ); /* Width */
	    dev_pt[dev_pt_index++] = va_arg( vl, int ); /* Height */
	}
	else
	{
	    dev_pt_index += 2;
	}
	break;


    case DEV_TAG_GET_ALPHA_MODE:
    case DEV_TAG_SET_ALPHA_MODE:
    case DEV_TAG_GET_DEPTH:
    case DEV_TAG_SET_DEPTH:
    case DEV_TAG_GET_PIXEL_ORDER:
    case DEV_TAG_SET_PIXEL_ORDER:
    case DEV_TAG_GET_PITCH:
	dev_pt[dev_pt_index++] = 4;
	dev_pt[dev_pt_index++] = 0; /* Request */

	if( ( tag == DEV_TAG_SET_DEPTH ) ||
	    ( tag == DEV_TAG_SET_PIXEL_ORDER ) ||
	    ( tag == DEV_TAG_SET_ALPHA_MODE ) )
	{
	    /* Colour Depth, bits-per-pixel \ Pixel Order State */
	    dev_pt[dev_pt_index++] = va_arg( vl, int );
	}
	else
	{
	    dev_pt_index += 1;
	}
	break;

    case DEV_TAG_GET_OVERSCAN:
    case DEV_TAG_SET_OVERSCAN:
	dev_pt[dev_pt_index++] = 16;
	dev_pt[dev_pt_index++] = 0; /* Request */

	if( ( tag == DEV_TAG_SET_OVERSCAN ) )
	{
	    dev_pt[dev_pt_index++] = va_arg( vl, int ); /* Top pixels */
	    dev_pt[dev_pt_index++] = va_arg( vl, int ); /* Bottom pixels */
	    dev_pt[dev_pt_index++] = va_arg( vl, int ); /* Left pixels */
	    dev_pt[dev_pt_index++] = va_arg( vl, int ); /* Right pixels */
	}
	else
	{
	    dev_pt_index += 4;
	}
	break;

    default:
	/* Unsupported tags, just remove the tag from the list */
	dev_pt_index--;
	break;
    }

    /* Make sure the tags are 0 terminated to end the list and update the buffer size */
    dev_pt[dev_pt_index] = 0;

    va_end( vl );
}


sint32 device_propertyProcess( void )
{
    sint32 result;

    /* Fill in the size of the buffer */
    dev_pt[PT_OSIZE] = ( dev_pt_index + 1 ) << 2;
    dev_pt[PT_OREQUEST_OR_RESPONSE] = 0;

    device_mailbox0Write( MB0_TAGS_ARM_TO_VC, (uint32)dev_pt );

    result = device_mailbox0Read( MB0_TAGS_ARM_TO_VC );

    return result;
}


device_mailbox_property_t* device_propertyGet( device_mailbox_tag_t tag )
{
    static device_mailbox_property_t property;
    sint32* tag_buffer = NULL;

    property.tag = tag;

    /* Get the tag from the buffer. Start at the first tag position  */
    sint32 index = 2;

    while( index < ( dev_pt[PT_OSIZE] >> 2 ) )
    {
        /* printf( "Test Tag: [%d] %8.8X\r\n", index, pt[index] ); */
        if( dev_pt[index] == tag )
        {
            tag_buffer = &dev_pt[index];
            break;
        }

        /* Progress to the next tag if we haven't yet discovered the tag */
        index += ( dev_pt[index + 1] >> 2 ) + 3;
    }

    /* Return NULL of the property tag cannot be found in the buffer */
    if( tag_buffer == NULL )
        return NULL;

    /* Return the required data */
    property.byte_length = tag_buffer[T_ORESPONSE] & 0xFFFF;
    blib_memcpy( property.data.buffer_8, &tag_buffer[T_OVALUE], property.byte_length );

    return &property;
}


/******************************************************************************
 ***** Private function definitions                                       *****
 ******************************************************************************/


static void device_mailbox0Write( device_mailbox0_channel_t channel, sint32 value )
{
    /* For information about accessing mailboxes, see:
       https://github.com/raspberrypi/firmware/wiki/Accessing-mailboxes */

    /* Add the channel number into the lower 4 bits */
    value &= ~(0xF);
    value |= channel;

    /* Wait until the mailbox becomes available and then write to the mailbox
       channel */
    while( ( dev_rpiMailbox0->Status & DEV_ARM_MS_FULL ) != 0 ) { }

    /* Write the modified value + channel number into the write register */
    dev_rpiMailbox0->Write = value;
}


static sint32 device_mailbox0Read( device_mailbox0_channel_t channel )
{
    /* For information about accessing mailboxes, see:
       https://github.com/raspberrypi/firmware/wiki/Accessing-mailboxes */
    sint32 value = -1;

    /* Keep reading the register until the desired channel gives us a value */
    while( ( value & 0xF ) != channel )
    {
        /* Wait while the mailbox is empty because otherwise there's no value
           to read! */
        while( dev_rpiMailbox0->Status & DEV_ARM_MS_EMPTY ) { }

        /* Extract the value from the Read register of the mailbox. The value
           is actually in the upper 28 bits */
        value = dev_rpiMailbox0->Read;
    }

    /* Return just the value (the upper 28-bits) */
    return value >> 4;
}
