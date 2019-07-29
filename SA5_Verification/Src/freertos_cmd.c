/*****************************************************************************
 * 
 * @filepath 	/SA5_Verification/Src/freertos_cmd.c
 * 
 * @project 	SA5_Verification
 * 
 * @brief 		This file contains commands that been used in rtos shell
 * 
 * @date 		May 31, 2019
 * 
 * @author		ziyi.xiong
 *
 ****************************************************************************/
/** Includes **/
#include "freertos_cmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "cmsis_os.h"
#include "i2c.h"
#include "usart.h"
#include "adc.h"

#include "main.h"

/** Declarations **/
extern const uint8_t VERSION;
extern uint8_t reg[16];
extern volatile testStage tStage;

static BaseType_t prvVersionCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvPowerUpCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvResetCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvShutDownCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvGetVccCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvReadCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvWriteCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvBTempCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvCTempCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvGetRegCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);

static BaseType_t prvGetSNCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvSetSNCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvGetMac0Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvGetMac1Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvSetMac0Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvSetMac1Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvI2cMcuCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvI2c1684Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvI2CDbgCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvSlotIDCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvUart0Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvUart1Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvUart2Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvPcieCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvSdioCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvErrCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvRegReadCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvI2CDbgAddrCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvGPIOCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);
static BaseType_t prvSUartCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString);


static uint8_t isHexChar(char data);

static const CLI_Command_Definition_t xVersionCommand = {
		"version",
		"\r\nversion:\r\n Provide the firmware version information \r\n",
		prvVersionCommand,
		0 };
static const CLI_Command_Definition_t xResetCommand = {
		"reset",
		"\r\nreset:\r\n Reset the SA5 core board MCU\r\n",
		prvResetCommand,
		0 };
static const CLI_Command_Definition_t xPowerUpCommand = {
		"powerup",
		"\r\npowerup:\r\n Power up the SA5 core board \r\n",
		prvPowerUpCommand,
		0 };
static const CLI_Command_Definition_t xShutDownCommand = {
		"shutdown",
		"\r\nshutdown:\r\n Shut down the SA5 core board \r\n",
		prvShutDownCommand,
		0 };
static const CLI_Command_Definition_t xGetVccCommand = {
		"getvcc",
		"\r\ngetvcc:\r\n Get the ADC Value from SA5 MCU Vcc\r\n",
		prvGetVccCommand,
		0 };
static const CLI_Command_Definition_t xReadCommand = {
		"read",
		"\r\nread address (length):\r\n Read register from SA5 MCU\r\n",
		prvReadCommand,
		-1 };
static const CLI_Command_Definition_t xWriteCommand = {
		"write",
		"\r\nwrite address data:\r\n Write data to SA5 MCU register\r\n",
		prvWriteCommand,
		2 };
static const CLI_Command_Definition_t xBTempCommand = {
		"btemp",
		"\r\nbtemp:\r\n Get the board temperature\r\n",
		prvBTempCommand,
		0 };
static const CLI_Command_Definition_t xCTempCommand = {
		"ctemp",
		"\r\nctemp:\r\n Get the 1684 temperature\r\n",
		prvCTempCommand,
		0 };
static const CLI_Command_Definition_t xGetRegCommand = {
		"getreg",
		"\r\ngetreg address:\r\n Get the internal register value\r\n",
		prvGetRegCommand,
		1 };

static const CLI_Command_Definition_t xGetSNCommand = {
		"getsn",
		"\r\ngetsn:\r\n Get the SN of board\r\n",
		prvGetSNCommand,
		0 };
static const CLI_Command_Definition_t xSetSNCommand = {
		"setsn",
		"\r\nsetsn data:\r\n Set the sn of board\r\n",
		prvSetSNCommand,
		1 };
static const CLI_Command_Definition_t xGetMac0Command = {
		"getmac0",
		"\r\ngetmac0:\r\n Get the MAC0 Address\r\n",
		prvGetMac0Command,
		0 };
static const CLI_Command_Definition_t xGetMac1Command = {
		"getmac1",
		"\r\ngetmac1:\r\n Get the MAC1 Address\r\n",
		prvGetMac1Command,
		0 };
static const CLI_Command_Definition_t xSetMac0Command = {
		"setmac0",
		"\r\nsetmac0 data:\r\n Input the MAC0 Address\r\n",
		prvSetMac0Command,
		1 };
static const CLI_Command_Definition_t xSetMac1Command = {
		"setmac1",
		"\r\nsetmac1 data:\r\n Input the MAC1 Address\r\n",
		prvSetMac1Command,
		1 };
static const CLI_Command_Definition_t xI2cMcuCommand = {
		"i2cmcu",
		"\r\ni2cmcu:\r\n Test the CPLD_MCU_I2C interface\r\n",
		prvI2cMcuCommand,
		0 };
static const CLI_Command_Definition_t xI2c1684Command = {
		"i2c1684",
		"\r\ni2c1684:\r\n Test the I2C of 1684\r\n",
		prvI2c1684Command,
		0 };
static const CLI_Command_Definition_t xIDbgCommand = {
		"i2cdbg",
		"\r\ni2cdebug:\r\n Test the I2C of CPLD_TPU\r\n",
		prvI2CDbgCommand,
		0 };
static const CLI_Command_Definition_t xSlotIDCommand = {
		"slotid",
		"\r\nslotid:\r\n Test the SLOT_ID\r\n",
		prvSlotIDCommand,
		0 };
