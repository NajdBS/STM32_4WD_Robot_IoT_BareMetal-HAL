#include "stm32f4xx.h"
#include "ESP.h"
#include "PWM.h"
#include "EXTI.h"


// Buffers
char cmdBuffer[CMD_BUFFER_SIZE];
char ESP_REC_Buffer[ESP_TX_RX_BUFFER_SIZE];//ESP
char DataBuffer[DATA_BUFFER_SIZE];
char CpyBuffer[DATA_BUFFER_SIZE];//TEST ESP
char BLE_REC_Buffer[BLE_BUFFER_SIZE];//BLE RX
char BLE_SEND_Buffer[BLE_BUFFER_SIZE];//BLE Tx

// Variables for system management
int current_speed_forward = START_SPEED;
int current_speed_backward = START_SPEED;
bool flag = false;
float temperature;
uint16_t ADC_Value[BUFFER_SIZE];

int systemState = 0;
int j = 0;
int i = 0;





int main(void)
{
		//config_clock();//8MHZ
		USART2_Init();
    USART3_Init();
		USART6_Init();
    IWDG_Init();
    ESP_Init_Station_Client();
		config_EXTI();
		config_GPIO_ADC_Channnel();
		config_ADC1();  
		config_TIMER2();
		config_DMA2();
	  config_TIMER3();
    I2C1_Init();
		DS1621_Init();
		// Interruptions
    NVIC_SetPriority(USART3_IRQn, 0);  
		NVIC_SetPriority(USART2_IRQn, 1);  
		NVIC_SetPriority(DMA2_Stream0_IRQn, 2); 
		NVIC_SetPriority(EXTI0_IRQn, 3);           
		while (1) 
    {
    if (flag == true){
		temperature = DS1621_Read_Temp();
		ESP_SendDataToServer("192.168.4.1", 80);  // Send sensor data to the specified server IP and port
		ESP_SendDataToCloud("184.106.153.149", 80); //Cloud
		flag = false;
		}
		// Refresh watchdog periodically
    IWDG_Refresh();
    }
}



