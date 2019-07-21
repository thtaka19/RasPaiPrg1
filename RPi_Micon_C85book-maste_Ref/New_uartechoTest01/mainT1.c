#include "rpi_lib/rpi.h"

// UART peripheral
/***
#define UART0_BASE		0x00201000
#define UART0_DR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x00))
#define UART0_FR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x18))
#define UART0_IBRD		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x24))
#define UART0_FBRD		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x28))
#define UART0_LCRH		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x2c))
#define UART0_CR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x30))
***/

#define PHY_PERI_ADDR(x) (0x20000000 + (x))  //for Pi Zero , Pi1 or
// #define PHY_PERI_ADDR(x) (0x3F000000 + (x))  //for Pi2 , Pi3 
#define	RPI_IO_BASE  PHY_PERI_ADDR(0x00000000)
#define RPI_GPIO_BASE	(struct rpiGpio *)(RPI_IO_BASE |0x00200000) 

struct rpiAux {
	volatile unsigned int	IRQ;		/*	5000	*/
	volatile unsigned int	ENABLES;	/*	5004	*/
	volatile unsigned int	NO0[16-2];	/*		*/
	volatile unsigned int	MU_IO_REG;	/*	5040	*/
	volatile unsigned int	MU_IER_REG;	/*	5044	*/
//	volatile unsigned int	MU_IER0_REG;	/*	5044	*/ // 2017 TT IIR_REG
	volatile unsigned int	MU_IIR_REG;	/*	5048	*/
//	volatile unsigned int	MU_IIR0_REG;	/*	5048	*/ // 2017 TT IER_REG
	volatile unsigned int	MU_LCR_REG;	/*	504C	*/
	volatile unsigned int	MU_MCR_REG;	/*	5050	*/
	volatile unsigned int	MU_LSR_REG;	/*	5054	*/
	volatile unsigned int	MU_MSR_REG;	/*	5058	*/
	volatile unsigned int	MU_SCRATCH;	/*	505C	*/
	volatile unsigned int	MU_CNTL_REG;	/*	5060	*/
	volatile unsigned int	MU_STAT_REG;	/*	5064	*/
	volatile unsigned int	MU_BAUD_REG;	/*	5068	*/
	volatile unsigned int	NO1[8-3];	/*		*/
	volatile unsigned int	SPI0_CNTL0_REG;	/*	5080	*/
	volatile unsigned int	SPI0_CNTL1_REG;	/*	5084	*/
	volatile unsigned int	SPI0_STAT_REG;	/*	5088	*/
	volatile unsigned int	SPI0_IO_REG;	/*	5090	*/
	volatile unsigned int	SPI0_PEEK_REG;	/*	5094	*/
	volatile unsigned int	NO2[16-5];	/*		*/
	volatile unsigned int	SPI1_CNTL0_REG;	/*	50C0	*/
	volatile unsigned int	SPI1_CNTL1_REG;	/*	50C4	*/
	volatile unsigned int	SPI1_STAT_REG;	/*	50C8	*/
	volatile unsigned int	SPI1_IO_REG;	/*	50D0	*/
	volatile unsigned int	SPI1_PEEK_REG;	/*	50D4	*/
};
#define RPI_AUX_BASE	(struct rpiAux *)(RPI_IO_BASE |0x00215000)
int main(void){
	rpi_init();

	/****	初期設定開始	***/
	// UART無効化
//	*UART0_CR 	= 0;
	
	//ポートの設定
	pinMode(14,INPUT_PULLDOWN);
	pinMode(15,INPUT_PULLDOWN);
	pinMode(14,ALT5);//mini_Uart
	pinMode(15,ALT5);

	/***
	// ボーレートの設定
	//(3000000 / (16 * 115200) = 1.627
	//(0.627*64)+0.5 = 40
	// IBRD 1 FBRD 40
	*UART0_IBRD = 1;
	*UART0_FBRD = 40;
	
	// LCRH
	// stick parity dis, 8bit, FIFO en, two stop bit no, odd parity, parity dis, break no
	*UART0_LCRH = 0x70;

	// CR
	// CTS dis, RTS dis, OUT1-2=0, RTS dis, DTR dis, RXE en, TXE en, loop back dis, SIRLP=0, SIREN=0, UARTEN en
	*UART0_CR 	= 0x0301;
	***/
		struct rpiAux* rpiAux= RPI_AUX_BASE;
				// Set mini_Serial Register

	rpiAux->ENABLES=0;	//disable all (miniUART,  (SPI1, SPI2))
	rpiAux->MU_IER_REG=0;	//disable interrupt
	rpiAux->MU_CNTL_REG=0;	//01 Receive Enable 02 Transmit Enalbe
	
	rpiAux->MU_LCR_REG=3;	//0x 8bit mode 0x01	And
	rpiAux->MU_MCR_REG=0;	//Modem Control 0

	rpiAux->MU_IIR_REG=0xC6;	// 0xC6 FIFO c:Enable/ 6:Clear
		//((250,000,000/115200)/8)-1 = 270
	rpiAux->MU_BAUD_REG=270;	
	rpiAux->MU_CNTL_REG=3; //01 Receive Enable 02 Transmit Enalbe


//	rpiAux->MU_IER_REG=0x00;	// No Interrupt
	rpiAux->ENABLES=1;	//enable only miniUART, Not (SPI1, SPI2)
	
	//	初期設定終了	**


	int c;
	while(1){
		// 受信FIFOが空でなくなるのを待つ
//		while (*UART0_FR & (1 << 4));
		// 受信データを読み込む
//		c = *UART0_DR;
	while(!(rpiAux->MU_LSR_REG & 0x01)) {;}
	c =rpiAux->MU_IO_REG & 0xFF;	
		
		// 読み込んだ文字を送り返す
		

	while(!(rpiAux->MU_LSR_REG &0x20)){;}
	rpiAux->MU_IO_REG=c;
//		*UART0_DR = 0x00ff & c;
	}
	
	return 0;
}