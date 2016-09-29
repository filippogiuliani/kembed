
#ifndef __BLIB_UTILS_H
#define __BLIB_UTILS_H

/******************************************************************************
 ***** Constant definitions                                               *****
 ******************************************************************************/

#ifdef DEBUG

#define DPRINT(args)          (device_print_uart0 (args))

#else

#define DPRINT(args)

#endif

/******************************************************************************
 ***** Public function definitions                                        *****
 ******************************************************************************/

void blib_uwait( uint32 us );
uint32 blib_memcpy ( void * destination, const void * source, const uint32 size );


#endif /* __BLIB_UTILS_H */
