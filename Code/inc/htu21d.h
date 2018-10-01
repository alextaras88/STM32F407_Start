#include "stm32f4xx.h"

#include "I2C.h"
#include "Delay.h"

/************************************************************************************/
#define ERROR_BAD_CRC		999

#define SHIFTED_DIVISOR 0x988000

#define TRIGGER_TEMP_MEASURE_HOLD  	 0xE3
#define TRIGGER_HUMD_MEASURE_HOLD 	 0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define WRITE_USER_REG  						 0xE6
#define READ_USER_REG  							 0xE7
#define SOFT_RESET  								 0xFE

#define USER_REGISTER_RESOLUTION_MASK 				0x81
#define USER_REGISTER_RESOLUTION_RH12_TEMP14 	0x00
#define USER_REGISTER_RESOLUTION_RH8_TEMP12 	0x01
#define USER_REGISTER_RESOLUTION_RH10_TEMP13 	0x80
#define USER_REGISTER_RESOLUTION_RH11_TEMP11 	0x81

#define USER_REGISTER_END_OF_BATTERY 		 	0x40
#define USER_REGISTER_HEATER_ENABLED 			0x04
#define USER_REGISTER_DISABLE_OTP_RELOAD 	0x02

/************************************************************************************/
void htu21d_SoftReset(void);
uint8_t CheckCRC(uint16_t message_from_sensor, uint8_t check_value_from_sensor);
uint16_t htu21d_ReadValue(uint8_t cmd);
float ht21d_GetTemp(void);
float ht21d_GetHumidity(void);
/************************************************************************************/

