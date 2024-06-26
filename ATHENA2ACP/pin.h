/*
 * pin.h:
 *
 * (C) Copyright 2023 Sophgo Technology
 * Author: Donghao Zhao <donghao.zhao@sophgo.com>
 */

#ifndef __PIN_H__
#define __PIN_H__

#include <gd32e50x_gpio.h>

/* Port A definition */
#define PCB_VRE0_PORT			GPIOA
#define PCB_VRE0_PIN			GPIO_PIN_0
#define PCB_VRE0_EXTI			EXTI_0
#define BOM_VRE0_PORT			GPIOA
#define BOM_VRE0_PIN			GPIO_PIN_1
#define BOM_VRE0_EXTI			EXTI_1
#define NTC1_PORT			GPIOA
#define NTC1_PIN			GPIO_PIN_4
#define NTC1_EXTI			EXTI_4
#define NTC2_PORT			GPIOA
#define NTC2_PIN			GPIO_PIN_5
#define NTC2_EXTI			EXTI_5
#define FLIGHT_MODE_HASH_PORT		GPIOA
#define FLIGHT_MODE_HASH_PIN		GPIO_PIN_8
#define FLIGHT_MODE_HASH_EXTI		EXTI_8
#define GPIO_LTE_PWR_EN_PORT		GPIOA
#define GPIO_LTE_PWR_EN_PIN		GPIO_PIN_9
#define GPIO_LTE_PWR_EN_EXTI		EXTI_9
#define GPIO_LTE_RST_PORT		GPIOA
#define GPIO_LTE_RST_PIN		GPIO_PIN_10
#define GPIO_LTE_RST_EXTI		EXTI_10
#define PCIE0_SEL_PORT			GPIOA
#define PCIE0_SEL_PIN			GPIO_PIN_12
#define PCIE0_SEL_EXTI			EXTI_12

/* Port B definition */
#define MCU_BOOT1_PORT			GPIOB
#define MCU_BOOT1_PIN			GPIO_PIN_2
#define MCU_BOOT1_EXTI			EXTI_2
#define MCU_I2C0_SCL_PORT		GPIOB
#define MCU_I2C0_SCL_PIN		GPIO_PIN_6
#define MCU_I2C0_SCL_EXTI		EXTI_6
#define MCU_I2C0_SDA_PORT		GPIOB
#define MCU_I2C0_SDA_PIN		GPIO_PIN_7
#define MCU_I2C0_SDA_EXTI		EXTI_7
#define PWR_RSTN_H_PORT			GPIOB
#define PWR_RSTN_H_PIN			GPIO_PIN_13
#define PWR_RSTN_H_EXTI			EXTI_13
#define PWR_BUTTON1_H_PORT		GPIOB
#define PWR_BUTTON1_H_PIN		GPIO_PIN_14
#define PWR_BUTTON1_H_EXTI		EXTI_14
#define PWR_ON_H_PORT			GPIOB
#define PWR_ON_H_PIN			GPIO_PIN_15
#define PWR_ON_H_EXTI			EXTI_15

/* Port C definition */
#define I_12V_SYS_PORT			GPIOC
#define I_12V_SYS_PIN			GPIO_PIN_0
#define I_12V_SYS_EXTI			EXTI_0
#define MCU_HUB_RESET_HASH_PORT		GPIOC
#define MCU_HUB_RESET_HASH_PIN		GPIO_PIN_1
#define MCU_HUB_RESET_HASH_EXTI		EXTI_1
#define EN_VDD_1V8_PCIE_PORT		GPIOC
#define EN_VDD_1V8_PCIE_PIN		GPIO_PIN_6
#define EN_VDD_1V8_PCIE_EXTI		EXTI_6
#define EN_VDD_DDR_1V8_PORT		GPIOC
#define EN_VDD_DDR_1V8_PIN		GPIO_PIN_7
#define EN_VDD_DDR_1V8_EXTI		EXTI_7
#define KEY_POWER_ON_PORT		GPIOC
#define KEY_POWER_ON_PIN		GPIO_PIN_9
#define KEY_POWER_ON_EXTI		EXTI_9
#define POWER_LED_PORT			GPIOC
#define POWER_LED_PIN			GPIO_PIN_13
#define POWER_LED_EXTI			EXTI_13

