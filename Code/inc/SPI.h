#include "stm32f4xx.h"

#define SPI1_CS_LOW		GPIOA->ODR &= ~GPIO_ODR_ODR_4;
#define SPI1_CS_HIGH	GPIOA->ODR |= GPIO_ODR_ODR_4;

/****************************************************************************************/
void SPI1_Init(void);
void Spi1_Write_Data8(uint8_t data);
uint8_t Spi1_Write_Read_Data8(uint8_t data);
/****************************************************************************************/
