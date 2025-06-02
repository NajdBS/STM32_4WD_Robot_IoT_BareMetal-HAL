#ifndef TIMER3_CONFIG_H
#define TIMER3_CONFIG_H

#include "stm32f4xx.h"  // Include the STM32F4 specific library

#define MAX_SPEED 999     // Maximum value for CCR (maximum speed)
#define MIN_SPEED 300     // Minimum speed 
#define START_SPEED 500   // Starting speed 
#define STEP_SPEED 100    // Step size to increase/decrease speed
#define TURNING_SPEED 700 // Speed for turning (left or right)

extern int current_speed_forward;
extern int current_speed_backward;

// Function prototype for TIM3 initialization
void config_TIMER3(void);

#endif // TIMER3_CONFIG_H
