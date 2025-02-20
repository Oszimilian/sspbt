#include <libopencm3/stm32/can.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <inttypes.h>
#include "ss_gpio.h"

int8_t ss_enable_can_rcc(uint8_t can_interface_id) {
    int8_t status = 0;
    switch(can_interface_id) {
        case 1:
            rcc_periph_clock_enable(RCC_CAN1);
            break;
        
        case 2:
            rcc_periph_clock_enable(RCC_CAN2);
            break;

        default:
            status = -1;
            break;
    }

    return status;
}

int8_t ss_enable_can_gpios(uint8_t can_interface_id) {
    int8_t status = 0;

    uint16_t tx = 0;
    uint16_t rx = 0;
    uint16_t stb = 0;

    switch(can_interface_id) {
        case 1:
            tx = ss_io_init(PIN('B', 9), GPIO_MODE_AF);
            rx = ss_io_init(PIN('B', 8), GPIO_MODE_AF);
            stb = ss_io_init(PIN('B', 7), GPIO_MODE_OUTPUT);
            break;
        
        case 2:
            tx = ss_io_init(PIN('B', 6), GPIO_MODE_AF);
            rx = ss_io_init(PIN('B', 5), GPIO_MODE_AF);
            stb = ss_io_init(PIN('B', 4), GPIO_MODE_OUTPUT);
            break;

        default:
            status = -1;
            break;
    }

    if (status == 0) {
        gpio_set_af(GPIO(PINBANK(tx)), 9, BIT(PINNO(tx)));
        gpio_set_af(GPIO(PINBANK(rx)), 9, BIT(PINNO(rx)));
    }

    return status;
}

int8_t ss_init_can_nvic(uint8_t can_interface_id, uint8_t prio) {
    int8_t status = 0;

    switch(can_interface_id) {
        case 1:
            nvic_enable_irq(NVIC_CAN2_RX0_IRQ);
            nvic_set_priority(NVIC_CAN2_RX0_IRQ, prio);
            break;
        
        case 2:
            nvic_enable_irq(NVIC_CAN2_RX0_IRQ);
            nvic_set_priority(NVIC_CAN2_RX0_IRQ, prio);
            break;

        default:
            status = -1;
            break;
    }

    return status;
}

int8_t ss_can_get_bit_timings(uint32_t baudrate, uint32_t* sjw, uint32_t* tseg1, uint32_t* tseg2, uint32_t* prescaler) {
    int8_t status = 0;
    
    switch(baudrate) {
        case 1000000: 
            *prescaler = 3;
            *tseg1 = 12;
            *tseg2 = 3;
            *sjw = 1;
            break;

        case 500000: 
            *prescaler = 6;
            *tseg1 = 12;
            *tseg2 = 3;
            *sjw = 1;
            break;

        case 250000: 
            *prescaler = 12;
            *tseg1 = 12;
            *tseg2 = 3;
            *sjw = 1;
            break;

        default: status = -1; break;
    }

    return status;
}



int8_t ss_init_can(uint8_t can_interface_id, uint32_t baudrate) {
    int8_t status = 0;
    uint32_t prescaler = 0;
    uint32_t sjw = 0;
    uint32_t tseg1 = 0;
    uint32_t tseg2 = 0;

    if (ss_enable_can_rcc(can_interface_id) == -1) status = -1;

    if (ss_enable_can_gpios(can_interface_id) == -1) status = -1;

    if (ss_init_can_nvic(can_interface_id, 1) == -1) status = -1;

    if (ss_can_get_bit_timings(baudrate, &sjw, &tseg1, &tseg2, &prescaler) == -1) status = -1;

    can_init(   CAN1,
                false,
                true,
                false,
                false,
                false,
                false,
                sjw,
                tseg1,
                tseg2,
                2,
                false,
                false);

    can_filter_id_mask_32bit_init( 0,
                                    0,
                                    0,
                                    0,
                                    true);
                                    
    can_enable_irq(CAN1, CAN_IER_FMPIE0);
}

