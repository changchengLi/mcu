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
#define I_DDR23_VDDQ_1V2_PORT		GPIOA
#define I_DDR23_VDDQ_1V2_PIN		GPIO_PIN_2
#define I_DDR23_VDDQ_1V2_EXTI		EXTI_2
#define PCB_VRE0_PORT		GPIOA
#define PCB_VRE0_PIN		GPIO_PIN_3
#define PCB_VRE0_EXTI		EXTI_3
#define I_VQPS18_PORT		GPIOA
#define I_VQPS18_PIN		GPIO_PIN_4
#define I_VQPS18_EXTI		EXTI_4
#define I_VDD_PLL_0V8_PORT		GPIOA
#define I_VDD_PLL_0V8_PIN		GPIO_PIN_5
#define I_VDD_PLL_0V8_EXTI		EXTI_5
#define I_VDD_PCIE_D_0V8_PORT		GPIOA
#define I_VDD_PCIE_D_0V8_PIN		GPIO_PIN_6
#define I_VDD_PCIE_D_0V8_EXTI		EXTI_6
#define I_VDD_PCIE_C_0V8_PORT		GPIOA
#define I_VDD_PCIE_C_0V8_PIN		GPIO_PIN_7
#define I_VDD_PCIE_C_0V8_EXTI		EXTI_7
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
#define STATUS_LED0_PORT		GPIOA
#define STATUS_LED0_PIN		GPIO_PIN_15
#define STATUS_LED0_EXTI		EXTI_15

/* port B definition */
#define I_5V_PORT		GPIOB
#define I_5V_PIN		GPIO_PIN_0
#define I_5V_EXTI		EXTI_0
#define I_VDD_12V_PORT		GPIOB
#define I_VDD_12V_PIN		GPIO_PIN_1
#define I_VDD_12V_EXTI		EXTI_1
#define MCU_BOOT1_PORT		GPIOB
#define MCU_BOOT1_PIN		GPIO_PIN_2
#define MCU_BOOT1_EXTI		EXTI_2
#define MCU_I2C1_SCL_PORT		GPIOB
#define MCU_I2C1_SCL_PIN		GPIO_PIN_6
#define MCU_I2C1_SCL_EXTI		EXTI_6
#define MCU_I2C1_SDA_PORT		GPIOB
#define MCU_I2C1_SDA_PIN		GPIO_PIN_7
#define MCU_I2C1_SDA_EXTI		EXTI_7
#define MCU_I2C2_SCL_PORT		GPIOB
#define MCU_I2C2_SCL_PIN		GPIO_PIN_10
#define MCU_I2C2_SCL_EXTI		EXTI_10
#define MCU_I2C2_SDA_PORT		GPIOB
#define MCU_I2C2_SDA_PIN		GPIO_PIN_11
#define MCU_I2C2_SDA_EXTI		EXTI_11
#define PG_DDR_VDD_0V8_PORT		GPIOB
#define PG_DDR_VDD_0V8_PIN		GPIO_PIN_12
#define PG_DDR_VDD_0V8_EXTI		EXTI_12
#define PG_VDDC_PORT		GPIOB
#define PG_VDDC_PIN		GPIO_PIN_13
#define PG_VDDC_EXTI		EXTI_13
#define EN_DDR23_VTT_0V6_PORT		GPIOB
#define EN_DDR23_VTT_0V6_PIN		GPIO_PIN_14
#define EN_DDR23_VTT_0V6_EXTI		EXTI_14
#define EN_DDR01_VTT_0V6_PORT		GPIOB
#define EN_DDR01_VTT_0V6_PIN		GPIO_PIN_15
#define EN_DDR01_VTT_0V6_EXTI		EXTI_15

/* port C definition */
#define I_VDD_RGMII_1V8_PORT		GPIOC
#define I_VDD_RGMII_1V8_PIN		GPIO_PIN_0
#define I_VDD_RGMII_1V8_EXTI		EXTI_0
#define I_VDD_EMMC_1V8_PORT		GPIOC
#define I_VDD_EMMC_1V8_PIN		GPIO_PIN_1
#define I_VDD_EMMC_1V8_EXTI		EXTI_1
#define I_VDD_EMMC_3V3_PORT		GPIOC
#define I_VDD_EMMC_3V3_PIN		GPIO_PIN_2
#define I_VDD_EMMC_3V3_EXTI		EXTI_2
#define I_VDDC_PORT		GPIOC
#define I_VDDC_PIN		GPIO_PIN_3
#define I_VDDC_EXTI		EXTI_3
#define I_VDD_PCIE_H_1V8_PORT		GPIOC
#define I_VDD_PCIE_H_1V8_PIN		GPIO_PIN_4
#define I_VDD_PCIE_H_1V8_EXTI		EXTI_4
#define I_VDDIO18_PORT		GPIOC
#define I_VDDIO18_PIN		GPIO_PIN_5
#define I_VDDIO18_EXTI		EXTI_5
#define PG_DDR01_VDDQ_1V2_PORT		GPIOC
#define PG_DDR01_VDDQ_1V2_PIN		GPIO_PIN_6
#define PG_DDR01_VDDQ_1V2_EXTI		EXTI_6
#define EN_DDR23_VDDQ_1V2_PORT		GPIOC
#define EN_DDR23_VDDQ_1V2_PIN		GPIO_PIN_7
#define EN_DDR23_VDDQ_1V2_EXTI		EXTI_7
#define EN_DDR01_VDDQ_1V2_PORT		GPIOC
#define EN_DDR01_VDDQ_1V2_PIN		GPIO_PIN_8
#define EN_DDR01_VDDQ_1V2_EXTI		EXTI_8
#define MCU_I2C3_SDA_PORT		GPIOC
#define MCU_I2C3_SDA_PIN		GPIO_PIN_9
#define MCU_I2C3_SDA_EXTI		EXTI_9
#define MCU_ATX_ON_PORT		GPIOC
#define MCU_ATX_ON_PIN		GPIO_PIN_12
#define MCU_ATX_ON_EXTI		EXTI_12
#define MCU_PS_ON_PORT		GPIOC
#define MCU_PS_ON_PIN		GPIO_PIN_13
#define MCU_PS_ON_EXTI		EXTI_13

