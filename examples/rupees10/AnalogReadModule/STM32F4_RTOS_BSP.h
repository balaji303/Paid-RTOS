#ifndef __STM32F4_RTOS_BSP_H
#define __STM32F4_RTOS_BSP_H
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "GLCD_ST7735.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

extern ADC_HandleTypeDef hadc1;

#define PROBE_PORT	GPIOC        //PORT for probe
#define CH0					GPIO_PIN_0   //Probe Channel 0 PIN
#define CH1					GPIO_PIN_1   //Probe Channel 1 PIN
#define CH2					GPIO_PIN_2   //Probe Channel 2 PIN
#define CH3					GPIO_PIN_3   //Probe Channel 3 PIN

#define HAL_OK		1
/**
	* @brief Configure System clock to run at 80Mhz
	* @input  None
	* @retval None
  */

void SystemClock_Config80Mhz(void);

/**
  *@brief  Initialize ADC1
	*@input  None
	*@retval None
	*/
	
void ADC1_Init(void);
/**
	*@brief  Generate milliseconds delay using general purpose timer
	*@input  Number of milliseconds delay
	*@retval None
 */
void DelayMs(uint32_t _time);

/**
  *@brief  Initialize General Purpose TIMER 2
	*@input  None
	*@retval None
	*/

void TIM2_Init(void);

/**
  *@brief  Initialize General Purpose TIMER 3
	*@input  None
	*@retval None
	*/
void TIM3_Init(void);
/**
  *@brief  Initialize General Purpose TIMER 4
	*@input  None
	*@retval None
	*/
void TIM4_Init(void);
/**
  *@brief  Initialize General Purpose TIMER 5
	*@input  None
	*@retval None
	*/
void TIM5_Init(void);
/**
  *@brief  Initialize General Purpose TIMER 2 and Configure Interrupt
	*@input  None
	*@retval None
	*/
void TIM2_Init_Start(void);

/**
  *@brief  Initialize General Purpose TIMER 3 and Configure Interrupt
	*@input  None
	*@retval None
	*/
void TIM3_Init_Start(void);
/**
  *@brief  Initialize General Purpose TIMER 4 and Configure Interrupt
	*@input  None
	*@retval None
	*/
void TIM4_Init_Start(void);
/**
  *@brief  Initialize General Purpose TIMER 5 and Configure Interrupt
	*@input  None
	*@retval None
	*/
void TIM5_Init_Start(void);

/**
  *@brief  Initialize 4 GPIOC pins as output
	*@input  None
	*@retval None
	*/
	
void Probe_Init(void);


/**
  *@brief  Toggle GPIOC_PIN_0
	*@input  None
	*@retval None
	*/
	
void Probe_CH0(void);

/**
  *@brief  Toggle GPIOC_PIN_1
	*@input  None
	*@retval None
	*/
void Probe_CH1(void);

/**
  *@brief  Toggle GPIOC_PIN_2
	*@input  None
	*@retval None
	*/

void Probe_CH2(void);

/**
  *@brief  Toggle GPIOC_PIN_3
	*@input  None
	*@retval None
	*/

void Probe_CH3(void);

#endif

