#include "rpi_lib/rpi.h"
#include <stdio.h>
#include <stdint.h>
//DEbug
#include "AQM0802.h"

#define BSC1_BASE	(0x00804000)
#define BSC1_C		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x00))
#define BSC1_S		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x04))
#define BSC1_DLEN	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x08))
#define BSC1_A		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x0C))
#define BSC1_FIFO	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x10))
#define BSC1_DIV	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x14))
#define BSC1_DEL	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x18))
#define BSC1_CLKT	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x1C))

// I2C(BSC) Concrol MASK(use OR MASK)
#define BSC_C_I2CEN_EN		((vu32_t)0x01 << 15)
#define BSC_C_ST_EN			((vu32_t)0x01 << 7)
#define BSC_C_CLEAR_ALL		((vu32_t)0x03 << 4)
#define BSC_C_READ_READ		((vu32_t)0x01)

// I2C(BSC) Status MASK
#define BSC_S_CLKT			((vu32_t)0x01 << 9)
#define BSC_S_ERR			((vu32_t)0x01 << 8)
#define BSC_S_RXF			((vu32_t)0x01 << 7)
#define BSC_S_TXE			((vu32_t)0x01 << 6)
#define BSC_S_RXD			((vu32_t)0x01 << 5)
#define BSC_S_TXD			((vu32_t)0x01 << 4)
#define BSC_S_RXR			((vu32_t)0x01 << 3)
#define BSC_S_TXW			((vu32_t)0x01 << 2)
#define BSC_S_DONE			((vu32_t)0x01 << 1)
#define BSC_S_TA			((vu32_t)0x01 << 0)
/***
// buffer
volatile uint8_t txBuffer[BUFFER_LENGTH];
volatile uint32_t txBufferIndex;
volatile uint32_t txBufferLength;
volatile uint8_t rxBuffer[BUFFER_LENGTH];
volatile uint32_t rxBufferIndex;
volatile uint32_t rxBufferLength;
***/
// LCD
//#define	AQM0802_ADDR	(0x7C)

