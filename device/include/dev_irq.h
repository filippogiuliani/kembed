#ifndef __DEV_IRQ_H
#define __DEV_IRQ_H



/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define DEV_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define DEV_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define DEV_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define DEV_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define DEV_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define DEV_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define DEV_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define DEV_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)

/** @brief The interrupt controller memory mapped register set */
typedef struct {
    vuint32 IRQ_basic_pending;
    vuint32 IRQ_pending_1;
    vuint32 IRQ_pending_2;
    vuint32 FIQ_control;
    vuint32 Enable_IRQs_1;
    vuint32 Enable_IRQs_2;
    vuint32 Enable_Basic_IRQs;
    vuint32 Disable_IRQs_1;
    vuint32 Disable_IRQs_2;
    vuint32 Disable_Basic_IRQs;
} device_irq_controller_t;

/**
   @brief Return the IRQ Controller register set
*/
device_irq_controller_t* device_getIrqController( void );

#endif /* __DEV_IRQ_H */