/* port D definition */
#define SLOT2_PRSENT2_2_PORT		GPIOD
#define SLOT2_PRSENT2_2_PIN		GPIO_PIN_2
#define SLOT2_PRSENT2_2_EXTI		EXTI_2
#define SLOT2_PRSENT2_1_PORT		GPIOD
#define SLOT2_PRSENT2_1_PIN		GPIO_PIN_3
#define SLOT2_PRSENT2_1_EXTI		EXTI_3
#define SLOT2_PRSENT2_0_PORT		GPIOD
#define SLOT2_PRSENT2_0_PIN		GPIO_PIN_4
#define SLOT2_PRSENT2_0_EXTI		EXTI_4
#define MCU_USART1_TX_PORT		GPIOD
#define MCU_USART1_TX_PIN		GPIO_PIN_5
#define MCU_USART1_TX_EXTI		EXTI_5
#define MCU_USART1_RX_PORT		GPIOD
#define MCU_USART1_RX_PIN		GPIO_PIN_6
#define MCU_USART1_RX_EXTI		EXTI_6
#define EN_VDD_3V3_PORT		GPIOD
#define EN_VDD_3V3_PIN		GPIO_PIN_8
#define EN_VDD_3V3_EXTI		EXTI_8
#define TEST_MOD_PORT		GPIOD
#define TEST_MOD_PIN		GPIO_PIN_9
#define TEST_MOD_EXTI		EXTI_9
#define MCU_BOOT_SEL6_H_PORT		GPIOD
#define MCU_BOOT_SEL6_H_PIN		GPIO_PIN_10
#define MCU_BOOT_SEL6_H_EXTI		EXTI_10
#define EN_VQPS18_PORT		GPIOD
#define EN_VQPS18_PIN		GPIO_PIN_11
#define EN_VQPS18_EXTI		EXTI_11
#define CORPOWER_OK_PORT		GPIOD
#define CORPOWER_OK_PIN		GPIO_PIN_12
#define CORPOWER_OK_EXTI		EXTI_12
#define MCU_OK_PORT		GPIOD
#define MCU_OK_PIN		GPIO_PIN_13
#define MCU_OK_EXTI		EXTI_13
#define EN_DDR23_VPP_2V5_PORT		GPIOD
#define EN_DDR23_VPP_2V5_PIN		GPIO_PIN_14
#define EN_DDR23_VPP_2V5_EXTI		EXTI_14
#define PG_DDR23_VDDQ_1V2_PORT		GPIOD
#define PG_DDR23_VDDQ_1V2_PIN		GPIO_PIN_15
#define PG_DDR23_VDDQ_1V2_EXTI		EXTI_15

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
#define SLOT0_PRSENT2_0_PORT		GPIOE
#define SLOT0_PRSENT2_0_PIN		GPIO_PIN_7
#define SLOT0_PRSENT2_0_EXTI		EXTI_7
#define SLOT0_PRSENT2_1_PORT		GPIOE
#define SLOT0_PRSENT2_1_PIN		GPIO_PIN_8
#define SLOT0_PRSENT2_1_EXTI		EXTI_8
#define SLOT0_PRSENT2_2_PORT		GPIOE
#define SLOT0_PRSENT2_2_PIN		GPIO_PIN_9
#define SLOT0_PRSENT2_2_EXTI		EXTI_9
#define SLOT0_PRSENT2_3_PORT		GPIOE
#define SLOT0_PRSENT2_3_PIN		GPIO_PIN_10
#define SLOT0_PRSENT2_3_EXTI		EXTI_10
#define SLOT1_PRSENT2_0_PORT		GPIOE
#define SLOT1_PRSENT2_0_PIN		GPIO_PIN_11
#define SLOT1_PRSENT2_0_EXTI		EXTI_11
#define SLOT1_PRSENT2_1_PORT		GPIOE
#define SLOT1_PRSENT2_1_PIN		GPIO_PIN_12
#define SLOT1_PRSENT2_1_EXTI		EXTI_12
#define SLOT1_PRSENT2_2_PORT		GPIOE
#define SLOT1_PRSENT2_2_PIN		GPIO_PIN_13
#define SLOT1_PRSENT2_2_EXTI		EXTI_13
#define PWR_OK_C_PORT		GPIOE
#define PWR_OK_C_PIN		GPIO_PIN_14
#define PWR_OK_C_EXTI		EXTI_14
#define MCU_LPC_RST_PORT		GPIOE
#define MCU_LPC_RST_PIN		GPIO_PIN_15
#define MCU_LPC_RST_EXTI		EXTI_15

#endif
/* AUTO GENERATED CODE END */