/* Port D definition */
#define MCU_SSD_ALARM_LED_PORT		GPIOD
#define MCU_SSD_ALARM_LED_PIN		GPIO_PIN_0
#define MCU_SSD_ALARM_LED_EXTI		EXTI_0
#define MCU_SSD_STATUS_LED_PORT		GPIOD
#define MCU_SSD_STATUS_LED_PIN		GPIO_PIN_1
#define MCU_SSD_STATUS_LED_EXTI		EXTI_1
#define MCU_ALARM_LED_PORT		GPIOD
#define MCU_ALARM_LED_PIN		GPIO_PIN_2
#define MCU_ALARM_LED_EXTI		EXTI_2
#define MCU_STATUS_LED_PORT		GPIOD
#define MCU_STATUS_LED_PIN		GPIO_PIN_3
#define MCU_STATUS_LED_EXTI		EXTI_3
#define MCU_USART_TX_PORT		GPIOD
#define MCU_USART_TX_PIN		GPIO_PIN_5
#define MCU_USART_TX_EXTI		EXTI_5
#define MCU_USART_RX_PORT		GPIOD
#define MCU_USART_RX_PIN		GPIO_PIN_6
#define MCU_USART_RX_EXTI		EXTI_6
#define PWR_WAKEUP_H_PORT		GPIOD
#define PWR_WAKEUP_H_PIN		GPIO_PIN_9
#define PWR_WAKEUP_H_EXTI		EXTI_9
#define SYS_RSTN_H_HASH_PORT		GPIOD
#define SYS_RSTN_H_HASH_PIN		GPIO_PIN_10
#define SYS_RSTN_H_HASH_EXTI		EXTI_10
#define EN_VDD_1V8_PORT			GPIOD
#define EN_VDD_1V8_PIN			GPIO_PIN_11
#define EN_VDD_1V8_EXTI			EXTI_11
#define EN_VDD_DDR_1V1_PORT		GPIOD
#define EN_VDD_DDR_1V1_PIN		GPIO_PIN_12
#define EN_VDD_DDR_1V1_EXTI		EXTI_12
#define EN_VDD_DDR_0V6_PORT		GPIOD
#define EN_VDD_DDR_0V6_PIN		GPIO_PIN_13
#define EN_VDD_DDR_0V6_EXTI		EXTI_13
#define EN_VDD_0V8_PORT			GPIOD
#define EN_VDD_0V8_PIN			GPIO_PIN_14
#define EN_VDD_0V8_EXTI			EXTI_14
#define EN_VDD_0V8_PCIE_PORT		GPIOD
#define EN_VDD_0V8_PCIE_PIN		GPIO_PIN_15
#define EN_VDD_0V8_PCIE_EXTI		EXTI_15

/* Port E definition */
#define EN_VDDC_0V8_PORT		GPIOE
#define EN_VDDC_0V8_PIN			GPIO_PIN_2
#define EN_VDDC_0V8_EXTI		EXTI_2
#define EN_VDD_5V0_PORT			GPIOE
#define EN_VDD_5V0_PIN			GPIO_PIN_3
#define EN_VDD_5V0_EXTI			EXTI_3
#define EN_VDD_3V3_PORT			GPIOE
#define EN_VDD_3V3_PIN			GPIO_PIN_4
#define EN_VDD_3V3_EXTI			EXTI_4
#define PG_VDDC_0V8_PORT		GPIOE
#define PG_VDDC_0V8_PIN			GPIO_PIN_5
#define PG_VDDC_0V8_EXTI		EXTI_5
#define EN_12V_SYS_PORT			GPIOE
#define EN_12V_SYS_PIN			GPIO_PIN_6
#define EN_12V_SYS_EXTI			EXTI_6
#define OVER_TEMP_PORT			GPIOE
#define OVER_TEMP_PIN			GPIO_PIN_10
#define OVER_TEMP_EXTI			EXTI_10
#define BT_M2_EN_PORT			GPIOE
#define BT_M2_EN_PIN			GPIO_PIN_11
#define BT_M2_EN_EXTI			EXTI_11
#define W_DISABLE1_CTRL_PORT		GPIOE
#define W_DISABLE1_CTRL_PIN		GPIO_PIN_12
#define W_DISABLE1_CTRL_EXTI		EXTI_12
#define EN_VDD_0V8_RTC_PORT		GPIOE
#define EN_VDD_0V8_RTC_PIN		GPIO_PIN_13
#define EN_VDD_0V8_RTC_EXTI		EXTI_13
#define EN_VDD_1V8_RTC_PORT		GPIOE
#define EN_VDD_1V8_RTC_PIN		GPIO_PIN_14
#define EN_VDD_1V8_RTC_EXTI		EXTI_14
#define SD_PW_SEL_PORT			GPIOE
#define SD_PW_SEL_PIN			GPIO_PIN_15
#define SD_PW_SEL_EXTI			EXTI_15

#endif /* __PIN_H__ */
