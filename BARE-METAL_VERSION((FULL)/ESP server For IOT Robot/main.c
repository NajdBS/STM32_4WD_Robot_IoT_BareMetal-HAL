#include "stm32f4xx.h"
#include "ESP.h"
#include "WEBSERVER.h"

// Buffers
char cmdBuffer[CMD_BUFFER_SIZE];
char RX2_Buffer[TX_RX_BUFFER_SIZE];//esp reception here
char CpyBuffer[CPY_BUFFER_SIZE];//buffer for test esp reception 

//Var
int j = 0;
uint8_t ESP_Configured = 0; 

bool browrser_request = false;
int linkID;

float Esp_temperature;
uint16_t Esp_ADC_Value[4];


int main(void)
{
    USART2_Init();//ESP
    USART3_Init();//esp terminal
		IWDG_Init();
		ESP_Init_Station_Server();
    while (1) 
    {
		if (browrser_request == true )
			{
			processRequest(CpyBuffer);
			browrser_request = false;	
			}
		// Refresh watchdog periodically
    IWDG_Refresh();
    }
}




