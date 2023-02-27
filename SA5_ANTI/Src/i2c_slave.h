/*
 * i2c.h
 *
 *  Created on: Apr 23, 2019
 *      Author: weic
 */

#ifndef __I2C_SLAVE_H__
#define __I2C_SLAVE_H__

#include <stdint.h>

#define I2C_SLAVE_MAX	(8)

#define I2C_SLAVE_WRITE	(0)
#define I2C_SLAVE_READ	(1)

struct i2c_reg;

struct i2c_slave_op {
	uint8_t addr;
	uint8_t mask;

	void (*match)(void *priv, int dir);
	uint8_t (*read)(void *priv);
	void (*write)(void *priv, uint8_t data);
	void (*stop)(void *priv);
	void (*nack)(void *priv);
	void (*reset)(void *priv);

	void *priv;
};

struct i2c_slave_ctx {
	int dir;
	int id;
	unsigned int isr_irq_mask;
	struct i2c_reg *reg;
	struct i2c_slave_op *slave_list[I2C_SLAVE_MAX];
	struct i2c_slave_op *slave; /* current slave */
};

int i2c_init(struct i2c_slave_ctx *ctx, void *reg);
int i2c_slave_register(struct i2c_slave_ctx *ctx, struct i2c_slave_op *slave);
int i2c_slave_start(struct i2c_slave_ctx *ctx);
int i2c_slave_reset(struct i2c_slave_ctx *ctx);

#endif /* STM32L0XX_HAL_DRIVER_SRC_I2C_H_ */
