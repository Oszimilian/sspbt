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



int main(void)
{
	int i;


	//uint16_t heartbeat = ss_io_init(PIN('C', 1), GPIO_MODE_AF);

	//uint16_t error = ss_pwm_init(PIN('C', 2), 10000, 16000000);

	uint16_t pa2 = ss_pwm_init(PIN('A', 0), 1000, 16000000);


	/* Blink the LED (PD12) on the board with every transmitted byte. */
	while (1) {

		

		ss_pwm_write(pa2, 5);
	}

	return 0;
}
