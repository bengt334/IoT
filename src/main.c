/*
 * Copyright (c) 2022 Thomas Stranger
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include "temp/temp.h"



int main(void)
{
	int ret = 0;
	temp_sensor_t* temp_sensor = temp_sensor_new();
	ret = temp_sensor_ctor(temp_sensor);
	if (ret) {
		temp_sensor_dtor(temp_sensor);
		return ret;
	}
	while (true) {
		temp_sensor_get_value(temp_sensor);
		temp_sensor_print(temp_sensor);
	}
	temp_sensor_dtor(temp_sensor);
	return ret;
}

