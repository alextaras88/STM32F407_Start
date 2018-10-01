#include "SPI.h"

/****************************************************************************************/
void SPI1_Init(void){
	
	// GPIO INIT
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;								// Clock GPIOA
	GPIOA->AFR[0] |= (5<<20)|(5<<24)|(5<<28);						// PA5, PA6, PA7  GPIO AF5

	// PA5 SCK
	GPIOA->MODER |= GPIO_MODER_MODER5_1;								// AF 
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;									// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;           // Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;									// No pull-up, pull-down
	
	// PA6 MISO
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
  GPIOA->MODER |= GPIO_MODER_MODER6_1;								// INPUT Floating
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR6;		
	
	// PA7 MOSI
	GPIOA->MODER |= GPIO_MODER_MODER7_1;								// AF 
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT7;									// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;           // Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7;									// No pull-up, pull-down
	
	// PA4 CS
	GPIOA->MODER |= GPIO_MODER_MODER4_0;								// OUTPUT 
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT4;									// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;           // Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR4;									// No pull-up, pull-down
	
	SPI1_CS_HIGH;
	
	// SPI1 INIT
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;									// Clock SPI1
	
	SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;           // Spi Clock div 84MHz/128 ()
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI1->CR1 &= ~SPI_CR1_DFF;													// 8 Bit Data
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;											// MSB First
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;							// Software slave management & Internal slave select
	SPI1->CR1 |= SPI_CR1_MSTR;													// SPI Master Mode
	
	SPI1->CR1 |= SPI_CR1_SPE;														// SPI Enable
	
}
/****************************************************************************************/
 uint8_t Spi1_transfer_8(SPI_TypeDef* SPIx, uint8_t data){ 
	
	SPI_WAIT(SPIx);
	SPI1->DR = data;
	SPI_WAIT(SPIx);
	
	return SPIx->DR;
	
}
/****************************************************************************************/
void Spi1_multi_transfer_8(SPI_TypeDef* SPIx, uint8_t* dataOUT,uint8_t* dataIN, uint16_t size){
	
	uint16_t i;
	
	SPI_WAIT(SPIx);
	
	for(i=0;i<size;i++){
		
		SPIx->DR = dataOUT[i];
		SPI_WAIT(SPIx);
		dataIN[i] = SPIx->DR;
		
	}

}
/****************************************************************************************/






