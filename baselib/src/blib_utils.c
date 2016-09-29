

#include "blib_types.h"
#include "blib_utils.h"

#define RPI_SYSTIMER_BASE (0x20003000)

typedef struct
{
    vuint32 control_status;
    vuint32 counter_lo;
    vuint32 counter_hi;
    vuint32 compare0;
    vuint32 compare1;
    vuint32 compare2;
    vuint32 compare3;
} rpi_sys_timer_t;


static rpi_sys_timer_t* rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;

void blib_uwait ( uint32 us )
{
    vuint32 ts = rpiSystemTimer->counter_lo;

    while( ( rpiSystemTimer->counter_lo - ts ) < us )
    {
        /* BLANK */
    }
}


uint32 blib_memcpy ( void * destination, const void * source, const uint32 size )
{
    ASSERT (destination != NULL && source != NULL);
    
    uint32 i;
    uint8* __dst = (uint8 *)destination;
    uint8* __src = (uint8 *)source;

    for (i = 0U; i < size; i++)
	*__dst++ = *__src++;

    return 0;
}
