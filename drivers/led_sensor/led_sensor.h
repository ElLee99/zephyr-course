#ifndef ZEPHYR_INCLUDE_DRIVERS_LED_SENSOR_H_
#define ZEPHYR_INCLUDE_DRIVERS_LED_SENSOR_H_



#include <zephyr/device.h>
#include <stdbool.h>



#ifdef __cplusplus
extern "C" {
#endif

int led_sensor_enable(const struct device *dev, bool led_enabled);

#ifdef __cplusplus
}
#endif



#endif /* ZEPHYR_INCLUDE_DRIVERS_LED_SENSOR_H_ */