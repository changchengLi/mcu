/* THIS IS AUTO GENERATED CODE */

#ifndef __PIN_H__
#define __PIN_H__

#include <gd32e50x_gpio.h>

/* port A definition */
#define I_DDR_VDD_0V8_PORT		GPIOA
#define I_DDR_VDD_0V8_PIN		GPIO_PIN_0
#define I_DDR_VDD_0V8_EXTI		EXTI_0
#define I_DDR01_VDDQ_1V2_PORT		GPIOA
#define I_DDR01_VDDQ_1V2_PIN		GPIO_PIN_1
#define I_DDR01_VDDQ_1V2_EXTI		EXTI_1
#define I_VDD_EMMC_1V8_PORT		GPIOA
#define I_VDD_EMMC_1V8_PIN		GPIO_PIN_2
#define I_VDD_EMMC_1V8_EXTI		EXTI_2
#define I_VDD_EMMC_3V3_PORT		GPIOA
#define I_VDD_EMMC_3V3_PIN		GPIO_PIN_3
#define I_VDD_EMMC_3V3_EXTI		EXTI_3
#define I_VDD_PLL_0V8_PORT		GPIOA
#define I_VDD_PLL_0V8_PIN		GPIO_PIN_7
#define I_VDD_PLL_0V8_EXTI		EXTI_7
#define MCU_I2C3_SCL_PORT		GPIOA
#define MCU_I2C3_SCL_PIN		GPIO_PIN_8
#define MCU_I2C3_SCL_EXTI		EXTI_8
#define EN_DDR01_VPP_2V5_PORT		GPIOA
#define EN_DDR01_VPP_2V5_PIN		GPIO_PIN_9
#define EN_DDR01_VPP_2V5_EXTI		EXTI_9
#define EN_VDDIO33_PORT		GPIOA
#define EN_VDDIO33_PIN		GPIO_PIN_10
#define EN_VDDIO33_EXTI		EXTI_10
#define EN_DDR_VDD_0V8_PORT		GPIOA
#define EN_DDR_VDD_0V8_PIN		GPIO_PIN_11
#define EN_DDR_VDD_0V8_EXTI		EXTI_11
#define EN_VDDC_PORT		GPIOA
#define EN_VDDC_PIN		GPIO_PIN_12
#define EN_VDDC_EXTI		EXTI_12
#define MCU_SWDIO_PORT		GPIOA
#define MCU_SWDIO_PIN		GPIO_PIN_13
#define MCU_SWDIO_EXTI		EXTI_13
#define MCU_SWCLK_PORT		GPIOA
#define MCU_SWCLK_PIN		GPIO_PIN_14
#define MCU_SWCLK_EXTI		EXTI_14
#define MCU_HEALTH_STATUS_PORT		GPIOA
#define MCU_HEALTH_STATUS_PIN		GPIO_PIN_15
#define MCU_HEALTH_STATUS_EXTI		EXTI_15

/* port B definition */
#define I_DDR01_VPP_2V5_PORT		GPIOB
#define I_DDR01_VPP_2V5_PIN		GPIO_PIN_0
#define I_DDR01_VPP_2V5_EXTI		EXTI_0
#define I_DDR01_VTT_0V6_PORT		GPIOB
#define I_DDR01_VTT_0V6_PIN		GPIO_PIN_1
#define I_DDR01_VTT_0V6_EXTI		EXTI_1
#define MCU_BOOT1_PORT		GPIOB
#define MCU_BOOT1_PIN		GPIO_PIN_2
#define MCU_BOOT1_EXTI		EXTI_2
#define MCU_I2C1_SCL_PORT		GPIOB
#define MCU_I2C1_SCL_PIN		GPIO_PIN_6
#define MCU_I2C1_SCL_EXTI		EXTI_6
#define MCU_I2C1_SDA_PORT		GPIOB
#define MCU_I2C1_SDA_PIN		GPIO_PIN_7
#define MCU_I2C1_SDA_EXTI		EXTI_7
#define MCU_USART2_TX_PORT		GPIOB
#define MCU_USART2_TX_PIN		GPIO_PIN_10
#define MCU_USART2_TX_EXTI		EXTI_10
#define MCU_USART2_RX_PORT		GPIOB
#define MCU_USART2_RX_PIN		GPIO_PIN_11
#define MCU_USART2_RX_EXTI		EXTI_11
#define PG_DDR_VDD_0V8_PORT		GPIOB
#define PG_DDR_VDD_0V8_PIN		GPIO_PIN_12
#define PG_DDR_VDD_0V8_EXTI		EXTI_12
#define PG_VDDC_PORT		GPIOB
#define PG_VDDC_PIN		GPIO_PIN_13
#define PG_VDDC_EXTI		EXTI_13
#define EN_VQPS18_PORT		GPIOB
#define EN_VQPS18_PIN		GPIO_PIN_14
#define EN_VQPS18_EXTI		EXTI_14
#define EN_DDR01_VTT_0V6_PORT		GPIOB
#define EN_DDR01_VTT_0V6_PIN		GPIO_PIN_15
#define EN_DDR01_VTT_0V6_EXTI		EXTI_15

