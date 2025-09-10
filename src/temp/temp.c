/*
 * Copyright (c) 2022 Thomas Stranger
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <math.h>
#include "temp.h"


/*
 * Get a device structure from a devicetree node with compatible
 * "maxim,ds18b20". (If there are multiple, just pick one.)
 */
static const struct device *get_ds18b20_device(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(maxim_ds18b20);

	if (dev == NULL) {
		/* No such node, or the node does not have status "okay". */
		printk("\nError: no device found.\n");
		return NULL;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return NULL;
	}

	printk("Found device \"%s\", getting sensor data\n", dev->name);
	return dev;
}

temp_sensor_t* temp_sensor_new() {
    return (temp_sensor_t*)k_malloc(sizeof(temp_sensor_t));
}

int temp_sensor_ctor(temp_sensor_t* temp_sensor) {
    temp_sensor->dev = get_ds18b20_device();
    printk("Get Device Data\n");	

	if (temp_sensor->dev == NULL) {
		printk("Failed to Get Device Data\n");
		return ENODEV;
	}
	return 0;
}

void temp_sensor_get_value(temp_sensor_t* temp_sensor) {
	int res = 0;
    res = sensor_sample_fetch(temp_sensor->dev);
		printk("Get sensor_sample_fetch\n");
		if (res != 0) {
			printk("sample_fetch() failed: %d\n", res);
		}

		res = sensor_channel_get(temp_sensor->dev, SENSOR_CHAN_AMBIENT_TEMP, &temp_sensor->temp_val);
		if (res != 0) {
			printk("channel_get() failed: %d\n", res);
		}
}

void temp_sensor_print(temp_sensor_t* temp_sensor) {
	printk("Temp: %d.%06d\n", temp_sensor->temp_val.val1, temp_sensor->temp_val.val2);
		k_sleep(K_MSEC(2000));
}

void temp_sensor_dtor(temp_sensor_t* temp_sensor) {
	if(temp_sensor) {
    	k_free(temp_sensor);
	}
}


