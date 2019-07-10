/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SYS_RST_X_Pin GPIO_PIN_13
#define SYS_RST_X_GPIO_Port GPIOC
#define PCIE_RST_MCU_Pin GPIO_PIN_14
#define PCIE_RST_MCU_GPIO_Port GPIOC
#define PCIE_RST_MCU_EXTI_IRQn EXTI4_15_IRQn
#define PG_CORE_Pin GPIO_PIN_15
#define PG_CORE_GPIO_Port GPIOC
#define PG_CORE_EXTI_IRQn EXTI4_15_IRQn
#define EN_3P3_Pin GPIO_PIN_0
#define EN_3P3_GPIO_Port GPIOH
#define EN_5V_Pin GPIO_PIN_1
#define EN_5V_GPIO_Port GPIOH
#define PCB_VER0_Pin GPIO_PIN_0
#define PCB_VER0_GPIO_Port GPIOA
#define PCB_VER1_Pin GPIO_PIN_1
#define PCB_VER1_GPIO_Port GPIOA
#define BOM_VER0_Pin GPIO_PIN_2
#define BOM_VER0_GPIO_Port GPIOA
#define BOM_VER1_Pin GPIO_PIN_3
#define BOM_VER1_GPIO_Port GPIOA
#define MCU_LED_Pin GPIO_PIN_5
#define MCU_LED_GPIO_Port GPIOA
#define MCU_CPLD_ERR_Pin GPIO_PIN_6
#define MCU_CPLD_ERR_GPIO_Port GPIOA
#define GPIO1_Pin GPIO_PIN_7
#define GPIO1_GPIO_Port GPIOA
#define EN0_ISL68127_Pin GPIO_PIN_0
#define EN0_ISL68127_GPIO_Port GPIOB
#define EN1_ISL68127_Pin GPIO_PIN_1
#define EN1_ISL68127_GPIO_Port GPIOB
#define EN_PMIC_Pin GPIO_PIN_2
#define EN_PMIC_GPIO_Port GPIOB
#define PMIC_SCL_Pin GPIO_PIN_10
#define PMIC_SCL_GPIO_Port GPIOB
#define PMIC_SDA_Pin GPIO_PIN_11
#define PMIC_SDA_GPIO_Port GPIOB
#define EN_VDDIO18_Pin GPIO_PIN_12
#define EN_VDDIO18_GPIO_Port GPIOB
#define EN_VDDIO33_Pin GPIO_PIN_13
#define EN_VDDIO33_GPIO_Port GPIOB
#define EN_VDD_PHY_Pin GPIO_PIN_14
#define EN_VDD_PHY_GPIO_Port GPIOB
#define EN_VDD_PCIE_Pin GPIO_PIN_15
#define EN_VDD_PCIE_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOA
#define GPIO2_Pin GPIO_PIN_9
#define GPIO2_GPIO_Port GPIOA
#define GPIO3_Pin GPIO_PIN_10
#define GPIO3_GPIO_Port GPIOA
#define P08_PWR_GOOD_Pin GPIO_PIN_11
#define P08_PWR_GOOD_GPIO_Port GPIOA
#define DDR_PWR_GOOD_Pin GPIO_PIN_12
#define DDR_PWR_GOOD_GPIO_Port GPIOA
#define TEMP_ALR_N_Pin GPIO_PIN_15
#define TEMP_ALR_N_GPIO_Port GPIOA
#define EN_VQPS18_Pin GPIO_PIN_3
#define EN_VQPS18_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_4
#define I2C1_SDA_GPIO_Port GPIOB
#define TWARN_VDD_TPU_Pin GPIO_PIN_5
#define TWARN_VDD_TPU_GPIO_Port GPIOB
#define TWARN_VDD_TPU_EXTI_IRQn EXTI4_15_IRQn
#define EN_VDD_TPU_MEM_Pin GPIO_PIN_6
#define EN_VDD_TPU_MEM_GPIO_Port GPIOB
#define TPU_I2C_ADD3_Pin GPIO_PIN_7
#define TPU_I2C_ADD3_GPIO_Port GPIOB
#define CPLD_MCU_SCL_Pin GPIO_PIN_8
#define CPLD_MCU_SCL_GPIO_Port GPIOB
#define CPLD_MCU_SDA_Pin GPIO_PIN_9
#define CPLD_MCU_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
typedef struct I2C_REGS_t
{
	uint8_t vender;
	uint8_t sw_ver;
	uint8_t hw_ver;
	uint8_t cmd_reg;

	uint8_t temp1684;
	uint8_t temp_board;
	uint8_t intr_status1;
	uint8_t intr_status2;

	uint8_t intr_mask1;
	uint8_t intr_mask2;
	uint8_t rst_1684_times;
	uint8_t uptime0;

	uint8_t uptime1;
	uint8_t cause_pwr_down;
	uint8_t rtc[6];
	uint8_t sn[4];
	uint8_t mac0[8];
	uint8_t mac1[8];
	uint8_t reserved[8];
}I2C_REGS;

