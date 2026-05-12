#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include "led_sensor.h"

int main (void)
{
    const struct device *led0 = DEVICE_DT_GET(DT_NODELABEL(led_sensor0));
    const struct device *led1 = DEVICE_DT_GET(DT_NODELABEL(led_sensor1));
    const struct device *led2 = DEVICE_DT_GET(DT_NODELABEL(led_sensor2));
    const struct device *led3 = DEVICE_DT_GET(DT_NODELABEL(led_sensor3));

    struct sensor_value val;

    if (!device_is_ready(led0)
        || !device_is_ready(led1)
        || !device_is_ready(led2)
        || !device_is_ready(led3)) 
    {
        return -1;
    }

    while (1)
    {
        sensor_sample_fetch(led0);
        sensor_sample_fetch(led1);
        sensor_sample_fetch(led2);
        sensor_sample_fetch(led3);

        led_sensor_enable(led0, false);
        led_sensor_enable(led1, false);
        led_sensor_enable(led2, false);
        led_sensor_enable(led3, false);

        k_msleep(500);

        sensor_channel_get(led0, SENSOR_CHAN_ALL, &val);
        sensor_channel_get(led1, SENSOR_CHAN_ALL, &val);
        sensor_channel_get(led2, SENSOR_CHAN_ALL, &val);
        sensor_channel_get(led3, SENSOR_CHAN_ALL, &val);

        led_sensor_enable(led0, false);
        led_sensor_enable(led1, false);
        led_sensor_enable(led2, false);
        led_sensor_enable(led3, false);

        k_msleep(500);

        
    }

    return 0;
}