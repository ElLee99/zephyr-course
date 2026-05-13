#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>
#include "led_sensor.h"



const struct device *led0 = DEVICE_DT_GET(DT_NODELABEL(led_sensor0));

static int cmd_fetch (const struct shell *sh, size_t argc, char **argv)
{
    if (!device_is_ready(led0)) 
    {
        shell_error(sh, "Device not ready");
        return -ENODEV;
    }

    sensor_sample_fetch(led0);

    shell_print(sh, "Sample fetched");

    return 0;
}

static int cmd_read (const struct shell *sh, size_t argc, char **argv)
{
    struct sensor_value val;

    sensor_channel_get(led0, SENSOR_CHAN_ALL, &val);

    shell_print(sh, "Sensor state: %d", val.val1);

    return 0;
}

static int cmd_info (const struct shell *sh, size_t argc, char **argv)
{
    bool is_ready = device_is_ready(led0);

    shell_print(sh, "Device name: %s", led0->name);

    if (is_ready) {
        shell_print(sh, "Is ready");
    } else {
        shell_print(sh, "Is not ready");
    }

    return 0;
}

static int cmd_set (const struct shell *sh, size_t argc, char **argv)
{
    int value;

    value = atoi(argv[1]);

    if (value != 0 && value != 1) 
    {
        shell_error(sh, "Use 0 or 1");
        return -EINVAL;
    }

    led_sensor_enable(led0, value);

    if (value == 1)
    {
        shell_print(sh, "LED sensor enabled");
    }
    else
    {
        shell_print(sh, "LED sensor disabled");
    }

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
    sensor_cmds,

    SHELL_CMD(fetch,
              NULL,
              "Fetch sensor sample",
              cmd_fetch),

    SHELL_CMD(read,
              NULL,
              "Read sensor value",
              cmd_read),

    SHELL_CMD(info,
              NULL,
              "Get sensor info",
              cmd_info),

    SHELL_CMD_ARG(set,
                  NULL,
                  "Enable/disable sensor: sensor set 0 or 1",
                  cmd_set,
                  2,
                  0),          

    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(
    sensor,
    &sensor_cmds,
    "LED sensor commands",
    NULL
);