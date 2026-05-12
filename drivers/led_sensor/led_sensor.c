#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>



#define DT_DRV_COMPAT johan_led_sensor



static int led_sensor_sample_fetch (const struct device *dev, enum sensor_channel chan);
static int led_sensor_channel_get (const struct device *dev, enum sensor_channel chan, struct sensor_value *val);



struct led_sensor_config {
    struct gpio_dt_spec led;
};

struct led_sensor_data {
    bool state;
    bool led_enabled;
};

static const struct sensor_driver_api led_api =
{
    .sample_fetch = led_sensor_sample_fetch,
    .channel_get = led_sensor_channel_get,
};



static int led_sensor_init (const struct device *dev)
{
    const struct led_sensor_config *cfg = dev->config;
    int ret = 0;

    if (!gpio_is_ready_dt(&cfg->led)) 
    {
        ret = -ENODEV;
        return ret;
    }

    ret = gpio_pin_configure_dt(&cfg->led, GPIO_OUTPUT_INACTIVE);
    
    return ret;
}

static int led_sensor_sample_fetch (const struct device *dev, 
                                    enum sensor_channel chan)
{
    const struct led_sensor_config *cfg = dev->config;
    struct led_sensor_data *data = dev->data;

    gpio_pin_set_dt(&cfg->led, 1);
    data->state = true;

    return 0;
}

static int led_sensor_channel_get (const struct device *dev, 
                                  enum sensor_channel chan,
                                  struct sensor_value *val)
{
    const struct led_sensor_config *cfg = dev->config;
    struct led_sensor_data *data = dev->data;

    gpio_pin_set_dt(&cfg->led, 0);
    data->state = false;
    val->val1 = data->state;
    val->val2 = 0;

    return 0;
}

int led_sensor_enable (const struct device *dev, bool led_enabled)
{
    struct led_sensor_data *data = dev->data;

    data->led_enabled = led_enabled;

    return 0;
}



#define LED_SENSOR_DEFINE(inst)                                     \
                                                                    \
    static struct led_sensor_data data_##inst;                      \
                                                                    \
    static const struct led_sensor_config config_##inst = {         \
        .led = GPIO_DT_SPEC_GET(DT_DRV_INST(inst), led_gpios),      \
    };                                                              \
                                                                    \
    DEVICE_DT_INST_DEFINE(inst,                                     \
                          led_sensor_init,                          \
                          NULL,                                     \
                          &data_##inst,                             \
                          &config_##inst,                           \
                          POST_KERNEL,                              \
                          CONFIG_SENSOR_INIT_PRIORITY,              \
                          &led_api);

DT_INST_FOREACH_STATUS_OKAY(LED_SENSOR_DEFINE)