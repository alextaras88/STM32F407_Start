#include "I2C.h"

/****************************************************************************************/
void I2C1_Init(void){
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;				// Clock PORT B
	GPIOB->AFR[0] |= (4<<24)|(4<<28);						// AF4 for Gpio Pins
	
	// PB6 SCL
	GPIOB->MODER |= GPIO_MODER_MODE6_1;					// AF OD
	GPIOB->OTYPER |= GPIO_OTYPER_OT6;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;		// Full speed
	
	
	// PB7 SDA
	GPIOB->MODER |= GPIO_MODER_MODE7_1;					// AF OD
	GPIOB->OTYPER |= GPIO_OTYPER_OT7;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;		// Full speed
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;					// Clock I2C1
	
	I2C1->CR1 |= I2C_CR1_SWRST;									// Soft Reset
	I2C1->CR1 &= ~I2C_CR1_SWRST;
	
	I2C1->CR2 &= ~I2C_CR2_FREQ;								 // Peripheral clock frequency
	I2C1->CR2 |= 42;

	I2C1->CCR &= ~I2C_CCR_CCR;
	I2C1->CCR = 210;

	I2C1->TRISE = 43;
	
	I2C1->CR1 |= I2C_CR1_PE;									 // Enable I2C1

}
/****************************************************************************************/
void Start_i2c(void){
	
	I2C1->CR1 |= I2C_CR1_START;   						// Start i2c
	while (!(I2C1->SR1 & I2C_SR1_SB)){};			// Wait Start
	(void) I2C1->SR1;
	
}
/****************************************************************************************************/
void Stop_i2c(void){
	
	
	I2C1->CR1 |= I2C_CR1_STOP;
	
}
/****************************************************************************************************/
void Write_addr_i2c(uint8_t addr, uint8_t rw){

	switch(rw){

	case 0:
		I2C1->DR = (addr<<1)+0;
		 break;
	case 1:
		I2C1->DR = (addr<<1)+1;
			 break;

	}

	while (!(I2C1->SR1 & I2C_SR1_ADDR)){}
	(void) I2C1->SR1;
	(void) I2C1->SR2;
		
	}
/****************************************************************************************************/
void Write_data_i2c(uint8_t data){

	while (!(I2C1->SR1 & I2C_SR1_TXE)){}
	I2C1->DR = data;	
	(void) I2C1->SR1;
	I2C1->CR1 |= I2C_CR1_ACK;
	(void) I2C1->SR2;

}
/****************************************************************************************************/
void Write_one_data_i2c(uint8_t data){

	while (!(I2C1->SR1 & I2C_SR1_TXE)){};
	I2C1->DR = data;	
	while (!(I2C1->SR1 & I2C_SR1_BTF)){};

}
/****************************************************************************************************/
void Write_last_data_i2c(uint8_t data){
		
	while (!(I2C1->SR1 & I2C_SR1_TXE)){}
	I2C1->DR = data;	
	(void) I2C1->SR1;
	(void) I2C1->SR2;
		
}
/****************************************************************************************************/	
uint8_t Read_data_i2c(void){
	
	I2C1->CR1 |= I2C_CR1_ACK;	
  while (!(I2C1->SR1 & I2C_SR1_RXNE)){};
			
  return I2C1->DR;
		
}
/****************************************************************************************************/
uint8_t Read_last_data_i2c(void){
	
	uint8_t data;
	
	(void) I2C1->SR1;
	(void) I2C1->SR2;
	I2C1->CR1 &= ~I2C_CR1_ACK;
  while (!(I2C1->SR1 & I2C_SR1_RXNE)){};
	data = I2C1->DR;
	Stop_i2c();
		
  return data;
		
}
/****************************************************************************************/


