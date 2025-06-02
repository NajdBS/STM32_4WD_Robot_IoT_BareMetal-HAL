#include "ESP.h"

// Function to check if the ESP response matches the expected response
void waitForResponse(char* expectedResponse) {
    while (1) {
        if (strstr(CpyBuffer, expectedResponse) != NULL) {
            break;  // Response matches, exit the loop
        }
        delay_ms(100);
    }
    //IWDG_Refresh(); 
}

// Function to send a command to the ESP and wait for the expected response
void ESP_SendCommand(char *cmd, char *expectedResponse, uint32_t timeout) {
    SendTxt_usart2(cmd);   // Send the command to the ESP
    waitForResponse(expectedResponse);  // Wait for the expected response
    delay_ms(timeout);  // Wait for the specified timeout
		IWDG_Refresh();  // Refresh watchdog timer to prevent reset
}

// Initialize the ESP module
void ESP_Init_Station_Client(void) {
    // Send commands and wait for expected responses
    ESP_SendCommand("AT\r\n", "\r\nOK\r\n", 1000);  // Check communication with ESP
    ESP_SendCommand("AT+RST\r\n", "\r\nOK\r\n", 5000);  // Reset ESP
    ESP_SendCommand("AT+CWMODE=1\r\n", "\r\nOK\r\n", 1000);  // Set ESP to Station (Client) mode
    
    /*sprintf(cmdBuffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", PrivateNetwork, ssid);
    ESP_SendCommand(cmdBuffer, "\r\nOK\r\n", 10000);  // Connect to the Wi-Fi network*/
    
    ESP_SendCommand("AT+CIFSR\r\n", "\r\nOK\r\n", 2000);  // Get the IP address
		SendTxt_usart3("\t#### ESP Is Configured ####\n");//
}

void ESP_OpenTCPConnection(const char *serverIP, uint16_t serverPort) {
    // Open TCP connection with the server
    sprintf(cmdBuffer, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", serverIP, serverPort);
    ESP_SendCommand(cmdBuffer, "\r\nOK\r\n", 3000);  // Wait for the "CONNECT" response
    ClearBuffer(cmdBuffer, sizeof(cmdBuffer));
}
void ESP_CloseTCPConnection(void) {
    // Close the TCP connection
    ESP_SendCommand("AT+CIPCLOSE\r\n", "\r\nOK\r\n", 1000);  // Wait for the "CLOSE" response
		ClearBuffer(cmdBuffer, sizeof(cmdBuffer));
}

// Function to send data to the cloud (ThingSpeak)
void ESP_SendDataToCloud(const char *serverIP, uint16_t serverPort) {
    
		sprintf(cmdBuffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", Network, Password);
    ESP_SendCommand(cmdBuffer, "\r\nOK\r\n", 10000);  // Connect to the Wi-Fi network
		ClearBuffer(cmdBuffer, sizeof(cmdBuffer));
	
		//temperature = DS1621_Read_Temp();     
    sprintf(DataBuffer, "GET /update?key=%s&field1=%d&field2=%d&field3=%d&field4=%d&field5=%.2f\r\n", Key, ADC_Value[0], ADC_Value[1], ADC_Value[2], ADC_Value[3],temperature);
    int dataLength = strlen(DataBuffer);  // For cloud transmission

    ESP_OpenTCPConnection(serverIP, serverPort);

    sprintf(cmdBuffer, "AT+CIPSEND=%d\r\n", dataLength);  // Prepare the command with data length
    ESP_SendCommand(cmdBuffer, ">", 1000);  // Send the command to indicate data length
    SendTxt_usart2(DataBuffer);  // Send the data string
    //waitForResponse("CLOSED\r\n");  // Wait for "SEND OK" response
		//ESP_SendCommand(DataBuffer, "CLOSED\r\n", 2000);  // Connect to the Wi-Fi network
    
		// ESP_CloseTCPConnection();
}

// Function to send data to the server via TCP
void ESP_SendDataToServer(const char *serverIP, uint16_t serverPort) {
	  
		sprintf(cmdBuffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", PrivateNetwork, ssid);
    ESP_SendCommand(cmdBuffer, "\r\nOK\r\n", 10000);  // Connect to the Wi-Fi network
		ClearBuffer(cmdBuffer, sizeof(cmdBuffer));
   
		//temperature = DS1621_Read_Temp();  
    sprintf(DataBuffer, "CH1=%d CH2=%d CH3=%d CH4=%d Temp_DS1621=%.2f C\n", ADC_Value[0], ADC_Value[1], ADC_Value[2], ADC_Value[3], temperature);
    int dataLength = strlen(DataBuffer);  

    // Step 1: Open TCP connection
    ESP_OpenTCPConnection(serverIP, serverPort);

    // Step 2: Send the data
    sprintf(cmdBuffer, "AT+CIPSEND=%d\r\n", dataLength);  // Prepare command with data length
    ESP_SendCommand(cmdBuffer, ">", 1000);  // Wait for ">" prompt to send data
    SendTxt_usart2(DataBuffer);  // Send the actual data string
    waitForResponse("\r\nSEND OK\r\n");  // Wait for confirmation "SEND OK"

    // Step 3: Close the TCP connection
    //ESP_CloseTCPConnection();
		SendTxt_usart2("AT+CIPCLOSE\r\n");
		delay_ms(1000);
}



/*
// Function to transmit data via USART3 (used for communication with HC-06 Bluetooth module)
void Transmit_string_to_HC06()
{
		char TX_Buffer [60];
		sprintf(TX_Buffer, "CH1=%d CH2=%d CH3=%d CH4=%d Temp_DS1621=%.2f C\n",ADC_Value[0], ADC_Value[1], ADC_Value[2], ADC_Value[3],temperature);
		SendTxt_usart3(TX_Buffer);
		ClearBuffer(TX_Buffer, sizeof(TX_Buffer));
}
*/
