#ifndef USART_H
#define USART_H

#include "stm32f4xx.h"   // Header for STM32F4
#include "UTIL.h"
#include "string.h"  
#include <stdio.h>
#include "PWM.h"
#include "EXTI.h"

#define ESP_TX_RX_BUFFER_SIZE 500  // Buffer size
#define CPY_BUFFER_SIZE 500 
#define BLE_BUFFER_SIZE 60 

extern char CpyBuffer[CPY_BUFFER_SIZE];
extern char ESP_REC_Buffer[ESP_TX_RX_BUFFER_SIZE];  
extern char BLE_REC_Buffer[BLE_BUFFER_SIZE]; // BLE RX
extern char BLE_SEND_Buffer[BLE_BUFFER_SIZE]; // BLE TX
extern int j;
extern int i;

// Initialization function for USART2
void USART2_Init(void);

// Function to send a character via USART2
void SendChar_usart2(char C);

// Function to send a string via USART2
void SendTxt_usart2(char *ADR);

// Initialization function for USART3
void USART3_Init(void);

// Function to send a character via USART3
void SendChar_usart3(char C);

// Function to send a string via USART3
void SendTxt_usart3(char *ADR);

// Initialization function for USART6
void USART6_Init(void);

// Function to send a character via USART6
void SendChar_usart6(char C);

// Function to send a string via USART6
void SendTxt_usart6(char *ADR);

// USART2 interrupt handler declaration
void USART2_IRQHandler(void);

// USART3 interrupt handler declaration
void USART3_IRQHandler(void);

#endif // USART_H
