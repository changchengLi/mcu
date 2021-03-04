/**
 * @file main.c
 * @author chao.wei
 * @brief application logical start
 */
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
#include <stdio.h>
#include <system.h>
#include <i2c_master.h>
#include <debug.h>
#include <chip.h>
#include <mp5475.h>
#include <pin.h>
#include <timer.h>
#include <mon.h>
#include <common.h>
#include <upgrade.h>
#include <mcu.h>
#include <pic.h>
#include <tca6416a.h>
#include <project.h>
#include <power.h>
#include <se5.h>
#include <sm5.h>
#include <loop.h>
#include <keyboard.h>
#include <eeprom.h>
#include <wdt.h>
#include <pcie.h>
#include <tmp451.h>

struct i2c_slave_ctx i2c1_slave_ctx;

int main(void)
{
	clock_init();
	system_init();

	debug("\nBITMAIN SOPHONE SM5MINI\n");

	if (get_stage() == RUN_STAGE_LOADER && check_app() == 0)
		app_start();

	led_init();

	i2c_master_init(I2C1);
	i2c_master_init(I2C2);

	tca6416a_probe();
	pic_probe();

	power_init();
	mp5475_init();
	power_on();
	chip_init();
	tmp451_init();

	debug("%s %s working at %s mode\n",
	      get_board_type_name(),
	      get_stage() == RUN_STAGE_LOADER ? "loader" : "application",
	      get_work_mode() == WORK_MODE_SOC ? "soc" : "pcie");

	nvic_enable_irq(NVIC_I2C1_IRQ);
	i2c_slave_init(&i2c1_slave_ctx, (void *)I2C1_BASE,
		       I2C1_OA1, I2C1_OA2, I2C1_OA2_MASK);

	/* auto detect or correct board type
	 * based on some characteristic on motherboard
	 */
	if (get_work_mode() == WORK_MODE_PCIE)
		set_board_type(SM5MP);
	else if (pic_available())
		set_board_type(SM5ME);
	else {
		if (tca6416a_available())
			set_board_type(
				get_declared_board_type() == SM5ME ?
				SM5ME : SM5MS);
		else
			/* on test boards */
			set_board_type(SM5MA);
	}

	/* but chip reset still be asserted */
	if (get_work_mode() == WORK_MODE_SOC) {
		if (get_board_type() == SM5ME)
			se5_init();
		else
			sm5_init();
	}

	mon_init();

	mcu_init(&i2c1_slave_ctx);
	eeprom_init(&i2c1_slave_ctx);
	wdt_init(&i2c1_slave_ctx);

	if (tca6416a_available())
		tca6416a_init(&i2c1_slave_ctx);

	if (pic_available()) {
		kbd_init(&i2c1_slave_ctx);
		pic_init(&i2c1_slave_ctx);
	}

	/* start i2c slaves */
	i2c_slave_start(&i2c1_slave_ctx);

	if (get_work_mode() == WORK_MODE_SOC)
		chip_enable();
	else
		pcie_init();

	/* never return */
	loop_start();

	return 0;
}

void i2c1_isr(void)
{
	i2c_slave_isr(&i2c1_slave_ctx);
}
