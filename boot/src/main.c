
#include "blib_types.h"

extern vuint32 __sBss;
extern vuint32 __eBss;
extern void kernel_main ( uint32 r0, uint32 r1, uint32 r2 );


void _cstartup (uint32 r0, uint32 r1, uint32 r2)
{
    vuint32* bss = &__sBss;
    vuint32* bss_end = &__eBss;

    while ( bss < bss_end )
	*bss++ = 0;

    kernel_main ( r0, r1, r2 );

    while (1);
}

void _exit ( int code )
{
    while (1)
	;
}
