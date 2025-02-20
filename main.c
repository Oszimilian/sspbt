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


Systick_Handle handle1 = {.timer = 0, .period=10, .tick = 0};


int main(void)
{
	int i;

	ss_init_systick(160000);

	ss_init_can(1, 1000000);

	uint16_t pa2 = ss_pwm_init(PIN('A', 0), 1000, 16000000);

	uint8_t pwm_val = 0;


	while (1) {
		if (ss_handle_timer(&handle1)) {
			ss_pwm_write(pa2, pwm_val);
			pwm_val = (pwm_val == 100)? 0 : pwm_val + 1;
		}
		
	}

	return 0;
}
