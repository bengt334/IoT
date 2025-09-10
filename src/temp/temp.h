#ifndef TEMP_H
#define TEMP_H

typedef struct {
    struct sensor_value temp_val;
    const struct device *dev;
} temp_sensor_t;

temp_sensor_t* temp_sensor_new();
int temp_sensor_ctor(temp_sensor_t* temp_sensor);
void temp_sensor_get_value(temp_sensor_t* temp_sensor);
void temp_sensor_dtor(temp_sensor_t* temp_sensor);
void temp_sensor_print(temp_sensor_t* temp_sensor);
#endif