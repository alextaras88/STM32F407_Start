#include "USART.h"

/****************************************************************************************/
void USART2_Init(void){
	
	// GPIO INIT
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;								// Clock GPIOA
	GPIOA->AFR[0] |= (7<<8)|(7<<12);										// PA2, PA3, GPIO AF7
	
	// PA2 TX
	GPIOA->MODER |= GPIO_MODER_MODER2_1;								// AF 
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT2;									// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;           // Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;									// No pull-up, pull-down
	
	// PA3 RX
	GPIOA->MODER |=  GPIO_MODER_MODER3_1;								// AF
	GPIOA->OTYPER |= GPIO_OTYPER_OT3;										// OD
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;						// Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR3;									// No pull-up, pull-down

	// USART_INIT
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;								// Clock USART2
	
	USART2->BRR = 0x0000016C;														// BRR = (F/baudrate)/16, 115200
	
	USART2->CR1   |= USART_CR1_TE;                      // Enable TX
	USART2->CR1   |= USART_CR1_RE;                      // Enable RX    
  USART2->CR1   |= USART_CR1_UE;                      // Enable USART     
  USART2->CR1     |= USART_CR1_RXNEIE;                // ENABLE Interuppts RX        
  NVIC_EnableIRQ (USART2_IRQn);                       // ENABLE Interuppts USART 
	
}
/****************************************************************************************/
void USART2_Send (char chr){                   				// Send char
	
	while (!(USART2->SR & USART_SR_TC));
	USART2->DR = chr;
	
}
/****************************************************************************************/
void USART2_Send_String (char* str){            			// Send string
	
	uint8_t i = 0;
 
	while(str[i])
	USART2_Send (str[i++]);
	
}
/****************************************************************************************/
void USART2_IRQHandler (void){ 										    // IRQ USART2
	                  
	if (USART2->SR & USART_CR1_RXNEIE){            			// IRQ USART2_RX
		
		USART2->SR &= ~USART_CR1_RXNEIE; 									// Clear flag intruppt							
		
		
		if (USART2->DR == '0'){
			
			USART2_Send_String ("OFF\r\n");
			GPIOD->ODR &= ~GPIO_ODR_ODR_14;
			
		}
		
		if (USART2->DR == '1'){
			
			USART2_Send_String ("ON\r\n");
			GPIOD->ODR |= GPIO_ODR_ODR_14;
			
		}
		
	}
	
} 	
/****************************************************************************************/


