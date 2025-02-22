#ifndef _SSVESC_H_
#define _SSVESC_H_

#include <inttypes.h>
#include "ss_can.h"

uint8_t ssvesc_get_pwm(struct can_rx_msg* can_frame);

uint8_t ssvesc_get_dir(struct can_rx_msg* can_frame);

uint8_t ssvesc_get_state(struct can_rx_msg* can_frame);

void ssvesc_handle(struct can_rx_msg* can_frame, uint16_t pwm_pin, uint16_t dir_pin, uint16_t en_pin);

#endif