static const CLI_Command_Definition_t xUart0Command = {
		"uart0",
		"\r\nuart0:\r\n Test the UART0\r\n",
		prvUart0Command,
		0 };
static const CLI_Command_Definition_t xUart1Command = {
		"uart1",
		"\r\nuart1:\r\n Test the UART1\r\n",
		prvUart1Command,
		0 };
static const CLI_Command_Definition_t xUart2Command = {
		"uart2",
		"\r\nuart2:\r\n Test the UART2\r\n",
		prvUart2Command,
		0 };
static const CLI_Command_Definition_t xPcieCommand = {
		"pcie",
		"\r\npcie:\r\n Test the PCIE interface\r\n",
		prvPcieCommand,
		0 };
static const CLI_Command_Definition_t xSdioCommand = {
		"sdio",
		"\r\nsdio:\r\n Test the SD card function\r\n",
		prvSdioCommand,
		0 };
static const CLI_Command_Definition_t xErrCommand = {
		"err",
		"\r\nerr:\r\n Test the MCU Error interrupt\r\n",
		prvErrCommand,
		0 };
static const CLI_Command_Definition_t xRegReadCommand = {
		"regread",
		"\r\nregread:\r\n read test mcu reg values\r\n",
		prvRegReadCommand,
		0 };
static const CLI_Command_Definition_t xI2CDbgAddrCommand = {
		"i2cdbgaddr",
		"\r\ni2cdbgaddr:\r\n Test debug i2c addr\r\n",
		prvI2CDbgAddrCommand,
		0 };
static const CLI_Command_Definition_t xGPIOCommand = {
		"gpio",
		"\r\ngpio:\r\n gpio test\r\n",
		prvGPIOCommand,
		0 };
static const CLI_Command_Definition_t xSUartCommand = {
		"suart",
		"\r\nsuart:\r\n suart test\r\n",
		prvSUartCommand,
		1 };



/** Source Code **/
/*-----------------------------------------------------------*/
void Shell_RegisterCommand(void) {
	FreeRTOS_CLIRegisterCommand(&xVersionCommand);
	FreeRTOS_CLIRegisterCommand(&xResetCommand);
	FreeRTOS_CLIRegisterCommand(&xPowerUpCommand);
	FreeRTOS_CLIRegisterCommand(&xShutDownCommand);
	FreeRTOS_CLIRegisterCommand(&xGetVccCommand);
	FreeRTOS_CLIRegisterCommand(&xReadCommand);
	FreeRTOS_CLIRegisterCommand(&xWriteCommand);
	FreeRTOS_CLIRegisterCommand(&xBTempCommand);
	FreeRTOS_CLIRegisterCommand(&xCTempCommand);
	FreeRTOS_CLIRegisterCommand(&xGetRegCommand);

	FreeRTOS_CLIRegisterCommand(&xGetSNCommand);
	FreeRTOS_CLIRegisterCommand(&xSetSNCommand);
	FreeRTOS_CLIRegisterCommand(&xGetMac0Command);
	FreeRTOS_CLIRegisterCommand(&xGetMac1Command);
	FreeRTOS_CLIRegisterCommand(&xSetMac0Command);
	FreeRTOS_CLIRegisterCommand(&xSetMac1Command);
	FreeRTOS_CLIRegisterCommand(&xI2cMcuCommand);
	FreeRTOS_CLIRegisterCommand(&xI2c1684Command);
	FreeRTOS_CLIRegisterCommand(&xIDbgCommand);
	FreeRTOS_CLIRegisterCommand(&xSlotIDCommand);
	FreeRTOS_CLIRegisterCommand(&xUart0Command);
	FreeRTOS_CLIRegisterCommand(&xUart1Command);
	FreeRTOS_CLIRegisterCommand(&xUart2Command);
	FreeRTOS_CLIRegisterCommand(&xPcieCommand);
	FreeRTOS_CLIRegisterCommand(&xSdioCommand);
	FreeRTOS_CLIRegisterCommand(&xErrCommand);
	FreeRTOS_CLIRegisterCommand(&xRegReadCommand);
	FreeRTOS_CLIRegisterCommand(&xI2CDbgAddrCommand);
	FreeRTOS_CLIRegisterCommand(&xGPIOCommand);
	FreeRTOS_CLIRegisterCommand(&xSUartCommand);
}

