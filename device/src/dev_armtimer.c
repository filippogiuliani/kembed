
#include <blib_types.h>
#include <device.h>
#include <dev_private.h>



/** @brief See the documentation for the ARM side timer (Section 14 of the
    BCM2835 Peripherals PDF) */
#define DEV_ARMTIMER_BASE               ( DEV_PERIPHERAL_BASE + 0xB400 )


static device_arm_timer_t* dev_rpiArmTimer = (device_arm_timer_t*)DEV_ARMTIMER_BASE;

device_arm_timer_t* device_getArmTimer(void)
{
    return dev_rpiArmTimer;
}
