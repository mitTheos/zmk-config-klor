#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>
#include <zephyr/sys/__assert.h>

LOG_MODULE_REGISTER(enable_charge_pump);

static void enable_charge_pump() {
    LOG_INF("Starting...");
    const uint8_t display_commands[] = {0x00, 0xae, 0x8d, 0x14, 0xaf};
    const struct device* dev = device_get_binding("i2c@40003000");
    
    const uint16_t dev_addr = 0x3c;

    __ASSERT(sizeof(*display_commands) == 5);
    int ret = i2c_write(dev, display_commands, sizeof(*display_commands), dev_addr);
    if (ret != 0) {
        LOG_ERR("Failed to write to device.");
    } 
    LOG_INF("Successfully enabled charge pump.");

    __ASSERT(0 == 1);
}

SYS_INIT(enable_charge_pump, POST_KERNEL, 999);
