#ifndef ADC_H
#define ADC_H

#include "stm32f4xx.h"   
#include <stdbool.h> 

/*#include "USART.h"
#include "I2C.h"
extern float temperature;*/


// Define the size of ADC channels buffer
#define BUFFER_SIZE 4
#define dataUploadInterval 9999 //ARR (ms)

// Declare global variables
extern uint16_t ADC_Value[BUFFER_SIZE]; // Array to store ADC conversion results
extern bool flag;

// Function declarations
void config_GPIO_ADC_Channnel(void);  // Function to configure GPIO for ADC channels
void config_TIMER2(void);             // Function to configure Timer 6 for ADC trigger
void config_TIMER7(void);
void config_ADC1(void);               // Function to configure ADC1 with DMA
void config_DMA2(void);               // Function to configure DMA2 for ADC1

// Interrupt handler for DMA2 Stream0
void DMA2_Stream0_IRQHandler(void);    // DMA2 Stream0 interrupt handler for ADC
void TIM7_IRQHandler(void);
#endif // ADC_H