/*-----------------------------------------------------------*/
static BaseType_t prvVersionCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	sprintf(pcWriteBuffer, "Version 0x%02X, for test only\r\n", VERSION);
		return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvResetCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage, data[1];
	if (stage == 0) { // write reset pin
		HAL_GPIO_WritePin(MCU_NRST_GPIO_Port, MCU_NRST_Pin, GPIO_PIN_RESET);
		osDelay(10);
		HAL_GPIO_WritePin(MCU_NRST_GPIO_Port, MCU_NRST_Pin, GPIO_PIN_SET);
		memset(reg, 0xFF, MAX_REG_SIZE);
		sprintf(pcWriteBuffer, "[reset] NRST command issued\r\n");
		stage = 1;
		return pdTRUE; // indicate that still have more lines to output
	} else if (stage == 1) { // write power up command
		osDelay(100);
		*data = 0x01;
		if (HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_RESET_IIC, 1, data, 1, 100)
				== HAL_OK) {
			sprintf(pcWriteBuffer, "[reset] Power-up command issued\r\n");
			osDelay(500);
			stage = 2;
			return pdTRUE;
		} else {
			sprintf(pcWriteBuffer,
					"[reset] I2C Write failed\r\nQA_FAIL_RST\r\n");
			stage = 0;
			return pdFALSE;
		}
	} else if (stage == 2) { //verify power up result REG
		*data = 0x00;
		if (HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_RESET_IIC, 1, data, 1, 100)
				!= HAL_OK) {
			sprintf(pcWriteBuffer,
					"[reset] I2C Read Error\r\nQA_FAIL_RST\r\n");
			stage = 0;
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[reset] REG[0x03]=0x%02X\r\n", *data);
		stage = 3;
		return pdTRUE;
	} else { // verify power up result VCC
		int adValue = 0;
		for (int i = 10; i > 0; i--) {
			HAL_ADC_PollForConversion(&hadc, 10);
			adValue = (int)AD_TO_VOLTAGE(HAL_ADC_GetValue(&hadc));
			if (adValue > 3100) {
				sprintf(pcWriteBuffer, "[reset] VCC=%dmV\r\nQA_PASS_RST\r\n", adValue);
				stage = 0;
				return pdFALSE;
			} else {
				osDelay(100);
				continue;
			}
		}
		sprintf(pcWriteBuffer, "[reset] VCC=%dmV\r\nQA_FAIL_RST\r\n", adValue);
		stage = 0;
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/
static BaseType_t prvPowerUpCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage, data[1];
	if (stage == 0) { // write power up command
		*data = 0x01;
		if (HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_RESET_IIC, 1, data, 1, 100)
				!= HAL_OK) {
			sprintf(pcWriteBuffer,
					"[powerup] I2C Write Error\r\nQA_FAIL_PWR\r\n");
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[powerup] command issued\r\n");
		osDelay(100);
		stage = 1;
		return pdTRUE;
	} else if (stage == 1) { // verify powerup register
		*data = 0x00;
		if (HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_RESET_IIC, 1, data, 1, 100)
				!= HAL_OK) {
			sprintf(pcWriteBuffer,
					"[powerup] I2C Read Error\r\nQA_FAIL_PWR\r\n");
			stage = 0;
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[powerup] REG[0x03]=0x%02X\r\n", *data);
		stage = 2;
		return pdTRUE;
	} else { // verify Vcc voltage
		int adValue = 0;
		for (int i = 10; i > 0; i--) {
			HAL_ADC_PollForConversion(&hadc, 10);
			adValue = (int) AD_TO_VOLTAGE(HAL_ADC_GetValue(&hadc));
			if (adValue > 3100) {
				sprintf(pcWriteBuffer, "[powerup] VCC=%dmV\r\nQA_PASS_PWR\r\n",
						adValue);
				stage = 0;
				return pdFALSE;
			} else {
				osDelay(50);
				continue;
			}
		}
		sprintf(pcWriteBuffer, "[powerup] VCC=%dmV\r\nQA_FAIL_PWR\r\n", adValue);
		stage = 0;
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/
static BaseType_t prvShutDownCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	HAL_GPIO_WritePin(MCU_NRST_GPIO_Port, MCU_NRST_Pin, GPIO_PIN_RESET);
	osDelay(10);
	HAL_GPIO_WritePin(MCU_NRST_GPIO_Port, MCU_NRST_Pin, GPIO_PIN_SET);
	memset(reg, 0xFF, MAX_REG_SIZE);
	sprintf(pcWriteBuffer, "QA_PASS_SHUT\r\n");
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvGetVccCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	HAL_ADC_PollForConversion(&hadc, 10);
	sprintf(pcWriteBuffer, "[getvcc] Vcc Value=%dmV\r\n", (int)AD_TO_VOLTAGE(HAL_ADC_GetValue(&hadc)));
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvReadCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage, addr, buf[16], size;
/* continuous read
	if (stage == 0) {
		BaseType_t ParaStrLen;
		const char *pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		if (pPara == NULL) {
			sprintf(pcWriteBuffer, "[sys] Incorrect command parameter(s)\r\n");
			return pdFALSE;
		}
		addr = strtol(pPara, NULL, 16);
		if (addr < 0x00 || addr > 0x0F) {
			sprintf(pcWriteBuffer, "[read] Invalid address\r\n");
			return pdFALSE;
		}
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 2, &ParaStrLen);
		if (pPara == NULL) { // only 1 para
			size = 1;
		} else {
			size = strtol(pPara, NULL, 10);
			if (size + addr > 0x10)
				size = 16 - addr;
			else if (size < 1) {
				sprintf(pcWriteBuffer, "[read] Invalid size\r\n");
				stage = 0;
				return pdFALSE;
			}
		}
		if (HAL_I2C_Mem_Read(&hi2c1, 0x17 << 1, addr, 1, buf, size, 100)
				!= HAL_OK) {
			stage = 0;
			sprintf(pcWriteBuffer, "[read] I2C Read Error\r\n");
			return pdFALSE;
		}
		stage = 1;
		return pdTRUE;
	} else {
		sprintf(pcWriteBuffer, "[read] REG[0x%02X]=0x%02X\r\n", addr + stage - 1, buf[stage - 1]);
		if (stage == size) {
			stage = 0;
			return pdFALSE;
		}
		else {
			stage ++;
			return pdTRUE;
		}
	}
 */
///* discrete read
	if (stage == 0) { // get parameters
		BaseType_t ParaStrLen;
		const char *pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		if (pPara == NULL) {
			sprintf(pcWriteBuffer, "[sys] Incorrect command parameter(s)\r\n");
			return pdFALSE;
		}
		addr = strtol(pPara, NULL, 16);
		if (addr < 0x00 || addr > 0x0F) {
			sprintf(pcWriteBuffer, "[read] Invalid address\r\n");
			return pdFALSE;
		}
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 2, &ParaStrLen);
		if (pPara == NULL) { // only 1 para
			size = 1;
		} else {
			size = strtol(pPara, NULL, 10);
			if (size + addr > 0x10)
				size = 16 - addr;
			else if (size < 1) {
				sprintf(pcWriteBuffer, "[read] Invalid size\r\n");
				stage = 0;
				return pdFALSE;
			}
		}
		stage = 1;
		return pdTRUE;
	} else { // loop to issue command
		if (HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, addr + stage - 1, 1, buf, 1, 100)
				!= HAL_OK) {
			stage = 0;
			sprintf(pcWriteBuffer, "[read] I2C Read Error\r\n");
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[read] REG[0x%02X]=0x%02X\r\n", addr + stage - 1, *buf);
		if (stage == size) { // reach the end
			stage = 0;
			return pdFALSE;
		}
		else { // still more to read
			stage ++;
			return pdTRUE;
		}
	}

// */
}
/*-----------------------------------------------------------*/
static BaseType_t prvWriteCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage, addr, data;
	if (stage == 0) {
		BaseType_t ParaStrLen;
		const char *pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		addr = strtol(pPara, NULL, 16);
		if (addr < 0x00 || addr > 0x0F) {
			sprintf(pcWriteBuffer, "[write] Invalid address\r\n");
			return pdFALSE;
		}
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 2, &ParaStrLen);
		data = strtol(pPara, NULL, 16);
		if (data < 0x00 || data > 0xFF) {
			sprintf(pcWriteBuffer, "[write] Invalid data\r\n");
			return pdFALSE;
		}
		stage = 1;
		return pdTRUE;
	} else {
		if (HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, addr, 1, &data, 1, 100)
				!= HAL_OK) {
			stage = 0;
			sprintf(pcWriteBuffer, "[write] I2C Read Error\r\n");
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[write] REG[0x%02X]=0x%02X\r\n", addr, data);
		stage = 0;
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/
static BaseType_t prvBTempCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t data[1];
	if (HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_BTEMP_IIC, 1, data, 1, 100) != HAL_OK)
		sprintf(pcWriteBuffer, "[btemp] I2C Read Error\r\n");
	else
		sprintf(pcWriteBuffer, "[btemp] Board temp: 0x%02X\r\n", *data);
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvCTempCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t data[1];
	if (HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_CTEMP_IIC, 1, data, 1, 100) != HAL_OK)
		sprintf(pcWriteBuffer, "[ctemp] I2C Read Error\r\n");
	else
		sprintf(pcWriteBuffer, "[ctemp] 1684 Temp: 0x%02X\r\n", *data);
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvGetRegCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t addr;
	BaseType_t ParaStrLen;
	const char *pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
	addr = strtol(pPara, NULL, 16);
	if (addr < 0x00 || addr > 0x0F) {
		sprintf(pcWriteBuffer, "[getreg] Invalid address\r\n");
		return pdFALSE;
	}
		sprintf(pcWriteBuffer, "[getreg] Int REG[0x%02X]=0x%02X\r\n",addr,reg[addr]);
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvGetSNCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t data[32] = {0};
	data[0] = LOW_U16(MCU_EEPROM_SN_ADDR);
    data[1] = HIGH_U16(MCU_EEPROM_SN_ADDR);
	if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_LADDR_IIC,1,data, 2, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[getsn] write address failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	if(HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_DATA_IIC, 1, data, 17, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[getsn] read sn failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	sprintf(pcWriteBuffer, "sn[%s]\r\n", data);
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvSetSNCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage;
	static const char *pPara;
	if (stage == 0) {
		BaseType_t ParaStrLen;
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		if (ParaStrLen != 17) { // incorrect length
			sprintf(pcWriteBuffer, "[setsn] Incorrect length %d\r\nQA_FAIL_SN\r\n",
					(int)ParaStrLen);
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[setsn] Input SN %s\r\n", pPara);
		stage = 1;
		return pdTRUE;
	} else {
	    stage = 0;
	    uint8_t data[32] = {0};

        data[0] = LOW_U16(MCU_EEPROM_SN_ADDR);
        data[1] = HIGH_U16(MCU_EEPROM_SN_ADDR);
        if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_LADDR_IIC, 1, data, 2, MCU_I2C_TIMEOUT)!= HAL_OK)
        {
            sprintf(pcWriteBuffer, "[setsn] write address failed\r\nQA_FAIL_SN\r\n");
            return pdFALSE;
        }
        if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_DATA_IIC, 1, (uint8_t *)pPara, 17, MCU_I2C_TIMEOUT) != HAL_OK)
        {
            sprintf(pcWriteBuffer, "[setsn] write sn failed\r\nQA_FAIL_SN\r\n");
            return pdFALSE;
        }
        sprintf(pcWriteBuffer, "QA_PASS_SN\r\n");
        return pdFALSE;
	}
}
/*-----------------------------------------------------------*/
static BaseType_t prvGetMac0Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t data[32] = {0};

	data[0] = LOW_U16(MCU_EEPROM_MAC0_ADDR);
    data[1] = HIGH_U16(MCU_EEPROM_MAC0_ADDR);
	if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_LADDR_IIC, 1, data, 2, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[getsn] write address failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	if(HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_DATA_IIC, 1, data, 6, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[getsn] read mac0 failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	if (data[0] != 0x00)
		sprintf(pcWriteBuffer, "mac0[%02X%02X%02X%02X%02X%02X]\r\n",
				data[0], data[1], data[2], data[3], data[4], data[5]);
	else
		sprintf(pcWriteBuffer, "mac0[]\r\n");
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvSetMac0Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage;
	static const char *pPara;
	if (stage == 0) {
		BaseType_t ParaStrLen;
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		if (ParaStrLen != 12) { // incorrect length
			sprintf(pcWriteBuffer, "[setmac0] Incorrect length %d\r\nQA_FAIL_MAC0\r\n",
					(int)ParaStrLen);
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[setmac0] Input MAC %s\r\n", pPara);
		stage = 1;
		return pdTRUE;
	} else {
		stage = 0;
        uint8_t data[32] = {0};
        data[0] = LOW_U16(MCU_EEPROM_MAC0_ADDR);
        data[1] = HIGH_U16(MCU_EEPROM_MAC0_ADDR);
        if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_LADDR_IIC, 1, data, 2, MCU_I2C_TIMEOUT)!= HAL_OK)
        {
            sprintf(pcWriteBuffer, "[setmac0] write address failed\r\nQA_FAIL_MAC0\r\n");
            return pdFALSE;
        }
        for (uint8_t i = 0; i < 6; i++) { // convert string to hex
			char buf[2] = {pPara[2*i],pPara[2*i+1]};
			if (!isHexChar(buf[0]) || !isHexChar(buf[1])) { // check is hex char
				sprintf(pcWriteBuffer, "[setmac0] Invaild char %c%c\r\nQA_FAIL_MAC0\r\n",
						buf[0],buf[1]);
				stage = 0;
				return pdFALSE;
			}
			data[i] = strtol(buf, NULL, 16);
		}
    	if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_DATA_IIC, 1, data, 6, MCU_I2C_TIMEOUT)!= HAL_OK)
    	{
    	    sprintf(pcWriteBuffer, "[setmac0] write mac0 failed\r\nQA_FAIL_MAC0\r\n");
    	    return pdFALSE;
    	}
		sprintf(pcWriteBuffer, "QA_PASS_MAC0\r\n");
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/
static BaseType_t prvGetMac1Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t data[32] = {0};
	data[0] = LOW_U16(MCU_EEPROM_MAC1_ADDR);
    data[1] = HIGH_U16(MCU_EEPROM_MAC1_ADDR);
	if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_LADDR_IIC, 1, data, 2, MCU_I2C_TIMEOUT)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[getsn] write address failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
    if(HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_DATA_IIC, 1, data, 6, MCU_I2C_TIMEOUT)!= HAL_OK)
    {
        sprintf(pcWriteBuffer, "[getsn] read mac1 failed\r\nQA_FAIL_IDBG\r\n");
        return pdFALSE;
    }
	if (data[0] != 0x00)
		sprintf(pcWriteBuffer, "mac1[%02X%02X%02X%02X%02X%02X]\r\n",
				data[0], data[1], data[2], data[3], data[4], data[5]);
	else
		sprintf(pcWriteBuffer, "mac1[]\r\n");
	return pdFALSE;
}

