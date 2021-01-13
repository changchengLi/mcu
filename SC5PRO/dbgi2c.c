#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <i2c_master.h>
#include <i2c_slave.h>
#include <chip.h>
#include <tca9548a.h>
#include <libopencm3/cm3/nvic.h>
#include <dbgi2c.h>
#include <tick.h>

#define DBGI2C_ADDR_BASE	0x28
#define DBGI2C_I2C_MASTER	I2C2
#define DBGI2C_I2C_TIMEOUT	1

static inline uint8_t dbgi2c_idx2addr(int idx)
{
	return DBGI2C_ADDR_BASE + idx;
}

int dbgi2c_i2c_write_byte(int idx, uint8_t data)
{
	return i2c_master_write_byte(DBGI2C_I2C_MASTER,  dbgi2c_idx2addr(idx),
				     DBGI2C_I2C_TIMEOUT, data);
}

int dbgi2c_i2c_write_block(int idx, uint8_t *data, unsigned int len)
{
	return i2c_master_write_block(DBGI2C_I2C_MASTER, dbgi2c_idx2addr(idx),
				      DBGI2C_I2C_TIMEOUT, data, len);
}

int dbgi2c_i2c_read_block(int idx, uint8_t *data, unsigned int len)
{
	return i2c_master_read_block(DBGI2C_I2C_MASTER, dbgi2c_idx2addr(idx),
				     DBGI2C_I2C_TIMEOUT, data, len);
}

static inline uint8_t dbgi2c_addr_width(int n)
{
	return (0x20 + (n / 8) - 1);
}
static inline uint8_t dbgi2c_data_width(int n)
{
	switch (n) {
	case 8:
		return 0x10;
	case 16:
		return 0x11;
	case 32:
		return 0x12;
	default:
		return 0x18;
	}
	return 0x18;
}

static int __dbgi2c_write(int idx, int addr_width, int data_width,
			  uint64_t addr, void *data, int len)
{
	uint8_t msg[128];
	int msg_len, i, err;

	/* append data width type */
	msg[0] = dbgi2c_data_width(data_width);
	msg_len = 1;

	/* append address */
	for (i = 0; i < addr_width / 8; ++i, ++msg_len)
		msg[msg_len] = ((uint8_t *)&addr)[i];

	/* append data */
	for (i = 0; i < len; ++i, ++msg_len)
		msg[msg_len] = ((uint8_t *)data)[i];

	err = dbgi2c_i2c_write_byte(idx, dbgi2c_addr_width(addr_width));
	if (err) {
		printf("set address width failed\n");
		return err;
	}

	err = dbgi2c_i2c_write_block(idx, msg, msg_len);
	if (err)
		printf("write address or data failed of soc%d\n", idx);

	return err;
}

static int __dbgi2c_read(int idx, int addr_width, int data_width,
			 uint64_t addr, void *data, int len)
{
	uint8_t msg[128];
	int msg_len, i, err;

	/* append data width type */
	msg[0] = dbgi2c_data_width(data_width);
	msg_len = 1;

	/* append address */
	for (i = 0; i < addr_width / 8; ++i, ++msg_len)
		msg[msg_len] = ((uint8_t *)&addr)[i];


	err = dbgi2c_i2c_write_byte(idx, dbgi2c_addr_width(addr_width));
	if (err) {
		printf("set address width failed\n");
		return err;
	}
	err = dbgi2c_i2c_write_block(idx, msg, msg_len);
	if (err) {
		printf("set address failed\n");
		return err;
	}

	/* get data */
	err = dbgi2c_i2c_read_block(idx, data, len);
	if (err)
		printf("get data failed\n");

	return err;
}

static inline int get_addr_width(uint64_t addr)
{
	int i;

	for (i = 8; i <= 48; i += 8) {
		if ((addr & ~(((unsigned long)1 << i) - 1)) == 0)
			break;
	}

	return i;
}

int dbgi2c_write32(int idx, uint64_t addr, uint32_t value)
{
	int addr_width = get_addr_width(addr);

	return __dbgi2c_write(idx, addr_width, 32,
			      addr, &value, 4);
}

int dbgi2c_read32(int idx, uint64_t addr, uint32_t *value)
{
	int addr_width = get_addr_width(addr);

	return __dbgi2c_read(idx, addr_width, 32,
			     addr, value, 4);
}

