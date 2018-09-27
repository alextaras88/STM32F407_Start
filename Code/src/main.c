#include "main.h"

int main ()
{
	
	//uint8_t status = 0;
		
	RCC_Init();
	//MCO2_Init();
	GPIO_Init();
	Delay_Init();
	
	//SPI1_Init();
	USART2_Init();
	
	USART2_Send_String ("STM32F4_TEST_USART\r\n0");
	
	while(1)
	{
		
//		SPI1_CS_LOW;
//		Spi1_Write_Data8(0x01);
//		Spi1_Write_Data8(0x02);
//		Spi1_Write_Data8(0x03);
//		Spi1_Write_Data8(0x55);
//		Spi1_Write_Data8(0x0D);
//		SPI1_CS_HIGH;
//		GPIOD->ODR ^= GPIO_ODR_ODR_12;
//		Delay_ms(200);
//		
//		if ((GPIOA->IDR & GPIO_IDR_IDR_0) != 0)
//			{
//				Delay_ms(200);
//				if ((GPIOA->IDR & GPIO_IDR_IDR_0) != 0)
//				{
//					status++;
//				}
//				if (status > 2){status = 0;}
//			}	
//			
//			switch (status)
//			{
//			case 0:
//				GPIOD->ODR &= ~(GPIO_ODR_ODR_12 |
//				GPIO_ODR_ODR_13 |
//				GPIO_ODR_ODR_14 |
//				GPIO_ODR_ODR_15);
//				GPIOD->ODR |= GPIO_ODR_ODR_12;
//				GPIOD->ODR &= ~GPIO_ODR_ODR_14;
//				Delay_ms(200);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_12;
//				GPIOD->ODR |= GPIO_ODR_ODR_14;
//				Delay_ms(200);
//			break;
//				
//			case 1:
//				GPIOD->ODR &= ~(GPIO_ODR_ODR_12 |
//				GPIO_ODR_ODR_13 |
//				GPIO_ODR_ODR_14 |
//				GPIO_ODR_ODR_15);
//				GPIOD->ODR |= GPIO_ODR_ODR_13;
//				GPIOD->ODR &= ~GPIO_ODR_ODR_15;
//				Delay_ms(500);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_13;
//				GPIOD->ODR |= GPIO_ODR_ODR_15;
//				Delay_ms(500);
//			break;
//				
//			case 2:
//				GPIOD->ODR &= ~(GPIO_ODR_ODR_12 |
//				GPIO_ODR_ODR_13 |
//				GPIO_ODR_ODR_14 |
//				GPIO_ODR_ODR_15);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_15;
//				GPIOD->ODR |= GPIO_ODR_ODR_12;
//				Delay_ms(250);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_12;
//				GPIOD->ODR |= GPIO_ODR_ODR_13;
//				Delay_ms(250);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_13;
//				GPIOD->ODR |= GPIO_ODR_ODR_14;
//				Delay_ms(250);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_14;
//				GPIOD->ODR |= GPIO_ODR_ODR_15;
//				Delay_ms(250);
//			break;
//							
//			}

	}

}

