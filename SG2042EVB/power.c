#include <gd32e50x_gpio.h>
#include <timer.h>
#include <power.h>
#include <debug.h>
#include <common.h>
#include <upgrade.h>
#include <board_power.h>
#include <system.h>
#include <stdio.h>
#include <stdbool.h>
#include <timer.h>
#include <chip.h>
#include <i2c-slaves/slt.h>
#include <loop.h>
#include <board_power_impl.h>

/* in us */
#define NODE_CHECK_TIMEOUT	(10 * 1000)

int power_is_on;

static int node_check(struct power_node const *node)
{
	return 0;

	int err = 0;
	uint32_t port = node->param[0];
	uint16_t pin = node->param[1];

	timer_start(NODE_CHECK_TIMEOUT);

	while (gpio_get(port, pin) == 0) {
		if (timer_is_timeout()) {
			err = -1;
			break;
		}
	}
	timer_stop();

	return err;
}

static int node_on(struct power_node const *node)
{
	int err = 0;

	debug("%s ", node->name);

	if (node->type == NODE_TYPE_ENABLE) {
		gpio_set(node->param[0], node->param[1]);
	} else if (node->type == NODE_TYPE_CHECK) {
		err = node_check(node);
	} else {
		power_on_func func = (power_on_func)node->param[0];

		if (func)
			err = func();
	}

	debug("[%c]\n", err ? 'X' : 'O');

	if (err == 0 && node->delay)
		timer_udelay(node->delay);

	return err;
}

static void node_off(struct power_node const *node)
{
	debug("%s\n", node->name);

	/* skip check nodes */
	if (node->type == NODE_TYPE_ENABLE) {
		gpio_clear(node->param[0], node->param[1]);
	} else if (node->type == NODE_TYPE_FUNCTION) {
		power_off_func func = (power_off_func)node->param[1];

		if (func)
			func();
	}
}

int node_seqon(struct power_node const *node, unsigned int num)
{
	int err, i;

	err = 0;

	for (i = 0; i < num; ++i) {
		err = node_on(node + i);
		if (err)
			break;
	}

	/* donot power off */
#if 0
	if (err) {
		--i;
		while (i >= 0) {
			node_off(node + i);
			--i;
		}
	}
#endif
	return err;
}

void node_seqoff(struct power_node const *node, unsigned int num)
{
	int i;

	for (i = num - 1; i >= 0; --i)
		node_off(node + i);
}

void power_on(void)
{
	int err = node_seqon(board_power_nodes, ARRAY_SIZE(board_power_nodes));

	if (err) {
		led_set_frequency(5);
		debug("power on failed node: %d\n", err);
	} else {
		led_set_frequency(1);
		led_control(1, ON);
		chip_enable();
		power_is_on = true;
	}
}

void power_off(void)
{
	slt_reset();
	chip_disable();
	power_is_on = false;
	node_seqoff(board_power_nodes, ARRAY_SIZE(board_power_nodes));
	led_set_frequency(LED_FREQ_ALWAYS_OFF);
	led_control(1, OFF);
}

void power_init(void)
{
	led_set_frequency(LED_FREQ_ALWAYS_OFF);
	power_is_on = false;
	loop_add(board_power_control);
}

int power_status(void)
{
	return power_is_on;
}
