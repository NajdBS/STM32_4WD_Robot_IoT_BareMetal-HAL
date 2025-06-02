#include "PWM.h"


void config_TIMER3(void)
{
    // Enable clock for Timer 3 (APB1)
    RCC->APB1ENR |= (1 << 1); //enable TIM3

    // Enable clock for GPIOA
    RCC->AHB1ENR |= 0x1; //enable GPIOA (for PA6 and PA7)
    
    // Enable clock for GPIOB
    RCC->AHB1ENR |= (1 << 1);//enable GPIOB (for PB0 and PB1)

    // Configure PA6, PA7, PB0, and PB1 in alternate function mode (AF)
    GPIOA->MODER &= ~( (3 << (2 * 6)) | (3 << (2 * 7)) ); // Clear mode bits for PA6 and PA7
    GPIOA->MODER |= ( (2 << (2 * 6)) | (2 << (2 * 7)) );  // Set PA6 and PA7 to alternate function (AF)

    GPIOB->MODER &= ~( (3 << (2 * 0)) | (3 << (2 * 1)) ); // Clear mode bits for PB0 and PB1
    GPIOB->MODER |= ( (2 << (2 * 0)) | (2 << (2 * 1)) );  // Set PB0 and PB1 to alternate function (AF)

    // Configure the alternate function for the pins (AF2 for TIM3)
    // PA6 and PA7 correspond to Timer 3 channels 1 and 2
    GPIOA->AFR[0] &= ~( (0xF << (4 * 6)) | (0xF << (4 * 7)) );  // Clear AF bits for PA6 and PA7
    GPIOA->AFR[0] |= ( (2 << (4 * 6)) | (2 << (4 * 7)) );       // Select AF2 function for PA6 and PA7

    // PB0 and PB1 correspond to Timer 3 channels 3 and 4
    GPIOB->AFR[0] &= ~( (0xF << (4 * 0)) | (0xF << (4 * 1)) );  // Clear AF bits for PB0 and PB1
    GPIOB->AFR[0] |= ( (2 << (4 * 0)) | (2 << (4 * 1)) );       // Select AF2 function for PB0 and PB1

    // Configure Timer 3
    TIM3->CCER |= 0x1111; //enables CC1E, CC2E, CC3E, CC4E (channels 1, 2, 3, 4)
    TIM3->CCMR1 |= 0x6060; //channels 1 and 2 in PWM1 mode
    TIM3->CCMR2 |= 0x6060; //channels 3 and 4 in PWM1 mode

    // Configure the prescaler (PSC) and auto-reload value (ARR)
    TIM3->PSC = 15;         //timer frequency of 1 MHz 
    TIM3->ARR = 999;        // Auto-reload value (ARR) for a 1 MHz timer, giving a period of 1 ms
    
		// Start Timer 3
    TIM3->CR1 |= 0x1;
}
