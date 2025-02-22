/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "ss_gpio.h"
#include "ss_pwm.h"
#include "ss_systick.h"
#include "ss_can.h"

#include "ssvesc.h"


Systick_Handle handle1 = {.timer = 0, .period=20, .tick = 0};

struct Fifo can_receive_fifos[2];

int main(void)
{
	int i;

	ss_init_systick(160000);

	init_fifo(&can_receive_fifos[0]);

	ss_can_init(1, 1000000);

	uint32_t msg_ids[] = {0x123, 0x111, 0x33};
	ss_can_add_messages(msg_ids, 3);

	uint16_t heartbeat = ss_io_init(PIN('C', 1), SS_GPIO_MODE_OUTPUT);

	uint16_t error = ss_io_init(PIN('C', 0), SS_GPIO_MODE_OUTPUT);
	ss_io_write(error, SS_GPIO_OFF);

	
	uint16_t pwm_pin = ss_pwm_init(PIN('A', 0), 10000, 16000000);
	uint16_t dir_pin = ss_io_init(PIN('A', 1), GPIO_MODE_OUTPUT);
	uint16_t en_pin = ss_io_init(PIN('A', 2), GPIO_MODE_OUTPUT);


	uint8_t k = 0;


	while (1) {
		if (ss_handle_timer(&handle1)) {
			ss_io_write(heartbeat, SS_GPIO_TOGGLE);
			struct can_tx_msg can_frame;
			can_frame.std_id = 19;
			can_frame.dlc = 1;
			can_frame.data[0] = 1;
			ss_can_send(	1,
							&can_frame);

			//ss_pwm_write(pwm_pin, k);
			//k = (k < 100)? k + 10 : 0;
		}	

		if (!is_fifo_empty(&can_receive_fifos[0])) {
			
			struct can_rx_msg can_frame;
			fifo_remove_can_frame(&can_receive_fifos[0], &can_frame);

			switch(can_frame.std_id) {
				case 0x123:
					ssvesc_handle(	&can_frame,
									pwm_pin,
									dir_pin,
									en_pin);

					ss_io_write(PIN('C', 0), SS_GPIO_TOGGLE);
					break;

				default: break;
			}
			 
		}
		
	}

	return 0;
}
