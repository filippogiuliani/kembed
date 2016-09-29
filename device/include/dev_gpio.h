
#ifndef __DEV_GPIO_H
#define __DEV_GPIO_H


typedef enum { GPIO_OFF = 0, GPIO_ON = 1 } device_gpio_state;



sint32 device_gpioSetFunction ( const uint32 gpio, const uint32 function );
sint32 device_gpioSetValue ( const uint32 gpio, const device_gpio_state state );


#endif /* __DEV_GPIO_H */
