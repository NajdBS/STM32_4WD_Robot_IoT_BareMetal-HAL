#ifndef ESP_UTILS_H
#define ESP_UTILS_H

#include "stm32f4xx.h"  
#include <stdio.h>       
#include "string.h"
#include "USART.h"
#include "UTIL.h"
#include "ADC.h"
#include "I2C.h"

//for esp server
#define PrivateNetwork "MonServeur" 
#define ssid "12345678"  
//for cloud
#define Network "Ooredoo-FEED82"
#define Password "dgn82q92@627"


#define Key "1N8DCHNZQH6S5I4B"
//#define Key "S2MTCHWWFZHJNI54"

//#define serverIP "184.106.153.149" //CLOUD SERVER
//#define serverPort "80"

#define CMD_BUFFER_SIZE 500
#define DATA_BUFFER_SIZE 500

extern uint16_t ADC_Value[BUFFER_SIZE];
extern float temperature;
extern char cmdBuffer[CMD_BUFFER_SIZE]; 
extern char DataBuffer[DATA_BUFFER_SIZE];



void ESP_Init_Station_Client(void);

void ESP_SendCommand(char *cmd, char *expectedResponse, uint32_t timeout);

void waitForResponse(char* expectedResponse);

void ESP_OpenTCPConnection(const char *serverIP, uint16_t serverPort);

void ESP_CloseTCPConnection(void);

void ESP_SendDataToCloud(const char *serverIP, uint16_t serverPort);

void ESP_SendDataToServer(const char *serverIP, uint16_t serverPort);


/*
/+
void Transmit_string_to_HC06();
*/
#endif // ESP_UTILS_H
