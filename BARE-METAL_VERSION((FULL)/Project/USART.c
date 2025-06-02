#include "USART.h"

void USART6_Init(void)
{
    // Enable GPIOC clock (GPIOC is used for USART6 TX/RX on STM32F407VG)
    RCC->AHB1ENR |= (1 << 2);  // Enable GPIOC clock (bit 2 in AHB1ENR)

    // Set PC6 (TX) and PC7 (RX) to alternate function (AF)
    GPIOC->MODER &= ~( (3 << (2 * 6)) | (3 << (2 * 7)) );   // Clear mode bits for PC6 and PC7
    GPIOC->MODER |= ( (2 << (2 * 6)) | (2 << (2 * 7)) );    // Set PC6 and PC7 to alternate function (AF)

    // Set AF8 (USART6) for PC6 and PC7
    GPIOC->AFR[0] &= ~( (0xF << (4 * 6)) | (0xF << (4 * 7)) );  // Clear AF bits
    GPIOC->AFR[0] |= ( (8 << (4 * 6)) | (8 << (4 * 7)) );       // Set AF8 (USART6) for PC6 and PC7

    // Configure USART6
    RCC->APB2ENR |= (1 << 5);  // Enable USART6 clock (bit 5 in APB2ENR)
    
    USART6->BRR = 0x008B;         // Baud rate 115200 for 16 MHz clock 
    
    USART6->CR1 |= (1 << 3);    // Enable transmitter (TE)
    USART6->CR1 |= (1 << 13);   // Enable USART6 (UE)
    
    NVIC_EnableIRQ(USART6_IRQn);  // Enable USART6 global interrupt
}

// Function to send a character via USART6
void SendChar_usart6(char C)
{
    while ((USART6->SR & 0x80) == 0) {} // Wait until the Transmit Data Register (TDR) is empty
    USART6->DR = C;                     // Load the character into the Data Register for transmission
}

// Function to send a string via USART6
void SendTxt_usart6(char *ADR)
{
    while (*ADR)
    {
        SendChar_usart6(*ADR);           // Send each character
        ADR++;                           // Move to the next character
    }
}


void USART2_Init(void)
{
    // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0);  // Enable GPIOA clock (bit 0 in AHB1ENR)

    // Set PA2 (TX) and PA3 (RX) to alternate function (AF)
    GPIOA->MODER &= ~( (3 << (2 * 2)) | (3 << (2 * 3)) );   // Clear mode bits for PA2 and PA3
    GPIOA->MODER |= ( (2 << (2 * 2)) | (2 << (2 * 3)) );    // Set PA2 and PA3 to alternate function (AF)

    // Set AF7 (USART2) for PA2 and PA3
    GPIOA->AFR[0] &= ~( (0xF << (4 * 2)) | (0xF << (4 * 3)) );  // Clear AF bits
    GPIOA->AFR[0] |= ( (7 << (4 * 2)) | (7 << (4 * 3)) );       // Set AF7 (USART2) for PA2 and PA3

    // Configure USART2
    RCC->APB1ENR |= (1 << 17);  // Enable USART2 clock (bit 17 in APB1ENR)
    
    USART2->BRR = 0x008B;        // Baud rate 115200 for 16 MHz clock 
    
    USART2->CR1 |= (1 << 3);    // Enable transmitter (TE)
    USART2->CR1 |= (1 << 2);    // Enable receiver (RE)
    USART2->CR1 |= (1 << 5);    // Enable RXNE interrupt (RXNEIE)
    USART2->CR1 |= (1 << 4);    // Enable IDLE interrupt (IDLEIE)
    USART2->CR1 |= (1 << 13);   // Enable USART2 (UE)
    
    NVIC_EnableIRQ(USART2_IRQn);  // Enable USART2 global interrupt
}

// Function to send a character via USART2
void SendChar_usart2(char C)
{
	while ((USART2->SR & 0x80) == 0) {} // Wait until the Transmit Data Register (TDR) is empty
	USART2->DR = C;                     // Load the character into the Data Register for transmission
}

// Function to send a string via USART2
void SendTxt_usart2(char *ADR)
{
	while (*ADR)
	{
		SendChar_usart2(*ADR);           // Send each character
		ADR++;                           // Move to the next character
	}
}

void USART2_IRQHandler()
{
    // Check if RXNE (Receive Not Empty) flag is set
    if ((USART2->SR & 0x20) != 0)  
    {
        if (j < ESP_TX_RX_BUFFER_SIZE - 1) 
        {
				j++;  
				ESP_REC_Buffer[j-1] = USART2->DR;  
				}
    }
    
    // Check if IDLE flag is set (indicates end of transmission)
    if ((USART2->SR & 0x10) != 0)  
    {
				SendTxt_usart6(ESP_REC_Buffer);
				SendTxt_usart3(ESP_REC_Buffer);
				memcpy(CpyBuffer, ESP_REC_Buffer, ESP_TX_RX_BUFFER_SIZE);
				ClearBuffer(ESP_REC_Buffer, sizeof(ESP_REC_Buffer));
        j = 0;                       
        USART2->SR;                  
        USART2->DR;                 
    }
}

void USART3_Init(void)
{
    // Enable GPIOB clock
    RCC->AHB1ENR |= (1 << 1);  // Enable GPIOB clock(bit 1 AHB1ENR)

    // Set PB10 (TX) and PB11 (RX) to alternate function (AF)
    GPIOB->MODER &= ~( (3 << (2 * 10)) | (3 << (2 * 11)) );   // Clear mode bits for PB10 and PB11
    GPIOB->MODER |= ( (2 << (2 * 10)) | (2 << (2 * 11)) );    // Set PB10 and PB11 to alternate function (AF)

    // Set AF7 (USART3) for PB10 and PB11
    GPIOB->AFR[1] &= ~( (0xF << (4 * (10 - 8))) | (0xF << (4 * (11 - 8))) );  // Clear AF bits
    GPIOB->AFR[1] |= ( (7 << (4 * (10 - 8))) | (7 << (4 * (11 - 8))) );       // Set AF7 (USART3) for PB10 and PB11
    //AF7 is the alternate function assigned to USART3_TX and USART3_RX on PB10 (transmit) and PB11 (receive), respectively.
		
	  //Config USART3		
		RCC->APB1ENR |= 1<<18; // Enable USART3 clock
		//USART3->BRR=834; 	// for 8 MHZ and 9600 Baudrate 
		USART3->BRR=1667; 	// for 16 MHZ and 9600 Baudrate 
		USART3->CR1 |= 1<<3; 	// Enable TE
	  USART3->CR1 |= 1<<2; 	// Enable RE
		USART3->CR1 |= 1<<5; 	// Enable RXNEIE
		USART3->CR1 |= 1<<4; 	// Enable IDLEIE
	  USART3->CR1 |= 1<<13; // Enable USART3
	  NVIC_EnableIRQ(USART3_IRQn);    // Enable USART3 global interrupt
		
}
// Function to send a character via USART3
void SendChar_usart3(char C)
{
	while((USART3->SR & 0x80) == 0){}// Check if the Transmit Data Register (TDR) is empty
  USART3->DR=C;  // Load the character into the Data Register (DR) for transmission
   
}


// Function to send a string via USART3
void SendTxt_usart3(char *ADR)
{
		while(*ADR)
		{
		SendChar_usart3(*ADR);
		ADR++;
		}
}
void USART3_IRQHandler()
{
	if((USART3->SR & 0x20) != 0) 
	{
		if (j < BLE_BUFFER_SIZE - 1) 
    {
		i++;
		BLE_REC_Buffer[i-1]=USART3->DR;
		}
	}
	if((USART3->SR & 0x10) != 0) 
	{
			SendTxt_usart3(BLE_REC_Buffer);
			// Command Forward+ to increase speed forward
			if (strstr(BLE_REC_Buffer, "Forward+"))
			{
					if (current_speed_forward + STEP_SPEED <= MAX_SPEED) {
							current_speed_forward += STEP_SPEED;  // Increase forward speed up to MAX_SPEED
					} else {
							current_speed_forward = MAX_SPEED;  // Don't exceed MAX_SPEED
					}
					TIM3->CCR1 = current_speed_forward;  
					TIM3->CCR2 = 0;  
					TIM3->CCR3 = 0;                     
					TIM3->CCR4 = current_speed_forward;    					
					sprintf(BLE_SEND_Buffer,"Current_speed_forward=%d\n",current_speed_forward);
					SendTxt_usart3(BLE_SEND_Buffer);
			}

			// Command Backward+ to increase speed backward
			if (strstr(BLE_REC_Buffer, "Backward+"))
			{
					if (current_speed_backward + STEP_SPEED <= MAX_SPEED) {
							current_speed_backward += STEP_SPEED;  // Increase backward speed up to MAX_SPEED
					} else {
							current_speed_backward = MAX_SPEED;  // Don't exceed MAX_SPEED
					}
					TIM3->CCR1 = 0;                       
					TIM3->CCR2 = current_speed_backward;                      
					TIM3->CCR3 = current_speed_backward;  
					TIM3->CCR4 = 0;  
					sprintf(BLE_SEND_Buffer,"Current_speed_backward=%d\n",current_speed_backward);
					SendTxt_usart3(BLE_SEND_Buffer);
					
			}

			// Command Forward- to decrease speed forward
			if (strstr(BLE_REC_Buffer, "Forward-"))
			{
					if (current_speed_forward - STEP_SPEED >= MIN_SPEED) {
							current_speed_forward -= STEP_SPEED;  // Decrease forward speed down to MIN_SPEED
					} else {
							current_speed_forward = MIN_SPEED;  // Don't go below MIN_SPEED
					}
					TIM3->CCR1 = current_speed_forward;  
					TIM3->CCR2 = 0;  
					TIM3->CCR3 = 0;                      
					TIM3->CCR4 = current_speed_forward;                      
					sprintf(BLE_SEND_Buffer,"Current_speed_forward=%d\n",current_speed_forward);
					SendTxt_usart3(BLE_SEND_Buffer);
			}

			// Command Backward- to decrease speed backward
			if (strstr(BLE_REC_Buffer, "Backward-"))
			{
					if (current_speed_backward - STEP_SPEED >= MIN_SPEED) {
							current_speed_backward -= STEP_SPEED;  // Decrease backward speed down to MIN_SPEED
					} else {
							current_speed_backward = MIN_SPEED;  // Don't go below MIN_SPEED
					}
					TIM3->CCR1 = 0;                       
					TIM3->CCR2 = current_speed_backward;  
					TIM3->CCR3 = current_speed_backward;  
					TIM3->CCR4 = 0;  
					sprintf(BLE_SEND_Buffer,"Current_speed_backward=%d\n",current_speed_backward);
					SendTxt_usart3(BLE_SEND_Buffer);
			}

			// Command Left to turn left
			if (strstr(BLE_REC_Buffer, "Left"))
			{
					TIM3->CCR1 = 0;  
					TIM3->CCR2 = 0;                    
					TIM3->CCR3 = 0;  
					TIM3->CCR4 = TURNING_SPEED;                      
					sprintf(BLE_SEND_Buffer,"Turning_speed=%d\n",TURNING_SPEED);
					SendTxt_usart3(BLE_SEND_Buffer);
			}

			// Command Right to turn right
			if (strstr(BLE_REC_Buffer, "Right"))
			{
					TIM3->CCR1 = TURNING_SPEED;                       
					TIM3->CCR2 = 0;   
					TIM3->CCR3 = 0;                      
					TIM3->CCR4 = 0;  
					sprintf(BLE_SEND_Buffer,"Turning_speed=%d\n",TURNING_SPEED);
					SendTxt_usart3(BLE_SEND_Buffer);
			}

			// Command Stop to stop all motors
			if (strstr(BLE_REC_Buffer, "Stop"))
			{
					TIM3->CCR1 = 0;  
					TIM3->CCR2 = 0;   
					TIM3->CCR3 = 0;   
					TIM3->CCR4 = 0;   
					current_speed_forward = MIN_SPEED;  // Reset forward speed
					current_speed_backward = MIN_SPEED; // Reset backward speed
					
					TIM6->CR1 = 0;         // Stop the TIM6 timer		
					TIM6->CNT = 0;         // Reset the TIM6 counter to 0
					systemState=0;  
			}
		  //SendTxt_usart3(RX_Buffer);
		  ClearBuffer(BLE_REC_Buffer, sizeof(BLE_REC_Buffer));
			i=0;
			USART3->SR;
			USART3->DR;		
	}

}



