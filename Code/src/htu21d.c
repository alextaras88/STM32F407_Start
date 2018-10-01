#include "htu21d.h"

/************************************************************************************/
/*   HTU21D(F) RH/T SENSOR IC                                                       */
/*   Digital Relative Humidity sensor with                                          */
/*   Temperature output                         																	  */
/************************************************************************************/

void htu21d_SoftReset(void){
	
	Start_i2c();
	Write_addr_i2c(0x40,0);
	Write_last_data_i2c(0xEF);
	Stop_i2c();
	
}
/************************************************************************************/
uint8_t CheckCRC(uint16_t message_from_sensor, uint8_t check_value_from_sensor){
	
	uint8_t i;
	uint32_t divsor;
	
  uint32_t remainder = (uint32_t)message_from_sensor << 8; //Pad with 8 bits because we have to add in the check value
  remainder |= check_value_from_sensor; //Add on the check value

  divsor = (uint32_t)SHIFTED_DIVISOR;

  for (i = 0 ; i < 16 ; i++) //Operate on only 16 positions of max 24. The remaining 8 are our remainder and should be zero when we're done.
  {
   
    if ( remainder & (uint32_t)1 << (23 - i) ) //Check if there is a one in the left position
      remainder ^= divsor;

    divsor >>= 1; //Rotate the divsor max 16 times so that we have 8 bits left of a remainder
  }

  return (uint8_t)remainder;
	
}
/************************************************************************************/
uint16_t htu21d_ReadValue(uint8_t cmd){
	
	uint16_t value = 0;
	uint8_t msb, lsb, checksum;
	
	Start_i2c();
	Write_addr_i2c(0x40,0);
	Write_last_data_i2c(cmd);
	
	Start_i2c();
	Write_addr_i2c(0x40,1);
	msb = Read_data_i2c();
  lsb = Read_data_i2c();
  checksum = Read_last_data_i2c();
	
  value = ((uint16_t) msb << 8) | (uint16_t) lsb;
	
	if (CheckCRC(value, checksum) != 0) return (ERROR_BAD_CRC); //Error out
	
	return value & 0xFFFC;

}
/************************************************************************************/
float ht21d_GetTemp(void){
	
	float temp = 0;
	uint16_t data_temp = htu21d_ReadValue(TRIGGER_TEMP_MEASURE_HOLD);
	
	temp = data_temp*(175.72 / 65536.0);
	temp = temp - (float)46.85;
	
	return (float)temp;
	
}
/************************************************************************************/
float ht21d_GetHumidity(void){
	
	float humidity = 0;
	uint16_t data_humidity = htu21d_ReadValue(TRIGGER_HUMD_MEASURE_HOLD);
	
	humidity = data_humidity*(125.0 / 65536.0);
	humidity = humidity - (float)6.0;
	
	return (float)humidity;
	
}
/************************************************************************************/


