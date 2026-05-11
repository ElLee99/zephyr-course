#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

void board_early_init_hook(void)
{
    printk("Board Initialized\n");
}


static int gboard_init(const struct device *dev)
{
    ARG_UNUSED(dev);

    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(gboard_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);