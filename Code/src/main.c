#include "main.h"

int main ()
{
	//uint32_t i = 0;
	//uint8_t status = 0;
		
	RCC_Init();
	MCO2_Init();
	GPIO_Init();
	Delay_Init();
	
	while(1)
	{
		GPIOD->BSRR |= GPIO_BSRR_BS_13;
		Delay_ms(500);
		GPIOD->BSRR |= GPIO_BSRR_BR_13;
		Delay_ms(500);
//		if ((GPIOA->IDR & GPIO_IDR_IDR_0) != 0)
//			{
//				for (i = 0; i<200000; i++) {}
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
//				for (i = 0; i<4000000; i++) {}
//				GPIOD->ODR &= ~GPIO_ODR_ODR_12;
//				GPIOD->ODR |= GPIO_ODR_ODR_14;
//				for (i = 0; i<4000000; i++) {}
//			break;
//				
//			case 1:
//				GPIOD->ODR &= ~(GPIO_ODR_ODR_12 |
//				GPIO_ODR_ODR_13 |
//				GPIO_ODR_ODR_14 |
//				GPIO_ODR_ODR_15);
//				GPIOD->ODR |= GPIO_ODR_ODR_13;
//				GPIOD->ODR &= ~GPIO_ODR_ODR_15;
//				for (i = 0; i<2000000; i++) {}
//				GPIOD->ODR &= ~GPIO_ODR_ODR_13;
//				GPIOD->ODR |= GPIO_ODR_ODR_15;
//				for (i = 0; i<2000000; i++) {}
//			break;
//				
//			case 2:
//				GPIOD->ODR &= ~(GPIO_ODR_ODR_12 |
//				GPIO_ODR_ODR_13 |
//				GPIO_ODR_ODR_14 |
//				GPIO_ODR_ODR_15);
//				GPIOD->ODR &= ~GPIO_ODR_ODR_15;
//				GPIOD->ODR |= GPIO_ODR_ODR_12;
//				for (i = 0; i<1000000; i++) {}
//				GPIOD->ODR &= ~GPIO_ODR_ODR_12;
//				GPIOD->ODR |= GPIO_ODR_ODR_13;
//				for (i = 0; i<1000000; i++) {}
//				GPIOD->ODR &= ~GPIO_ODR_ODR_13;
//				GPIOD->ODR |= GPIO_ODR_ODR_14;
//				for (i = 0; i<1000000; i++) {}
//				GPIOD->ODR &= ~GPIO_ODR_ODR_14;
//				GPIOD->ODR |= GPIO_ODR_ODR_15;
//				for (i = 0; i<1000000; i++) {}
//			break;
//							
//			}

	}

}

