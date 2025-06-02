#include "ADC.h"

void config_GPIO_ADC_Channnel(void)
{
    RCC->AHB1ENR |= 0x1;   // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 2); // Enable GPIOC clock 

    // Configure PA1, PC4, and PC5 as Analog Input
    GPIOA->MODER |= (0x3 << 2*1);    // PA1 as Analog (11: Analog mode)
		GPIOC->MODER |= (0x3 << 2*1);    // PC1 as Analog (11: Analog mode)
    GPIOC->MODER |= (0x3 << 2*4);    // PC4 as Analog (11: Analog mode)
    GPIOC->MODER |= (0x3 << 2*5);    // PC5 as Analog (11: Analog mode)
}

//BLE send data RTOS???
/*void config_TIMER7(void)
{
    RCC->APB1ENR |= (1 << 5);     // Enable TIM7 clock (Bit 5 pour TIM7)
    TIM7->PSC = 15999;            // Set prescaler to 15999
    TIM7->ARR = 1999;              // Set auto-reload to 999 (1 second interval)
    TIM7->DIER = 0x1;             // Enable update interrupt
    NVIC_EnableIRQ(TIM7_IRQn);    // Enable TIM7 interrupt in NVIC
}

void TIM7_IRQHandler(void)
{
    if(((TIM7->SR & 0x1) != 0)&&(ADC1->SR & 0x2)) // If update flag is set (UIF=1)
    {
				temperature=DS1621_Read_Temp();
				sprintf(BLE_SEND_Buffer,"CH1=%d CH2=%d CH3=%d Temp_DS1621=%.2f C\n",ADC_Value[0],ADC_Value[1],ADC_Value[2],temperature);
				SendTxt_usart3(BLE_SEND_Buffer);
				ClearBuffer(BLE_SEND_Buffer, sizeof(BLE_SEND_Buffer));
		}
        TIM7->SR &= ~0x1; // Clear the interrupt flag (UIF=0)
}*/
  


void config_TIMER2(void)
{
    // Enable clock for Timer 2 (APB1)
    RCC->APB1ENR |= (1 << 0); //enable TIM2
    
    // Configure the prescaler (PSC) and auto-reload value (ARR)
    TIM2->PSC = 15999;     // Prescaler: 16 MHz / (15999 + 1) = 1 kHz
    TIM2->ARR = dataUploadInterval;     // Auto-reload value for ...-second interval
	  
    // Configure TRGO (Trigger Output) to send an "Update Event" signal to ADC
    TIM2->CR2 &= ~(7 << 4); // Clear MMS bits (bits 6:4)
    TIM2->CR2 |= (2 << 4);  // Set MMS = 010 (Update Event as TRGO)

    // Start Timer 2
    //TIM2->CR1 |= 0x1;
}


void config_ADC1(void)
{
    // Enable ADC1 clock
    RCC->APB2ENR |= (1 << 8);    // Enable ADC1 clock

    // Configure ADC1
    ADC1->CR1 |= (1 << 8);       // SCAN mode enabled (multi-channel)
    ADC1->CR1 |= (1 << 11);      // Discontinuous mode enabled (DISCEN)
    ADC1->CR1 &= ~(0b111 << 13); // Clear [15:13] bits DISCNUM 
    ADC1->CR1 |= (3 << 13); //Set DISCNUM = 011 (4 channel)

    // Configure sequence for channels 1, 14, and 15
    ADC1->SQR1 &= ~(0xF << 20);  // Clear L bits [23:20]
    ADC1->SQR1 |= 3 << 20;      // Set L = 3 (Total 4 conversions: L+1 = 4)
    ADC1->SQR3 = (1 << 0) | (14 << 5) | (15 << 10) | (11 << 15);

		// Configure sampling time
	  //ADC1->SMPR2 &= ~((0b111 << 3) ); // Clear [5:3] bits, N1 = 3 ,channel sampling time : tconv = (3+12) * (1/8) ~= 2µs /PCLK2=2
    //ADC1->SMPR1 &= ~((0b111 << 3) | (0b111 << 12) | (0b111 << 16));
		// Configure ADC/DMA
    ADC1->CR2 |= (1 << 8) | (1 << 9);  // Enable DMA Mode and Continuous DMA Requests

	
    // Select External Trigger Source: TIM6_TRGO (EXTSEL = 0110)
    ADC1->CR2 &= ~(15 << 24);  // Clear EXTSEL bits [27:24]
    ADC1->CR2 |= (6 << 24);    // Set EXTSEL = 0110 (TIM6_TRGO)
    ADC1->CR2 &= ~(3 << 28);   // Clear EXTEN bits [29:28]
    ADC1->CR2 |= (1 << 28);    // Set EXTEN = 01 (Trigger on rising edge)
    
    // Enable ADC
    ADC1->CR2 |= 1;            // Turn on ADC
}

