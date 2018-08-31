#include "Start_Init.h"

//---------------------------------------------------------------------------------------------------------------------------

void RCC_Init(void)
	{   
	
		RCC->CR |= ((uint32_t)RCC_CR_HSEON);								// Enable HSE
	  while(!(RCC->CR & RCC_CR_HSERDY));                  // Wait HSE enable flag
	
		RCC->APB1ENR |= RCC_APB1ENR_PWREN;									// Enable PWR clock
		PWR->CR |= PWR_CR_VOS;															// Scale 1 mode (default value at reset)
	
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;	                	// AHB/1
		RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;										// APB2/2			   
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;										// APB1/4
	
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;									// Reset PLLM
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;									// Reset PLLN
		RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;                 	// Reset PLLP
		
		RCC->PLLCFGR = RCC_PLLCFGR_PLLM_2 | 								// PLLM=8, PLLN=168, PLLP=2, PLL source HSE ->168MHz
		RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_5 | 
		RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLSRC_HSE;
		 
		RCC->CR |= RCC_CR_PLLON;                      	    // Enable PLL
		while((RCC->CR & RCC_CR_PLLRDY) == 0){}            	// Wait PLL enable flag
	
		FLASH->ACR = FLASH_ACR_PRFTEN | 
		FLASH_ACR_ICEN | FLASH_ACR_DCEN |										// Config Flash
		FLASH_ACR_LATENCY_5WS;
	
		RCC->CFGR &= ~RCC_CFGR_SW;                   		    // Reset SW
		RCC->CFGR |= RCC_CFGR_SW_PLL;                 			// SYSCLK = PLL					
		while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}// Wait PLL-SYSCLK flag
		
	}

//---------------------------------------------------------------------------------------------------------------------------


void MCO1_Init(void)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;								// Clock GPIOA
	
		GPIOA->MODER |= GPIO_MODER_MODER8_1;  							// AF PA8
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT_8;  								// PP 
		GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8;						// Vety high speed
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR8;									// No pull-up, pull-down
	
		RCC->CFGR |= RCC_CFGR_MCO1PRE;
		RCC->CFGR |= RCC_CFGR_MCO1;
	
	}

//---------------------------------------------------------------------------------------------------------------------------

void MCO2_Init(void)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;									// Clock GPIOC
	
		GPIOC->MODER |= GPIO_MODER_MODER9_1;  								// AF PC_9
		GPIOC->OTYPER &= ~GPIO_OTYPER_OT_9;  									// PP 
		GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;							// Vety high speed
		GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR9;										// No pull-up, pull-down
	
		RCC->CFGR |= RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_2 ;  // /4
		//RCC->CFGR |= RCC_CFGR_MCO2;														// PLL
		RCC->CFGR &= ~RCC_CFGR_MCO2; 													  // SYSCLK
	
	}

//---------------------------------------------------------------------------------------------------------------------------

void GPIO_Init(void)
	{
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;                 	// Clock GPIOA
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;                 	// Clock GPIOD
	
		GPIOA->MODER &= ~GPIO_MODER_MODER0;					  			 	// IN PA_0
		GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;                 	// Push down
	
		GPIOD->MODER |= GPIO_MODER_MODER12_0;   			 			 	// OUT PD_12
		GPIOD->OTYPER &= ~GPIO_OTYPER_OT_12;  							 	// Push pull
		GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_1;	     		// High speed
	
		GPIOD->MODER |= GPIO_MODER_MODER13_0;   			 				// OUT PD_13
		GPIOD->OTYPER &= ~GPIO_OTYPER_OT_13;  				 				// Push pull
		GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;	    	 	// High speed
	
		GPIOD->MODER |= GPIO_MODER_MODER14_0;   			 				// OUT PD_14
		GPIOD->OTYPER &= ~GPIO_OTYPER_OT_14;  				 				// Push pull
		GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;	     		// High speed
	
		GPIOD->MODER |= GPIO_MODER_MODER15_0;   			 				// OUT PD_15
		GPIOD->OTYPER &= ~GPIO_OTYPER_OT_15;  				 				// Push pull
		GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_1;	     		// High speed
	
	}

