#include "stm32f4xx.h"

/****************************************************************************************/
void USART2_Init(void);
void USART2_Send (char chr);
void USART2_MultiSend(uint8_t *chr, uint16_t size);
void USART2_Send_String (char* str);

void USART2_IRQHandler (void);
/****************************************************************************************/