int dbgi2c_write8(int idx, uint64_t addr, uint8_t value)
{
	int addr_width = get_addr_width(addr);

	return __dbgi2c_write(idx, addr_width, 8,
			      addr, &value, 1);
}

int dbgi2c_read8(int idx, uint64_t addr, uint8_t *value)
{
	int addr_width = get_addr_width(addr);

	return __dbgi2c_read(idx, addr_width, 8,
			     addr, value, 1);
}

int dbgi2c_read(int idx, uint64_t addr, void *data, int len)
{
	int addr_width = get_addr_width(addr);

	return __dbgi2c_read(idx, addr_width, 0,
			     addr, data, len);
}

int dbgi2c_write(int idx, uint64_t addr, void *data, int len)
{
	int addr_width = get_addr_width(addr);

	return __dbgi2c_write(idx, addr_width, 0,
			      addr, data, len);
}

void dbgi2c_test(void)
{
	int i;
	uint32_t value = 0;
	int err = 0;

	for (i = 0; i < 8; ++i) {
		if (!chip_is_enabled()) {
			printf("chip slot %d not enabled\n", i);
			continue;
		}

		printf("chip slot %d\n", i);
		err = dbgi2c_read32(i, 0x50010000, &value);
		if (err)
			printf("failed on dbgi2c_test\n");
		else
			printf("chip id 0x%08lx\n", value);
	}
}

/* i2c master operations */
#define DBGI2C_MCU_INFO_BASE	0x201bf00
void dbgi2c_broadcast(int idx, struct dbgi2c_info *info)
{
	int i;

	for (i = 0; i < sizeof(struct dbgi2c_info) / 4; ++i) {
		dbgi2c_write32(idx, DBGI2C_MCU_INFO_BASE + i * 4,
			       ((uint32_t *)&info[i])[i]);
	}
}

/* i2c slave operations */

#define DBGI2C_SLAVE_BASE	0x60
#define DBGI2C_SOC_INFO_BASE	0x201bf80
#define DBGI2C_REG_MASK		(128 - 1)

struct dbgi2c_i2c_ctx {
	int set_idx;
	uint8_t idx;
	int soc;
} ctx;

static inline void idx_set(uint8_t idx)
{
	ctx.idx = idx & DBGI2C_REG_MASK;
}

static inline void idx_inc(void)
{
	ctx.idx = (ctx.idx + 1) & DBGI2C_REG_MASK;
}

static void dbgi2c_i2c_slave_match(void *priv, uint8_t addr,  int dir)
{
	ctx.soc = addr - DBGI2C_SLAVE_BASE;
	if (dir == I2C_SLAVE_WRITE)
		ctx.set_idx = 1;
}

static void dbgi2c_i2c_slave_write(void *priv, uint8_t data)
{
	uint64_t soc_addr;

	if (ctx.set_idx) {
		idx_set(data);
		ctx.set_idx = 0;
		return;
	}

	if (chip_is_enabled()) {
		soc_addr = DBGI2C_SOC_INFO_BASE + ctx.idx;
		dbgi2c_write8(ctx.soc, soc_addr, data);
	}

	idx_inc();
}

static uint8_t dbgi2c_i2c_slave_read(void *priv)
{
	uint8_t data = 0;
	uint64_t soc_addr;

	if (chip_is_enabled()) {
		soc_addr = DBGI2C_SOC_INFO_BASE + ctx.idx;
		dbgi2c_read8(ctx.soc, soc_addr, &data);
	} else {
		data = (ctx.soc << 8) | ctx.idx;
	}

	idx_inc();
	return data;
}

static struct i2c_slave_op slave = {
	.addr = DBGI2C_SLAVE_BASE,
	.mask = 0x07,
	.match	= dbgi2c_i2c_slave_match,
	.write	= dbgi2c_i2c_slave_write,
	.read	= dbgi2c_i2c_slave_read,
};

void dbgi2c_init(struct i2c_slave_ctx *i2c)
{
	/* open all soc debug i2c channel */
	tca9548a_set(TCA9548A1, 0xff);
	i2c_slave_register(i2c, &slave);
	/* enable interrupt */
	nvic_enable_irq(NVIC_I2C3_IRQ);
}

