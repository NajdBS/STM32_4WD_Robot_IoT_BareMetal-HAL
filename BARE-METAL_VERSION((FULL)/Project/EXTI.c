#include "EXTI.h"

void config_EXTI(void)
{
    RCC->APB2ENR |= 1 << 14;     // Enable SYSCFG clock
    SYSCFG->EXTICR[0] &= 0xFFF0; // Select PA0 as EXTI0 source
    EXTI->RTSR |= 0x1;           // Trigger interrupt on rising edge of PA0
    EXTI->IMR |= 0x1;            // Enable interrupt for EXTI line 0
    NVIC_EnableIRQ(EXTI0_IRQn);  // Enable EXTI0 interrupt in NVIC
}


void EXTI0_IRQHandler(void)
{
    if((EXTI->PR & 0x1) != 0)    // Check if EXTI0 interrupt is pending
    {
        systemState++;
				if (systemState == 1)
				{
				SendTxt_usart3("SYSTEM BEGIN\n");
				TIM2->CR1 = 0x1;         // Start the TIM6 timer		
				}	
				if (systemState == 2)
				{
				SendTxt_usart3("SYSTEM STOP\n");
				TIM2->CR1 = 0;         // Stop the TIM6 timer		
				TIM2->CNT = 0;         // Reset the TIM6 counter to 0
				systemState=0;  
				}	
				
        EXTI->PR |= 0x1;         // Clear the EXTI0 interrupt flag
    }
}

