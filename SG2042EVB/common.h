#ifndef __COMMON_H__
#define __COMMON_H__

#include <pin.h>
#include <gd32e50x.h>

#define MCU_SW_VER	0

#define false 0
#define true 1

#define ARRAY_SIZE(array)	(sizeof(array) / sizeof(array[0]))
#define ROUND_UP(x, n)		(((x) + ((n) - 1)) / n)

#define MCU_SLAVE_ADDR		0x17

#define LED_FREQ_ALWAYS_ON	1000
#define LED_FREQ_ALWAYS_OFF	0

enum {
	DDR_TYPE_LPDDR4X = 0,
	DDR_TYPE_LPDDR4 = 1,
};

uint8_t get_firmware_version(void);
int get_work_mode(void);
void board_init(void);
uint8_t get_ddr_type(void);

int get_board_temp(void);
int get_soc_temp(void);
void set_board_temp(int temp);
void set_soc_temp(int temp);
int get_ntc_tmp(void);
char *get_board_type_name();
uint8_t get_board_type(void);
void led_init(void);
void led_on(void);
void led_off(void);
void led_set_frequency(unsigned long freq);

/* remap libopencm3 to libgd */
#define gpio_clear	gpio_bit_reset
#define gpio_set	gpio_bit_set
#define gpio_get	gpio_input_bit_get

#define nvic_disable_irq(irq)	nvic_irq_disable(irq)
#define nvic_enable_irq(irq)	nvic_irq_enable(irq, 0, 0)

#define exti_reset_request	exti_interrupt_flag_clear

#endif
