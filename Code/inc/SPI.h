#include "stm32f4xx.h"

#define SPI1_CS_LOW		GPIOA->ODR &= ~GPIO_ODR_ODR_4;
#define SPI1_CS_HIGH	GPIOA->ODR |= GPIO_ODR_ODR_4;

#define SPI_IS_BUSY(SPIx)         (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))
#define SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))

/****************************************************************************************/
void SPI1_Init(void);
uint8_t Spi1_transfer_8(SPI_TypeDef* SPIx, uint8_t data);
void Spi1_multi_transfer_8(SPI_TypeDef* SPIx, uint8_t* dataOUT,uint8_t* dataIN, uint16_t size);
/****************************************************************************************/
