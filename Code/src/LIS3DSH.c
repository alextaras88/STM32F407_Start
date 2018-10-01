#include "LIS3DSH.h"

uint8_t buf2[8]={0};
char str1[30];

/****************************************************************************************/
void LIS3_SPI_Init(void){
	
	// GPIO INIT
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;								// Clock GPIOA
	GPIOA->AFR[0] |= (5<<20)|(5<<24)|(5<<28);						// PA5, PA6, PA7  GPIO AF5

	// PA5 SCK
	GPIOA->MODER |= GPIO_MODER_MODER5_1;								// AF 
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;									// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;           // Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;									// No pull-up, pull-down
	
	// PA6 MISO
	GPIOA->MODER &= ~GPIO_MODER_MODER6;									// INPUT Floating
	GPIOA->MODER |= GPIO_MODER_MODER6_1;	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR6;		
	
	// PA7 MOSI
	GPIOA->MODER |= GPIO_MODER_MODER7_1;								// AF 
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT7;									// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;           // Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7;									// No pull-up, pull-down
	
	// SPI1 INIT
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;									// Clock SPI1
	
	SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0;           // Spi Clock div 84MHz/16 (5.2Mb/s)
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI1->CR1 &= ~SPI_CR1_DFF;													// 8 Bit Data
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;											// MSB First
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;							// Software slave management & Internal slave select
	SPI1->CR1 |= SPI_CR1_MSTR;													// SPI Master Mode
	
	SPI1->CR1 |= SPI_CR1_SPE;								

}
/****************************************************************************************/
void LIS3_GPIO_Init(void){
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;								// Clock GPIOE
	
	// INT1 PE0 Input
	
	// INT2 PE1 Input
	
	// LIS3_CS PE3
	GPIOE->MODER |= GPIO_MODER_MODER3_0;								// OUTPUT 
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT3;									// PP
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;           // Full Speed
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR3;									// No pull-up, pull-down
	
	LIS3_CS_HIGH;

}
/****************************************************************************************/
void LIS3_Init(void){
	uint8_t ctrl = 0;
	
	LIS3_GPIO_Init();
	LIS3_SPI_Init();
	
	if(LIS3_ReadID() == 0x3F){
		
		GPIOD->ODR |= GPIO_ODR_ODR_13;
		Delay_ms(1000);
		GPIOD->ODR &= ~GPIO_ODR_ODR_13;
		
	

	}
	
	ctrl = (uint16_t) (LIS3DSH_DATARATE_100 | LIS3DSH_XYZ_ENABLE);
	ctrl |= ((uint16_t) (LIS3DSH_SERIALINTERFACE_4WIRE|\
											LIS3DSH_SELFTEST_NORMAL|\
											LIS3DSH_FULLSCALE_2|\
											LIS3DSH_FILTER_BW_800))<<8;
	
	
	 
	ctrl=(uint8_t)(ctrl);
	LIS3_IO_Write(&ctrl, LIS3DSH_CTRL_REG4_ADDR,1);
	ctrl=(uint8_t)(ctrl>>8);
  LIS3_IO_Write(&ctrl, LIS3DSH_CTRL_REG5_ADDR,1);

}
/****************************************************************************************/
void LIS3_IO_Read(uint8_t *buff, uint8_t readaddr, uint16_t size){
	
	uint16_t i = 0;
	
	 if(size > 0x01){

    readaddr |= (uint8_t)(READWRITE_CMD | MULTIPLEBYTE_CMD);

  }
  else{
		
    readaddr |= (uint8_t)READWRITE_CMD;
		
  }
	
	LIS3_CS_LOW;
	Spi1_transfer_8(SPI1, readaddr);
	
	for(i = 0;i<size;i++){
		 
		 buff[i] = Spi1_transfer_8(SPI1, DUMMY_BYTE);
	 }
	 
	 LIS3_CS_HIGH;
	 
}
/****************************************************************************************/
void LIS3_IO_Write(uint8_t *buff, uint8_t writeaddr, uint16_t size){
	
	uint16_t i = 0;
	

	LIS3_CS_HIGH;

  if(size > 0x01){
		
		writeaddr |= (uint8_t)MULTIPLEBYTE_CMD;

}

	LIS3_CS_LOW;

	Spi1_transfer_8(SPI1, writeaddr);

	for(i=0;i<size;i++){
		
		Spi1_transfer_8(SPI1, buff[i]);

	}
	
	LIS3_CS_HIGH;
	
}
/****************************************************************************************/
uint8_t LIS3_ReadID(void){ 
	
	uint8_t id = 0;
	
	LIS3_IO_Read(&id, LIS3DSH_WHO_AM_I_ADDR, 1);
	
	return id;
 
}
/****************************************************************************************/
void LIS3_GetXYZ(int16_t* pData){
	
	int8_t buffer[6];
  uint8_t ctrl,i = 0x00;
	
	float sensitivity = LIS3DSH_SENSITIVITY_0_06G;
	float valueinfloat = 0;
	
	LIS3_IO_Read(&ctrl, LIS3DSH_CTRL_REG5_ADDR,1);
	LIS3_IO_Read((uint8_t*)&buffer[0], LIS3DSH_OUT_X_L_ADDR,1);
	LIS3_IO_Read((uint8_t*)&buffer[1], LIS3DSH_OUT_X_H_ADDR,1);
	LIS3_IO_Read((uint8_t*)&buffer[2], LIS3DSH_OUT_Y_L_ADDR,1);
	LIS3_IO_Read((uint8_t*)&buffer[3], LIS3DSH_OUT_Y_H_ADDR,1);
	LIS3_IO_Read((uint8_t*)&buffer[4], LIS3DSH_OUT_Z_L_ADDR,1);
	LIS3_IO_Read((uint8_t*)&buffer[5], LIS3DSH_OUT_Z_H_ADDR,1);
	switch(ctrl&LIS3DSH__FULLSCALE_SELECTION)
	{
		case LIS3DSH_FULLSCALE_2:
			sensitivity=LIS3DSH_SENSITIVITY_0_06G;
			break;
		case LIS3DSH_FULLSCALE_4:
			sensitivity=LIS3DSH_SENSITIVITY_0_12G;
			break;
		case LIS3DSH_FULLSCALE_6:
			sensitivity=LIS3DSH_SENSITIVITY_0_18G;
			break;
		case LIS3DSH_FULLSCALE_8:
			sensitivity=LIS3DSH_SENSITIVITY_0_24G;
			break;
		case LIS3DSH_FULLSCALE_16:
			sensitivity=LIS3DSH_SENSITIVITY_0_73G;
			break;
		default:
			break;
	}
	for(i=0;i<3;i++)
	{
		valueinfloat = ((buffer[2*i+1] << 8) + buffer[2*i]);
		//*sensitivity;
		pData[i]=(int16_t)valueinfloat;
	}
	
}
/****************************************************************************************/
void LIS3_ReadAcc(void){
	
	int16_t buffer[3]={0};
	int16_t xval, yval, zval = 0x0000;
	
	LIS3_GetXYZ(buffer);
	xval = buffer[0];
	yval = buffer[1];
	zval = buffer[2];
	sprintf(str1,"X:%06d Y:%06d Z:%06d\r\n", xval, yval, zval);
	USART2_Send_String (str1);
//	buf2[0]=0x11;
//	buf2[1]=0x55;
//	buf2[2]=(uint8_t)(xval>>8);
//	buf2[3]=(uint8_t)xval;
//	buf2[4]=(uint8_t)(yval>>8);
//	buf2[5]=(uint8_t)yval;
//	buf2[6]=(uint8_t)(zval>>8);
//	buf2[7]=(uint8_t)zval;
	//USART2_MultiSend(buf2, 8);
	
	if((ABS(xval))>(ABS(yval)))
	{
		if(xval>2000)
		{
			GPIOD->ODR |= GPIO_ODR_ODR_14;
		}
		else if(xval<-2000)
		{
			GPIOD->ODR |= GPIO_ODR_ODR_12;
		}
	}
	else
	{
		if(yval>2000)
		{
			GPIOD->ODR |= GPIO_ODR_ODR_13;
		}
		else if(yval<-2000)
		{
			GPIOD->ODR |= GPIO_ODR_ODR_15;
		}
	}
	Delay_ms(20);
	GPIOD->ODR &= ~GPIO_ODR_ODR_12;
	GPIOD->ODR &= ~GPIO_ODR_ODR_13;
	GPIOD->ODR &= ~GPIO_ODR_ODR_14;
	GPIOD->ODR &= ~GPIO_ODR_ODR_15;

}
/****************************************************************************************/

