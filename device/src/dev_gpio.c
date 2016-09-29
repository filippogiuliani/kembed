
#include <blib_types.h>
#include <device.h>
#include <dev_private.h>

#define DEV_GPIO_BASE               ( DEV_PERIPHERAL_BASE + 0x00200000 )


sint32 device_gpioSetFunction ( const uint32 gpio, const uint32 function )
{
    ASSERT ( gpio <= 53  && function <= 7 );

    {
	uint32 __gpio = gpio;
	vuint32* __address = (uint32*)DEV_GPIO_BASE;
	uint32 __function = function;
	uint32 __mask;

	while (__gpio > 9)
	{
	    __gpio -= 10U;
	    __address++;
	}

	__gpio *= 3;
	__function = __function << __gpio;
	__mask = 0x7 << __gpio;
	*__address = (*__address & ~__mask) | __function;
    }

    return 0;
}

sint32 device_gpioSetValue ( const uint32 gpio, const device_gpio_state state )
{
    ASSERT ( gpio <= 53 && ( state == GPIO_OFF || state == GPIO_ON ) );

    {
	vuint32* __address = (uint32*)DEV_GPIO_BASE + (gpio >> 5U);
	uint32 __bit = 1 << (gpio & 0x1F);

	if (state == GPIO_OFF)
 	    *(__address + 10) = __bit;
	else
 	    *(__address + 7) = __bit;
    }

    return 0;
}