void aqm0802_initX(void){
	uint8_t aqm0802_initcmd_1st[18] = {
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_CMD_FUNCTION_BASE | AQM0802_CMD_FUNCTION_DL_EN | AQM0802_CMD_FUNCTION_N_EN,	// Function Set(0x38)
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_CMD_FUNCTION_BASE | AQM0802_CMD_FUNCTION_DL_EN | AQM0802_CMD_FUNCTION_N_EN | AQM0802_CMD_FUNCTION_IS_EN, // Function Set(0x39)
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_OSC_FREQ_BASE | AQM0802_OSC_FREQ_F2_EN,	// Internal OSC frequency(0x14)
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_CONTRAST_BASE,	// Contrast Set(0x70)
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_POW_ICON_CONTRAST_BASE | AQM0802_POW_ICON_CONTRAST_BON_EN | AQM0802_POW_ICON_CONTRAST_C5_EN, // Power/ICON/Contrast(0x56)
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_FOLLOWER_CTRL_BASE | AQM0802_FOLLOWER_CTRL_FON_EN | AQM0802_FOLLOWER_CTRL_RAB2_EN // Follower control(0x6C)
	};
	uint8_t aqm0802_initcmd_2nd[6] = {
		AQM0802_CTRL_Co,	// Co=1,RS=0
		AQM0802_CMD_FUNCTION_BASE | AQM0802_CMD_FUNCTION_DL_EN | AQM0802_CMD_FUNCTION_N_EN,	// Function Set(0x38)
		AQM0802_CTRL_Co,// Co=1,RS=0
		AQM0802_CMD_DISPLAY_CTRL_BASE | AQM0802_CMD_DISPLAY_CTRL_D,	// Display ON （0x0C）
		AQM0802_CTRL_Co,// Co=1,RS=0
		AQM0802_CMD_CLEAR_DISPLAY	// Display Clear(0x01)
	};

	// LCD init start
//	Wire1_beginTransmission(AQM0802_ADDR);
//		txBufferIndex = 0;
//	txBufferLength = 0;

	// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
	
////////////	
//	Wire1_writeData(aqm0802_initcmd_1st, 18);
//	Wire1_endTransmission(TRUE);
	*BSC1_C |= BSC_C_CLEAR_ALL;
	// 送信データ長設定
	*BSC1_DLEN = 2*9; 

	// set data
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x38; // Function Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x39; // Function Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x14; // Internal OSC frequency
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x70; // Contrast Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x56; // Power/ICON/Contrast
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x6C; // Follower control

	// transfer start
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;
	delay(1250);

//	Wire1_beginTransmission(AQM0802_ADDR);
//			txBufferIndex = 0;
//	txBufferLength = 0;

	// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
//////////	
	
//	Wire1_writeData(aqm0802_initcmd_2nd, 6);
//	Wire1_endTransmission(TRUE);
		delay(1250);

	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x38; // Function Set
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x0C; // Display ON/OFF 
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x01; // Display Clear
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;
	delay(1250);
	// 転送終了待ち
	// 1 = Transfer complete
	while(!(*BSC1_S & BSC_S_DONE));
	// transfer end
	// LCD init end
	
	// LCD init end
}
void aqm0802_initY(void){
	
	// LCD init start
	// 送信準備
	// Clear Status
	*BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
	// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
	
	// Buffer clear
	*BSC1_C |= BSC_C_CLEAR_ALL;
	// 送信データ長設定
	*BSC1_DLEN = 2*9; 

	// set data
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x38; // Function Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x39; // Function Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x14; // Internal OSC frequency
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x70; // Contrast Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x56; // Power/ICON/Contrast
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x6C; // Follower control

	// transfer start
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;

	delay(250);
		// 転送終了待ち
	// 1 = Transfer complete
	while(!(*BSC1_S & BSC_S_DONE));
	// transfer end
//	delay(1250);
		// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
//////////	
	
	
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x38; // Function Set
//	delay(50);	
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x0C; // Display ON/OFF
//	delay(250);	
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x01; // Display Clear
//	delay(250);
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;	
	delay(250);
	// 転送終了待ち
	// 1 = Transfer complete
	while(!(*BSC1_S & BSC_S_DONE));
	// transfer end
	// LCD init end
	
	
}
int main(void){
	uint8_t hello[] = "X123456";
	uint8_t world[] = "Wld99";
	rpi_init();

//	Wire1_begin();

	// I2C init
	// port setting
	pinMode(2, ALT0); // SDA
	pinMode(3, ALT0); // SCL
	
	
	// set I2C clock divider
	// SCL = 150[MHz] / 32768 = 4.58[kHz]
	*BSC1_DIV = 0;
	

//	aqm0802_initX();
//	aqm0802_initY();





	// LCD init start
	// 送信準備
	// Clear Status
	*BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
	// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
	
	// Buffer clear
	*BSC1_C |= BSC_C_CLEAR_ALL;
	// 送信データ長設定
	*BSC1_DLEN = 2*9; 

	// set data
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x38; // Function Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x39; // Function Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x14; // Internal OSC frequency
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x70; // Contrast Set
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x56; // Power/ICON/Contrast
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x6C; // Follower control

	// transfer start
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;

	delay(250);
	while(!(*BSC1_S & BSC_S_DONE));
	// transfer end
//	Add 2019 TT
		// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
/////Add 2019 TT End/////	
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));// 2019 Del
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x38; // Function Set
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x0C; // Display ON/OFF 
	// 送信バッファが空いているか確認
//	while(!(*BSC1_S & BSC_S_TXW));
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x01; // Display Clear
	// transfer start
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;

	delay(250);
	// 転送終了待ち
	// 1 = Transfer complete
	while(!(*BSC1_S & BSC_S_DONE));
	// transfer end
	// LCD init end
	
	delay(200);
//	aqm0802_print_line(hello, 1);	
//while(!(*BSC1_S & BSC_S_DONE)){  ; } // TT 2019
//	delay(300);
//Wire1_beginTransmission(AQM0802_ADDR);
//			txBufferIndex = 0;
//	txBufferLength = 0;

	// slave address
//	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
//	*BSC1_C &= ~BSC_C_READ_READ;

///////	
	// print "Hello"
	// 送信準備
	// Clear Status
	*BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
	// slave address
	*BSC1_A = AQM0802_ADDR >> 1;
	// Write mode
	*BSC1_C &= ~BSC_C_READ_READ;
	// Buffer clear
	*BSC1_C |= BSC_C_CLEAR_ALL;
	// 送信データ長設定
	*BSC1_DLEN = 8; 

	// send data
	*BSC1_FIFO = 0x80; // Co=1,RS=0
	*BSC1_FIFO = 0x80 | 0x00; //set DDRAM address
	*BSC1_FIFO = 0x40; // Co=0,RS=1
	*BSC1_FIFO = 'H';
	*BSC1_FIFO = 'e';
	*BSC1_FIFO = 'l';
	*BSC1_FIFO = 'l';
	*BSC1_FIFO = 'o';

	// transfer start
	*BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;

	// 転送終了待ち
	// 1 = Transfer complete
	while(!(*BSC1_S & BSC_S_DONE));
	// transfer end
		delay(1200);
	aqm0802_print_line(world, 2);
	// I2C通信終了
	*BSC1_C &= ~BSC_C_I2CEN_EN;
 	delay(1200);
//	aqm0802_print_line(hello, 1);
//	aqm0802_print_line(world, 2);
	return 0;
}
