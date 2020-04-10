#ifndef __PIN_H__
#define __PIN_H__

#define LED_PORT	GPIOC
#define LED_PIN		GPIO13

#define PCIE_RESET_PORT	GPIOB
#define PCIE_RESET_PIN	GPIO15
#define PCIE_RESET_NVIC	NVIC_EXTI4_15_IRQ
#define PCIE_RESET_EXTI	EXTI15

#define SYS_RESET_PORT	GPIOB
#define SYS_RESET_PIN	GPIO5

#define EN_VQPS_PORT	GPIOA
#define EN_VQPS_PIN	GPIO15

#endif
