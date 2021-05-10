#include "STM32F4_RTOS_BSP.h"
#define YMAX 5000
#define YMIN 0

uint32_t sensorValue;
void drawInfoBar(void);
void drawaxes(void);
void plotData(void);

int main(void)
{
	HAL_Init();
	ADC1_Init();
	
	ST7735_Init();
	drawaxes();
	while(1)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		sensorValue =HAL_ADC_GetValue(&hadc1);
		drawInfoBar();
		plotData();

	}
}


void drawInfoBar(void)
{
	ST7735_DrawString(1,0,"CPU =", GREEN);
	 ST7735_DrawString(7, 0, "75%", BLUE );
    ST7735_DrawString(11, 0, "Temp =", GREEN);
   	    ST7735_DrawString(18, 0, "30", BLUE );
	    

}

void drawaxes(void)
{
	ST7735_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "ADC", LIGHTGREEN, "", 0, YMAX, YMIN);
	
}

void plotData(void)
{
	ST7735_PlotPoint(sensorValue,GREEN);
	ST7735_PlotIncrement();
}
