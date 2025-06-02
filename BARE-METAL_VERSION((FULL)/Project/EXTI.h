#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

#include "stm32f4xx.h"  // Include the STM32F4 specific library
#include "USART.h"

// Declaration of global variables used in EXTI0_IRQHandler
extern int systemState;

// Function prototypes
void config_EXTI(void);
void EXTI0_IRQHandler(void);

#endif // EXTI_CONFIG_H