/*-----------------------------------------------------------*/
static BaseType_t prvSetMac1Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage;
	static const char *pPara;
	if (stage == 0) {
		BaseType_t ParaStrLen;
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		if (ParaStrLen != 12) { // incorrect length
			sprintf(pcWriteBuffer, "[setmac1] Incorrect length %d\r\nQA_FAIL_MAC1\r\n",
					(int)ParaStrLen);
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[setmac1] Input MAC %s\r\n", pPara);
		stage = 1;
		return pdTRUE;
	} else {
		stage = 0;
        uint8_t data[32] = {0};
        data[0] = LOW_U16(MCU_EEPROM_MAC1_ADDR);
        data[1] = HIGH_U16(MCU_EEPROM_MAC1_ADDR);
        if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_LADDR_IIC, 1, data, 2, MCU_I2C_TIMEOUT)!= HAL_OK)
        {
            sprintf(pcWriteBuffer, "[setmac1] write address failed\r\nQA_FAIL_MAC1\r\n");
            return pdFALSE;
        }
        for (uint8_t i = 0; i < 6; i++) { // convert string to hex
			char buf[2] = {pPara[2*i],pPara[2*i+1]};
			if (!isHexChar(buf[0]) || !isHexChar(buf[1])) { // check is hex char
				sprintf(pcWriteBuffer, "[setmac1] Invaild char %c%c\r\nQA_FAIL_MAC1\r\n",
						buf[0],buf[1]);
				stage = 0;
				return pdFALSE;
			}
			data[i] = strtol(buf, NULL, 16);
		}
        if(HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_EEPROM_DATA_IIC, 1, data, 6, MCU_I2C_TIMEOUT)!= HAL_OK)
        {
            sprintf(pcWriteBuffer, "[setmac1] write mac1 failed\r\nQA_FAIL_MAC1\r\n");
            return pdFALSE;
        }
		sprintf(pcWriteBuffer, "QA_PASS_MAC1\r\n");
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/
static BaseType_t prvI2cMcuCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	uint8_t data[1] = {0};
	if (HAL_I2C_Mem_Read(&hi2c1, CORE_MCU_ADDR, MCU_VERSION_IIC, 1, data, 1, 100) != HAL_OK)
		sprintf(pcWriteBuffer, "[i2cmcu] I2C Read Error\r\nQA_FAIL_IMCU\r\n");
	else if (*data == 0x01)
		sprintf(pcWriteBuffer, "[i2cmcu] REG[0x01]=0x%02X\r\nboard type sa5\r\nQA_PASS_IMCU\r\n",	*data);
	else if (*data == 0x04)
		sprintf(pcWriteBuffer, "[i2cmcu] REG[0x01]=0x%02X\r\nboard type sm5\r\nQA_PASS_IMCU\r\n", *data);
	else
		sprintf(pcWriteBuffer, "[i2cmcu] REG[0x01]=0x%02X\r\nboard type unknow\r\nQA_FAIL_IMCU\r\n", *data);
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvI2c1684Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t scnt;
	if (tStage == STAGE_KERNEL) { // test all ready passed
		sprintf(pcWriteBuffer, "[i2c1684] Int REG[0x00]=0x%02X\r\nQA_PASS_I1684\r\n",
						reg[0x00]);
		osDelay(500);
		return pdFALSE;
	}
	if(scnt < 60)
	{
	    osDelay(1000);
	    if (tStage == STAGE_KERNEL) { // test all ready passed
			sprintf(pcWriteBuffer, "[i2c1684] Int REG[0x00]=0x%02X\r\nQA_PASS_I1684\r\n",
					reg[0x00]);
			osDelay(500);
			return pdFALSE;
		}
		else
		{
		    sprintf(pcWriteBuffer, "[i2c1684] wait 1684 enter kernel, %ds\r\n", scnt);
			return pdTRUE;
		}
	}
	sprintf(pcWriteBuffer, "[i2c1684] Timeout\r\nQA_FAIL_I1684\r\n");
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvI2CDbgCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
    uint8_t data[32] = {0};
	data[0] = 0x10;
    data[1] = 0x00;
    data[2] = 0x20;
    data[3] = 0x00;
    data[4] = 0x10;
    data[5] = 0x25;
    if(HAL_I2C_Master_Transmit(&hi2c3, I2C3_SLAVE_ADDR(5), data, 6, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[i2cdbg] i2cdbg write failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
    data[0] = 0x23;
    if(HAL_I2C_Master_Transmit(&hi2c3, I2C3_SLAVE_ADDR(5), data, 1, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[i2cdbg] i2cdbg set mode failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	data[0] = 0x12;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 0x01;
    data[4] = 0x50;
    if(HAL_I2C_Master_Transmit(&hi2c3, I2C3_SLAVE_ADDR(5), data, 5, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[i2cdbg] i2cdbg transmit failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	if(HAL_I2C_Master_Receive(&hi2c3, I2C3_SLAVE_ADDR(5), data, 4, 100)!= HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[i2cdbg] i2cdbg receive failed\r\nQA_FAIL_IDBG\r\n");
	    return pdFALSE;
	}
	if((data[2] == 0x84)&&(data[3] == 0x16))
	{
	    sprintf(pcWriteBuffer, "[i2cdbg] reg[0x50010000] = %02x %02x %02x %02x\r\nQA_PASS_IDBG\r\n", data[3],data[2],data[1],data[0]);
	}
	else
	{
	    sprintf(pcWriteBuffer, "[i2cdbg] reg[0x50010000] = %02x %02x %02x %02x\r\nQA_FAIL_IDBG\r\n", data[3],data[2],data[1],data[0]);
	}
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvSlotIDCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	if (tStage == STAGE_KERNEL) 
    {
        if (reg[0x03] != 2)
        {
            sprintf(pcWriteBuffer, "[gpio] reg3 = 0x%x\r\nQA_FAIL_SLOTID\r\n", reg[0x03]);
            return pdFALSE;
        }
		HAL_GPIO_WritePin(GPIOB, SLOT_ID0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, SLOT_ID1_Pin, GPIO_PIN_RESET);
		reg[0x05] = 0xfa;
		for(int i = 10; i > 0; i--)
		{
		    osDelay(1000);
		    if ((reg[0x03] == 1))
		    {
		        sprintf(pcWriteBuffer, "[gpio] reg3 = 0x%x\r\nQA_PASS_SLOTID\r\n", reg[0x03]);
		        return pdFALSE;
		    }
		}
        sprintf(pcWriteBuffer, "[gpio] reg3 = 0x%x\r\nQA_FAIL_SLOTID\r\n", reg[0x03]);
        return pdFALSE;
    }

    sprintf(pcWriteBuffer, "[gpio] 1684 not in kernel\r\nQA_FAIL_SLOTID\r\n");
    return pdFALSE;
}
/*----------------------------------------------------------------------------------*/
static BaseType_t prvI2CDbgAddrCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString){
    if (tStage == STAGE_KERNEL)
    {
        if (reg[0x04] != 5)
        {
            sprintf(pcWriteBuffer, "[i2cdbgaddr] reg4 = 0x%x\r\nQA_FAIL_IDBGADDR\r\n", reg[0x04]);
            return pdFALSE;
        }
		HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD0_Pin|TPU_IIC_ADD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD1_Pin, GPIO_PIN_SET);
		reg[0x05] = 0xfa;
		for(int i = 10; i > 0; i--)
		{
		    osDelay(1000);
		    if (reg[0x04] == 2)
		    {
		        sprintf(pcWriteBuffer, "[i2cdbgaddr] reg4 = 0x%x\r\nQA_PASS_IDBGADDR\r\n", reg[0x04]);
		        HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD0_Pin|TPU_IIC_ADD2_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD1_Pin, GPIO_PIN_RESET);
		        return pdFALSE;
		    }
		}
        sprintf(pcWriteBuffer, "[i2cdbgaddr] reg4 = 0x%x\r\nQA_FAIL_IDBGADDR\r\n", reg[0x04]);
        HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD0_Pin|TPU_IIC_ADD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD1_Pin, GPIO_PIN_RESET);
        return pdFALSE;
    }
    sprintf(pcWriteBuffer, "[i2cdbgaddr] 1684 not in kernel\r\nQA_FAIL_IDBGADDR\r\n");
    return pdFALSE;
}
/*----------------------------------------------------------------------------------*/
static BaseType_t prvGPIOCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString){
	if (tStage == STAGE_KERNEL)
    {
        if ((reg[0x03] != 2)||(reg[0x04] != 5))
        {
            sprintf(pcWriteBuffer, "[gpio] reg3 = 0x%x, reg4 = 0x%x\r\nQA_FAIL_GPIO\r\n", reg[0x03], reg[0x04]);
            return pdFALSE;
        }
		HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD0_Pin|TPU_IIC_ADD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SLOT_ID0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, SLOT_ID1_Pin, GPIO_PIN_RESET);
		reg[0x05] = 0xfa;
		for(int i = 10; i > 0; i--)
		{
		    osDelay(1000);
		    if ((reg[0x03] == 1)&&(reg[0x04] == 2))
		    {
		        sprintf(pcWriteBuffer, "[gpio] reg3 = 0x%x, reg4 = 0x%x\r\nQA_PASS_GPIO\r\n", reg[0x03], reg[0x04]);
		        return pdFALSE;
		    }
		}
        sprintf(pcWriteBuffer, "[gpio] reg3 = 0x%x, reg4 = 0x%x\r\nQA_FAIL_GPIO\r\n", reg[0x03], reg[0x04]);
        return pdFALSE;
    }
    HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD0_Pin|TPU_IIC_ADD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, TPU_IIC_ADD1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SLOT_ID0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, SLOT_ID1_Pin, GPIO_PIN_RESET);
    sprintf(pcWriteBuffer, "[gpio] 1684 not in kernel\r\nQA_FAIL_GPIO\r\n");
    return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvPcieCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	if (tStage == STAGE_KERNEL)
    {
		for(int i = 10; i > 0; i--)
		{
		    osDelay(50);
		    if (reg[0x01] == 1)
		    {
		        sprintf(pcWriteBuffer, "[pcie] reg4 = 0x%x\r\nQA_PASS_PCIE\r\n", reg[0x01]);
		        return pdFALSE;
		    }
		}
        sprintf(pcWriteBuffer, "[pcie] timeout\r\nQA_FAIL_PCIE\r\n");
        return pdFALSE;
    }
    sprintf(pcWriteBuffer, "[pcie] 1684 not in kernel\r\nQA_FAIL_PCIE\r\n");
    return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvSdioCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	if (tStage == STAGE_KERNEL)
    {
		for(int i = 10; i > 0; i--)
		{
		    osDelay(50);
		    if (reg[0x02] == 1)
		    {
		        sprintf(pcWriteBuffer, "[sdio] reg4 = 0x%x\r\nQA_PASS_SDIO\r\n", reg[0x02]);
		        return pdFALSE;
		    }
		}
        sprintf(pcWriteBuffer, "[sdio] timeout\r\nQA_FAIL_SDIO\r\n");
        return pdFALSE;
    }
    sprintf(pcWriteBuffer, "[sdio] 1684 not in kernel\r\nQA_FAIL_SDIO\r\n");
    return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvSUartCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage;
	static const char *pPara;
	static char sbuf[64] = {0};
	char rbuf[64] = {0};
	if (stage == 0) {
		BaseType_t ParaStrLen;
		pPara = FreeRTOS_CLIGetParameter(pcCommandString, 1, &ParaStrLen);
		if (ParaStrLen == 0) { // incorrect length
			sprintf(pcWriteBuffer, "[suart] null cmd\r\n");
			return pdFALSE;
		}
		sprintf(sbuf, "%s\n", pPara);
		sprintf(pcWriteBuffer, "[suart]T:%s\r\n", sbuf);
		stage = 1;
		return pdTRUE;
	}
	else
	{
	    stage = 0;
		HAL_UART_Receive_IT(&hlpuart1, (uint8_t *)rbuf, 64);
		osDelay(100);
		if (HAL_UART_Transmit(&hlpuart1, (uint8_t *)sbuf, strlen(sbuf), 100) != HAL_OK) {
			sprintf(pcWriteBuffer, "[suart] HAL Error\r\n");
			HAL_UART_Abort(&hlpuart1);
			memset(rbuf, 0x00, 64);
			sprintf(pcWriteBuffer, "[suart] cmd send failed\r\n");
			return pdFALSE;
		}
		osDelay(100);
        sprintf(pcWriteBuffer, "[suart]R:%s\r\n", rbuf);
		HAL_UART_Abort(&hlpuart1);
		memset(rbuf, 0x00, 64);
		return pdFALSE;
    }
    return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvUart0Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	const char *tbuf = "/usr/sbin/testboard 0x34 4\n";
	if (HAL_UART_Transmit(&hlpuart1, (uint8_t *)tbuf, strlen(tbuf), 100) != HAL_OK)
	{
	    sprintf(pcWriteBuffer, "[uart0] uart0 transmit failed\r\nQA_FAIL_UART0\r\n");
		HAL_UART_Abort(&hlpuart1);
		return pdFALSE;
	}
	for(int i = 0; i < 10; i++)
	{
	    osDelay(1000);
	    if(tStage == STAGE_KERNEL)
	    {
	        HAL_UART_Abort(&hlpuart1);
	        sprintf(pcWriteBuffer, "[uart0] cmd response received\r\nQA_PASS_UART0\r\n");
		    return pdFALSE;
	    }
	}
	HAL_UART_Abort(&hlpuart1);
    sprintf(pcWriteBuffer, "[uart0] cmd response timeout\r\nQA_FAIL_UART0\r\n");
    return pdFALSE;
}

