#include "ssvesc.h"
#include "ss_gpio.h"


extern 

uint8_t ssvesc_get_pwm(struct can_rx_msg* can_frame) {
    return can_frame->data[0];
}

uint8_t ssvesc_get_dir(struct can_rx_msg* can_frame) {
    return can_frame->data[1] & 0x01;
}

uint8_t ssvesc_get_state(struct can_rx_msg* can_frame) {
    return can_frame->data[2] & 0x02;
}

void ssvesc_handle(struct can_rx_msg* can_frame, uint16_t pwm_pin, uint16_t dir_pin, uint16_t en_pin) {
    ss_pwm_write(pwm_pin, ssvesc_get_pwm(can_frame));

    ss_io_write(dir_pin, ssvesc_get_dir(can_frame) ? SS_GPIO_ON : SS_GPIO_OFF);

    ss_io_write(en_pin, ssvesc_get_state(can_frame) ? SS_GPIO_ON : SS_GPIO_OFF);
}