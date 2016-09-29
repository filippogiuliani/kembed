#ifndef __BLIB_TYPES_H
#define __BLIB_TYPES_H

#define ASSERT(cond)				\
    do {					\
	if (!(cond))				\
	    return -1;				\
    } while (0);
    

#define NULL      ((void*)(0x0))


typedef enum { FALSE = 0, TRUE = 1 } bool;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef signed int sint32;
typedef signed short sint16;
typedef signed char sint8;

typedef volatile unsigned int vuint32;
typedef volatile unsigned short vuint16;
typedef volatile unsigned char vuint8;

typedef volatile signed int vsint32;
typedef volatile signed short vsint16;
typedef volatile signed char vsint8;


#endif /* __BLIB_TYPES_H */