/*-----------------------------------------------------------*/
static BaseType_t prvUart1Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	const char *tbuf = "UART1";
	char rbuf[6] = {0};
	for (uint8_t counter = 0; counter < 5; counter++) {
		HAL_UART_Receive_IT(&huart2, (uint8_t *)rbuf, 6);
		osDelay(100);
		if (HAL_UART_Transmit(&huart2, (uint8_t *)tbuf, 6, 100) != HAL_OK) {
			sprintf(pcWriteBuffer, "[uart1] HAL Error\r\n");
			HAL_UART_Abort(&huart2);
			memset(rbuf, 0x00, 6);
			continue;
		}
		osDelay(10);
		if (memcmp(tbuf,rbuf,6) == 0) {
			sprintf(pcWriteBuffer, "QA_PASS_UART1\r\n");
			return pdFALSE;
		}
		HAL_UART_Abort(&huart2);
		memset(rbuf, 0x00, 6);
	}
	sprintf(pcWriteBuffer, "QA_FAIL_UART1\r\n");
	return pdFALSE;
}
/*-----------------------------------------------------------*/
static BaseType_t prvUart2Command(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	const char *tbuf = "UART2";
	char rbuf[6] = {0};
	for (uint8_t counter = 0; counter < 5; counter++) {
		HAL_UART_Receive_IT(&huart4, (uint8_t *)rbuf, 6);
		osDelay(100);
		if (HAL_UART_Transmit(&huart4, (uint8_t *)tbuf, 6, 100) != HAL_OK) {
			sprintf(pcWriteBuffer, "[uart2] HAL Error\r\n");
			HAL_UART_Abort(&huart4);
			memset(rbuf, 0x00, 6);
			continue;
		}
		osDelay(10);
		if (memcmp(tbuf,rbuf,6) == 0) {
			sprintf(pcWriteBuffer, "QA_PASS_UART2\r\n");
			return pdFALSE;
		}
		HAL_UART_Abort(&huart4);
		memset(rbuf, 0x00, 6);
	}
	sprintf(pcWriteBuffer, "QA_FAIL_UART2\r\n");
	return pdFALSE;
}

