#include "ADT7310.h"
void delay(int);

void adt7310_initialize(void){
	// software reset
	SPI0_transfer(0xFF);
	SPI0_transfer(0xFF);
	SPI0_transfer(0xFF);
	SPI0_transfer(0xFF);
	delay(50);
	// Configuretion Set Register
	// Send Command Byte 
	// Resister address=0x01, Write mode 
	SPI0_transfer(ADT7310_CMD_ADDR_CONFIG | ADT7310_CMD_WRITE);
	// Set Configuretion resister
	// Resolution=16bit, Oparation mode=standard
	SPI0_transfer(0x80);
}

float adt7310_getTemperature(int mode){
	static int isConrinuous = 0;
	uint32_t	rawtemp;
	float		calced_temp;

	switch(mode){
		// case ADT7310_MODE_ONESHOT:
		// 	break;
		// case ADT7310_MODE_1SPS:
		// 	break;
		case ADT7310_MODE_CONRINUOUS:
			if(!isConrinuous){
				// Send Command Byte
				// Resister address=0x02, Read mode, Conrinuousモード
				SPI0_transfer(ADT7310_CMD_ADDR_TEMP | ADT7310_CMD_READ | ADT7310_CMD_CONRINUOUS);
			}
			isConrinuous = 1;
			// receive upper 8bits
			rawtemp = SPI0_transfer(0);
			rawtemp = rawtemp << 8;
			// receive lower 8bits
			rawtemp |= SPI0_transfer(0);
			break;
		default:
			if(isConrinuous){
				// clear Conrinuous mode
				// Resister address=0x02, Read mode
				SPI0_transfer(ADT7310_CMD_ADDR_TEMP | ADT7310_CMD_READ);
			}
			return 0.0;
	}

	// Temperature calculation
	if(rawtemp & 0x8000){
		//if MSB==1 , negative
		calced_temp = (rawtemp - 32768) / 128.0;
	}
	else{
		//if MSB==0 positive
		calced_temp = rawtemp / 128.0;
	}
	return calced_temp;
}
