#include "stm32f4xx.h"

/****************************************************************************************/
void I2C1_Init(void);
void Start_i2c(void);
void Stop_i2c(void);
void Write_addr_i2c(uint8_t addr, uint8_t rw);
void Write_data_i2c(uint8_t data);
void Write_one_data_i2c(uint8_t data);
void Write_last_data_i2c(uint8_t data);
uint8_t Read_data_i2c(void);
uint8_t Read_last_data_i2c(void);