/*-----------------------------------------------------------*/
static BaseType_t prvErrCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString) {
	static uint8_t stage, data[1];
	HAL_NVIC_DisableIRQ(MCU_CPLD_ERR_EXTI_IRQn);
	if (stage == 0) { // write err interrupt register
		*data = SET<<1;
		if (HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_INTR_IIC, 1, data, 1, 100)
				!= HAL_OK) {
			sprintf(pcWriteBuffer, "[err] I2C Write Error\r\nQA_FAIL_ERR\r\n");
			return pdFALSE;
		}
		sprintf(pcWriteBuffer, "[err] register set\r\n");
		stage = 1;
		return pdTRUE;
	} else if (stage == 1) { // try to read pin MCU_ERR_INT
		for (int i = 10; i > 0; i--) {
			if (HAL_GPIO_ReadPin(MCU_CPLD_ERR_GPIO_Port, MCU_CPLD_ERR_Pin) == GPIO_PIN_SET) {
				sprintf(pcWriteBuffer, "[err] MCU interrupt received\r\n");
				stage = 2;
				return pdTRUE;
			} else {
				osDelay(50);
				continue;
			}
		}
		sprintf(pcWriteBuffer, "[err] MCU interrupt NOT received\r\nQA_FAIL_ERR\r\n");
		stage = 0;
		return pdFALSE;
	} else { // clear error register
		osDelay(50);
		*data = 0x05;
		if (HAL_I2C_Mem_Write(&hi2c1, CORE_MCU_ADDR, MCU_RESET_IIC, 1, data, 1, 100)
				!= HAL_OK)
			sprintf(pcWriteBuffer, "[err] I2C Write Error\r\nQA_FAIL_ERR\r\n");
		else
			sprintf(pcWriteBuffer, "[err] MCU_ERR_INT reset\r\nQA_PASS_ERR\r\n");
		stage = 0;
		return pdFALSE;
	}

}
/*----------------------------------------------------------------------------------*/
static BaseType_t prvRegReadCommand(char *pcWriteBuffer, size_t xWriteBufferLen,
		const char *pcCommandString){
		sprintf(pcWriteBuffer, "[regread] Reg[0-4]=0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\r\n",reg[0],reg[1],reg[2],reg[3],reg[4],reg[5]);
		return pdFALSE;
}


static uint8_t isHexChar(char data) {
	if (data < '0') return pdFALSE;
	if (data > '9' && data < 'A') return pdFALSE;
	if (data > 'F' && data < 'a') return pdFALSE;
	if (data > 'f') return pdFALSE;
	return pdTRUE;
}
