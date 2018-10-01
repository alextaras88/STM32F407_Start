#include "main.h"

char str[40];
float T;
float H;

int main ()
{
		
	RCC_Init();
	//MCO2_Init();
	GPIO_Init();
	Delay_Init();
	
//SPI1_Init();
	USART2_Init();
	//LIS3_Init();
	Delay_ms(100);
	I2C1_Init();
	Delay_ms(100);
	htu21d_SoftReset();
	Delay_ms(300);
	
	while(1){
		
		T =  ht21d_GetTemp();
		H =  ht21d_GetHumidity();
		sprintf(str, "T = %.2f" "  H = %.1f\r\n", T, H);
		USART2_Send_String(str);
		GPIOD->ODR ^= GPIO_ODR_ODR_12;
		
	}

}

