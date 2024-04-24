/* avago_apds9306_emul.c - Emulated driver for Broadcom / Avago APDS9306 light sensor. */

/*
 * Copyright (c) 2023, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/emul.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/i2c_emul.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT                       avago_apds9306

LOG_MODULE_REGISTER(avago_apds9306, CONFIG_AVAGO_APDS9306_LOG_LEVEL);

#if(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0)
#warning "apds9306 driver enabled without any devices"
#endif

struct apds9306_emul_data {
	struct i2c_emul emul;
	const struct device *i2c;
	uint32_t cur_reg;
};

struct apds9306_emul_config {
    struct i2c_dt_spec i2c;
    uint8_t resolution;
    uint8_t frequency;
    uint8_t gain;
};

/** @brief          Emulator an I2C transfer to an APDS9306 chip. This handles simple reads and writes.
 *  @param emul     I2C emulation information
 *  @param msgs     List of messages to process. For 'read' messages, this function
 *	                updates the 'buf' member with the data that was read
 *  @param num_msgs Number of messages to process
 *  @param addr     Address of the I2C target device. This is assumed to be correct,
 *	                due to the
 *  @return         0 If successful, -EIO General input / output error
 */
static int apds9306_emul_transfer(const struct emul *target, struct i2c_msg *msgs,
			      int num_msgs, int addr)
{
	return 0;
}

static struct i2c_emul_api bus_api = {
	.transfer = apds9306_emul_transfer,
};

/** @brief          Set up a new APDS9306 emulator.
 *                  This should be called for each APDS9306 device that needs to be emulated. It
 *                  registers it with the I2C emulation controller.
 * @param target    Emulation information
 * @param parent    Device to emulate (must use APDS9306 driver)
 * @return          0 indicating success (always)
 */
static int emul_avago_apds9306_init(const struct emul *target, const struct device *parent)
{
	return 0;
}

#define APDS9306_INIT(inst)                                                     \
    static struct apds9306_emul_data apds9306_emul_data_##inst;                 \
                                                                                \
    static const struct apds9306_emul_config apds9306_emul_config_##inst = {    \
        .i2c = I2C_DT_SPEC_INST_GET(inst),                                      \
        .resolution = DT_INST_PROP(inst, resolution),					        \
        .gain = DT_INST_PROP(inst, gain),					                    \
        .frequency = DT_INST_PROP(inst, frequency),					            \
    };                                                                          \
                                                                                \
    EMUL_DT_INST_DEFINE(inst, emul_avago_apds9306_init,                         \
                  &apds9306_emul_data_##inst,                                   \
                  &apds9306_emul_config_##inst,                                 \
                  &bus_api,                                                     \
                  NULL);

DT_INST_FOREACH_STATUS_OKAY(APDS9306_INIT)