/* port C definition */
#define PCB_VER0_PORT		GPIOC
#define PCB_VER0_PIN		GPIO_PIN_0
#define PCB_VER0_EXTI		EXTI_0
#define BOM_VER0_PORT		GPIOC
#define BOM_VER0_PIN		GPIO_PIN_1
#define BOM_VER0_EXTI		EXTI_1
#define I_VDD_12V_PORT		GPIOC
#define I_VDD_12V_PIN		GPIO_PIN_4
#define I_VDD_12V_EXTI		EXTI_4
#define I_5V_PORT		GPIOC
#define I_5V_PIN		GPIO_PIN_5
#define I_5V_EXTI		EXTI_5
#define DDR0_EVENT_MCU_PORT		GPIOC
#define DDR0_EVENT_MCU_PIN		GPIO_PIN_6
#define DDR0_EVENT_MCU_EXTI		EXTI_6
#define PG_DDR01_VDDQ_1V2_PORT		GPIOC
#define PG_DDR01_VDDQ_1V2_PIN		GPIO_PIN_7
#define PG_DDR01_VDDQ_1V2_EXTI		EXTI_7
#define EN_DDR01_VDDQ_1V2_PORT		GPIOC
#define EN_DDR01_VDDQ_1V2_PIN		GPIO_PIN_8
#define EN_DDR01_VDDQ_1V2_EXTI		EXTI_8
#define MCU_I2C3_SDA_PORT		GPIOC
#define MCU_I2C3_SDA_PIN		GPIO_PIN_9
#define MCU_I2C3_SDA_EXTI		EXTI_9
#define POWER_STATUS_PORT		GPIOC
#define POWER_STATUS_PIN		GPIO_PIN_13
#define POWER_STATUS_EXTI		EXTI_13

/* port D definition */
#define MCU_USART1_TX_PORT		GPIOD
#define MCU_USART1_TX_PIN		GPIO_PIN_5
#define MCU_USART1_TX_EXTI		EXTI_5
#define MCU_USART1_RX_PORT		GPIOD
#define MCU_USART1_RX_PIN		GPIO_PIN_6
#define MCU_USART1_RX_EXTI		EXTI_6
#define EN_VDD_3V3_PORT		GPIOD
#define EN_VDD_3V3_PIN		GPIO_PIN_8
#define EN_VDD_3V3_EXTI		EXTI_8
#define PWR_BUTTON_H_PORT		GPIOD
#define PWR_BUTTON_H_PIN		GPIO_PIN_9
#define PWR_BUTTON_H_EXTI		EXTI_9
#define PLSRST_OUT_PORT		GPIOD
#define PLSRST_OUT_PIN		GPIO_PIN_10
#define PLSRST_OUT_EXTI		EXTI_10
#define COREPOWER_OK_PORT		GPIOD
#define COREPOWER_OK_PIN		GPIO_PIN_11
#define COREPOWER_OK_EXTI		EXTI_11
#define PLL_LOCKO_PORT		GPIOD
#define PLL_LOCKO_PIN		GPIO_PIN_12
#define PLL_LOCKO_EXTI		EXTI_12
#define MCU_OK_PORT		GPIOD
#define MCU_OK_PIN		GPIO_PIN_13
#define MCU_OK_EXTI		EXTI_13
#define PWR_OK_PORT		GPIOD
#define PWR_OK_PIN		GPIO_PIN_14
#define PWR_OK_EXTI		EXTI_14
#define EN_ATX_PWR_PORT		GPIOD
#define EN_ATX_PWR_PIN		GPIO_PIN_15
#define EN_ATX_PWR_EXTI		EXTI_15

/* port E definition */
#define EN_VDD_PCIE_H_1V8_PORT		GPIOE
#define EN_VDD_PCIE_H_1V8_PIN		GPIO_PIN_2
#define EN_VDD_PCIE_H_1V8_EXTI		EXTI_2
#define EN_VDD_PCIE_D_0V8_PORT		GPIOE
#define EN_VDD_PCIE_D_0V8_PIN		GPIO_PIN_3
#define EN_VDD_PCIE_D_0V8_EXTI		EXTI_3
#define EN_VDD_PLL_0V8_PORT		GPIOE
#define EN_VDD_PLL_0V8_PIN		GPIO_PIN_4
#define EN_VDD_PLL_0V8_EXTI		EXTI_4
#define EN_VDDIO18_PORT		GPIOE
#define EN_VDDIO18_PIN		GPIO_PIN_5
#define EN_VDDIO18_EXTI		EXTI_5
#define SYS_RST_X_H_PORT		GPIOE
#define SYS_RST_X_H_PIN		GPIO_PIN_6
#define SYS_RST_X_H_EXTI		EXTI_6

#endif
/* AUTO GENERATED CODE END */