/*void config_DMA2(void)
{
		RCC->AHB1ENR |= 1<<22;// Enable DMA2 clock
	
		DMA2_Stream0->CR &= ~(0b111);// Select Channel 0 for ADC1
		//DMA2_Stream0->CR &= ~(0b11<<16);// Low Level Priority
		DMA2_Stream0->CR |= 1<<8;// Enable circular mode
		
		DMA2_Stream0->CR |= 1<<13;// Memory data size 16-bit
		DMA2_Stream0->CR |= 1<<11;// Peripheral data size 16-bit
		//DMA2_Stream0->CR &= ~(1<<6);// Data direction : Peripheral to Memory
		DMA2_Stream0->CR |= 1<<10;// Memory increment
		DMA2_Stream0->CR |= 1<<4;// Enable TCIE
		//DMA2_Stream0->CR &= ~(1<<18);// DBM=0;
		
		DMA2_Stream0->NDTR = 3;// Number of data to transfer
		DMA2_Stream0->M0AR = (uint32_t)&ADC_Value[0];// Set memory address : Address destination
		DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;// Set peripheral address : Address source
		
		//DMA2_Stream0->FCR &=~ (1<<2);// Enable Direct Mode and disable FIFO
		NVIC_EnableIRQ(DMA2_Stream0_IRQn);   // Enable DMA2_Stream0 global interrupt	
		DMA2_Stream0->CR |= 1<<0;// Enable STREAM   
}*/
void config_DMA2(void)
{
		RCC->AHB1ENR |= 1<<22;// Enable DMA2 clock
	
		DMA2_Stream0->CR &= ~(0b111);// Select Channel 0 for ADC1
		//DMA2_Stream0->CR &= ~(0b11<<16);// Low Level Priority
		DMA2_Stream0->CR |= 1<<8;// Enable circular mode
		
		DMA2_Stream0->CR |= 1<<13;// Memory data size 16-bit
		DMA2_Stream0->CR |= 1<<11;// Peripheral data size 16-bit
		//DMA2_Stream0->CR &= ~(1<<6);// Data direction : Peripheral to Memory
		DMA2_Stream0->CR |= 1<<10;// Memory increment
		DMA2_Stream0->CR |= 1<<4;// Enable TCIE
		//DMA2_Stream0->CR &= ~(1<<18);// DBM=0;
		
		DMA2_Stream0->NDTR = 4;// Number of data to transfer
		DMA2_Stream0->M0AR = (uint32_t)&ADC_Value[0];// Set memory address : Address destination
		DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;// Set peripheral address : Address source
		
		//DMA2_Stream0->FCR &=~ (1<<2);// Enable Direct Mode and disable FIFO
		//FIFO Mode
		DMA2_Stream0->CR |= 2<<23;//MBURST
		DMA2_Stream0->CR |= 2<<21;//PBURST
    DMA2_Stream0->FCR |= (1 << 2); // Enable FIFO,Disable Direct Mode
    //DMA2_Stream0->FCR |= (1 << 0); // FIFO Threshold = (50%)
		DMA2_Stream0->FCR |= ( 3<< 0); // FIFO Threshold = (100%)
		
		NVIC_EnableIRQ(DMA2_Stream0_IRQn);   // Enable DMA2_Stream0 global interrupt	
		DMA2_Stream0->CR |= 1<<0;// Enable STREAM   
}


void DMA2_Stream0_IRQHandler(void) {
		if (DMA2->LISR & (1 << 5)) // Check if Transfer Complete (TCIF0) is set
		{  
		flag=true;
		DMA2->LIFCR |= (1 << 5);// Clear the interrupt flag
    }
}