I2C_REGS i2c_regs;

#define REG_NUMBER			32
#define REG_VENDER			0x00
#define REG_SW_VER			0x01
#define REG_HW_VER			0x02
#define REG_CMD_REG			0x03

#define REG_TEMP1684		0X04
#define REG_TEMP_BOARD		0x05
#define REG_INTR_STATUS1	0x06
#define REG_INTR_STATUS2	0x07

#define REG_INTR_MASK1		0x08
#define REG_INTR_MASK2		0x09
#define REG_1684_RST_TIMES	0x0a
#define REG_UPTIME0			0x0b

#define REG_UPTIME1			0x0c
#define REG_CAUSE_PWR_DOWN	0x0d
#define REG_SYS_RTC_SEC		0x0e
#define REG_SYS_RTC_MIN		0x0f

#define REG_SYS_RTC_HOUR	0x10
#define REG_SYS_RTC_DAY		0x11
#define REG_SYS_RTC_MON		0x12
#define REG_SYS_RTC_YEAR	0x13

//SN  [17:14]   4*8 BIT
#define REG_SN				0x14
//MAC [1F:18]
#define REG_MAC0			0x18
//MAC [27:20]
#define REG_MAC1			0x20

#define BIT0   (0X01 << 0)
#define BIT1   (0X01 << 1)
#define BIT2   (0X01 << 2)
#define BIT3   (0X01 << 3)
#define BIT4   (0X01 << 4)
#define BIT5   (0X01 << 5)
#define BIT6   (0X01 << 6)
#define BIT7   (0X01 << 7)

#define BOARD_OVER_TEMP BIT3
#define BM1684_OVER_TEMP BIT4
#define CPLD_CLR_ERR BIT5
#define CPLD_SET_ERR BIT7


//CPLD Command
#define CMD_CPLD_PWR_ON			0x01       //1684 power on
#define CMD_CPLD_PWR_DOWN		0x02	   //1684 power down
#define CMD_CPLD_1684RST		0x03       //reset 1684
#define CMD_CPLD_SWRST			0x04	   //soft resetting
#define CMD_CPLD_CLR			0x05       // clean MCU_ERR_INT, set 0.
//BM1684 Command
#define CMD_BM1684_REBOOT		0x06       // power is always on
#define CMD_BM1684_RST			0x07       // power down

//EEPROM  FLASH
#define EEPROM_BASE_ADDR	0x08080000
#define EEPROM_BANK_SIZE	0x0BFF
#define EEPROM_BANK1_START	0X08080000
#define EEPROM_BANK1_END	0x08080BFF
#define EEPROM_BANK2_START	0X08080C00
#define EEPROM_BANK2_END	0x080817FF
//
//uint32_t writeFlashData = 0x55aa55aa;
//uint8_t readFlashData[4] = {0};
//uint32_t addr = 0x08080000;
//uint16_t addr_offset = 0x0;
//
/*
 *  SN Addr  : EEPROM_BANK1_START
 *  MAC0 Addr: EEPROM_BANK1_START +  4
 *  MAC1 Addr: EEPROM_BANK1_START + 12
 */
#define SN_Addr EEPROM_BANK1_START
#define MAC0_Addr (EEPROM_BANK1_START +  4)
#define MAC1_Addr (EEPROM_BANK1_START +  12)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
