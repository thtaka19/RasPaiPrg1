#include "ADT7310.h"
void delay(int);

void adt7310_initialize(void){
	// software reset
	SPI0_transfer(0xFF);
	SPI0_transfer(0xFF);
	SPI0_transfer(0xFF);
	SPI0_transfer(0xFF);
	delay(50);

	SPI0_transfer(ADT7310_CMD_ADDR_CONFIG | ADT7310_CMD_WRITE);

	SPI0_transfer(0x80);
}

float adt7310_getTemperature(int mode){
	static int isConrinuous = 0;
	uint32_t	rawtemp;
	float		calced_temp;

	switch(mode){

		case ADT7310_MODE_CONRINUOUS:
			if(!isConrinuous){

				SPI0_transfer(ADT7310_CMD_ADDR_TEMP | ADT7310_CMD_READ | ADT7310_CMD_CONRINUOUS);
			}
			isConrinuous = 1;
	
			rawtemp = SPI0_transfer(0);
			rawtemp = rawtemp << 8;
	
			rawtemp |= SPI0_transfer(0);
			break;
		default:
			if(isConrinuous){

				SPI0_transfer(ADT7310_CMD_ADDR_TEMP | ADT7310_CMD_READ);
			}
			return 0.0;
	}


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
