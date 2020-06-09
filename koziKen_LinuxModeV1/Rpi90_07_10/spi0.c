#include "../cmn00/rpi_spi0.h"
#include "../cmn00/io10.h"
#define GPIO_ALT0     0x4
gpio_configure(int, int);// pin,mode
// configure value
volatile int SPI0_BEGIN = 0;
volatile int SS_PORT = SPI_SS_OTHER;
volatile int BIT_ORDER = SPI_BIT_ORDER_MSBFIRST;
static	struct rpiSpi0* rpiSpi0= SPI0_BASE;

void SPI0_begin(int ss_port){
	vu32_t *res0,*res1;

	// pin setting
	// MISO
	//pinMode( 9, ALT0);
	// MOSI
	//pinMode(10, ALT0);
	// SCLK
	//pinMode(11, ALT0);
	/***
	res0 = GPFSEL0;
	res1 = GPFSEL1;
//	*res0 |= GPFSEL_MASK_ALT0(8);
	*res0 |= GPFSEL_MASK_ALT0(9);
	*res1 |= GPFSEL_MASK_ALT0(10);
	*res1 |= GPFSEL_MASK_ALT0(11);
***/
gpio_configure(9, GPIO_ALT0);
gpio_configure(10, GPIO_ALT0);
gpio_configure(11, GPIO_ALT0);
	// SS
	SS_PORT = ss_port;
	switch(ss_port){
		case SPI_SS_CS0:
			//pinMode( SPI_SS_PORT_CS0, SPI_SS_MODE_CS0);// 8,ALT0
			//*res0 |= GPFSEL_MASK_ALT0(8);
			gpio_configure(8, GPIO_ALT0);
			break;
		case SPI_SS_CS1:
			//pinMode( SPI_SS_PORT_CS1, SPI_SS_MODE_CS1);// 7,ALT0
			//*res0 |= GPFSEL_MASK_ALT0(7);
			gpio_configure(7, GPIO_ALT0);
			break;
		// case SPI_SS_CS2:
		// 	pinMode( SPI_SS_PORT_CS2, SPI_SS_MODE_CS2);
		// 	break;
		default:
			// other
			;
	}
rpiSpi0= spi_init( );
	// SPI0 configure initialize
	rpiSpi0->SPI0_CS = 0;

	// CS setting
	switch(ss_port){
		case SPI_SS_CS0:
			rpiSpi0->SPI0_CS |= SPI0_CS_CS_CS0;
			break;
		case SPI_SS_CS1:
			rpiSpi0->SPI0_CS |= SPI0_CS_CS_CS1;
			break;
		// case SPI_SS_CS2:
		// 	*SPI0_CS |= SPI0_CS_CSPOL2_HIGH | SPI0_CS_CS_CS2;
		// 	break;
		default:
			;
	}
	// *SPI0_CS |= SPI0_CS_CSPOL_LOW;

	// FIFO all clear
	rpiSpi0->SPI0_CS |= SPI0_CS_CLEAR_ALL;

	// Clock setting
	// 3.81[kHz](default)
	rpiSpi0->SPI0_CLK = 0;

	// initialize ok
	SPI0_BEGIN = 1;
}


void SPI0_end(void){
	// not initialize
	SPI0_BEGIN = 0;
}

void SPI0_setBitOrder(int order){
	BIT_ORDER = order;
}

void SPI0_setClockDivider(uint16_t divider){
	int i;
	// Clock setting
	// divide value check
	// The divisor must be a power of 2
	for(i=1;i < 0x10000;i << 1){
		if(divider == i){
			break;
		}
	}
	if(divider != 0 && i == 0x10000){
		// error
		return;
	}

	// SCLK = CoreClock / CDIV(divider)
	// CoreClock default is 250MHz
	rpiSpi0->SPI0_CLK = divider;

	return;
}


void SPI0_setDataMode(uint8_t mode){
	switch(mode){
		case SPI_MODE0:
			// MODE00
			rpiSpi0->SPI0_CS |= SPI0_CS_MODE_00;
			break;
		case SPI_MODE1:
			// MODE01
			rpiSpi0->SPI0_CS |= SPI0_CS_MODE_01;
			break;
		case SPI_MODE2:
			// MODE00
			rpiSpi0->SPI0_CS |= SPI0_CS_MODE_10;
			break;
		case SPI_MODE3:
			// MODE01
			rpiSpi0->SPI0_CS |= SPI0_CS_MODE_11;
			break;
		default:
			// error
			;
			}
	return;
}

uint8_t changeBitOrder(uint8_t byte){
	uint8_t cbyte = 0;
	int i;

	for(i=0;i<8;i++){
		if(byte & (0x01 << i)){
			cbyte |= 0x80 >> i;
		}
	}
	return cbyte;
}

uint8_t SPI0_transfer(uint8_t value){
	uint8_t read;
	uint8_t write;

	if(!SPI0_BEGIN){
		// not initialize
		return 0;
	}

	// transfer start（TA = 1）
	rpiSpi0->SPI0_CS |= SPI0_CS_TA_ACTIVE;

	// change bit order
	write = (BIT_ORDER == SPI_BIT_ORDER_MSBFIRST) ? value : changeBitOrder(value);

	// FIFO all clear
	rpiSpi0->SPI0_CS |= SPI0_CS_CLEAR_ALL;

	// Wat for trancemission（wait TXD）
	while(!(rpiSpi0->SPI0_CS & SPI0_CS_TXD_MASK));
	// send value
	rpiSpi0->SPI0_FIFO = write;

	// Wait receive
	while(!(rpiSpi0->SPI0_CS & SPI0_CS_RXD_MASK));
	// read value
	read = rpiSpi0->SPI0_FIFO;

	// 1 = Transfer is complete. Cleared by writing
	while(!(rpiSpi0->SPI0_CS & SPI0_CS_DONE_MASK));

	// change bit order
	read = (BIT_ORDER == SPI_BIT_ORDER_MSBFIRST) ? read : changeBitOrder(read);

	// transfer end
	rpiSpi0->SPI0_CS &= ~SPI0_CS_TA_ACTIVE;

	return read;
}
