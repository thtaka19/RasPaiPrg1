/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
//#include "../cmn00/io10.h"
#define PHY_PERI_ADDR(x) (0x20000000 + (x))  //for Pi Zero , Pi1 or
// #define PHY_PERI_ADDR(x) (0x3F000000 + (x))  //for Pi2 , Pi3 
#define	RPI_IO_BASE  PHY_PERI_ADDR(0x00000000)
#define RPI_GPIO_BASE	(struct rpiGpio *)(RPI_IO_BASE |0x00200000) 
//#define RPI_INTERRUPT_CONTROLLER_BASE	(RPI_IO_BASE | 0x0000B200)
struct rpiAux {
	volatile unsigned int	IRQ;		/*	5000	*/
	volatile unsigned int	ENABLES;	/*	5004	*/
	volatile unsigned int	NO0[16-2];	/*		*/
	volatile unsigned int	MU_IO_REG;	/*	5040	*/
//	volatile unsigned int	MU_IER_REG;	/*	5044	*/
	volatile unsigned int	MU_IER0_REG;	/*	5044	*/ // 2017 TT IIR_REG
//	volatile unsigned int	MU_IIR_REG;	/*	5048	*/
	volatile unsigned int	MU_IIR0_REG;	/*	5048	*/ // 2017 TT IER_REG
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
 struct rpiGpio{
	volatile unsigned int    GPFSEL[6];

    volatile const unsigned int    Reserved0;
volatile unsigned int    GPSET[2];	

    volatile const unsigned int    Reserved1;
	volatile unsigned int    GPCLR[2];

    volatile const unsigned int    Reserved2;
	    volatile unsigned int    GPLEV[2];

    volatile const unsigned int    Reserved3;
    volatile unsigned int    GPEDS0;
    volatile unsigned int    GPEDS1;
    volatile const unsigned int    Reserved4;
    volatile unsigned int    GPREN0;
    volatile unsigned int    GPREN1;
    volatile const unsigned int    Reserved5;
    volatile unsigned int    GPFEN0;
    volatile unsigned int    GPFEN1;
    volatile const unsigned int    Reserved6;
    volatile unsigned int    GPHEN0;
    volatile unsigned int    GPHEN1;
    volatile const unsigned int    Reserved7;
    volatile unsigned int    GPLEN0;
    volatile unsigned int    GPLEN1;
    volatile const unsigned int    Reserved8;
    volatile unsigned int    GPAREN0;
    volatile unsigned int    GPAREN1;
    volatile const unsigned int    Reserved9;
    volatile unsigned int    GPAFEN0;
    volatile unsigned int    GPAFEN1;
    volatile const unsigned int    Reserved10;
    volatile unsigned int    GPPUD;
	volatile unsigned int    GPPUDCLK[2];	

    volatile const unsigned int    Reserved11;
};

void	noOperation (void);

void	m_serialPutChar(int);
void	m_putChar(int);

int m_serialGetChar( void )
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	while(!(rpiAux->MU_LSR_REG & 0x01)) {
	}
	return(rpiAux->MU_IO_REG & 0xFF);
}

//-------------------------------------------------------------------
void m_serialPutChar (int c )
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	if(c == '\n') m_serialPutChar('\r');
	while(!(rpiAux->MU_LSR_REG &0x20)){
	}
	rpiAux->MU_IO_REG=c;
}
//-------------------------------------------------------------------

void m_serialPutStr(char const *pOutputStr)
{
    char const *pChar;
    /* Send each character of the string. */
    for (pChar = pOutputStr ; *pChar != '\0'; pChar++)
        m_serialPutChar(*pChar);
} 
//-------------------------------------------------------------------
void m_serialInit(void)
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
//	struct rpiIrqController *rpiIRQController = 
//		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	unsigned int ra;
	
		// Set mini_Serial mode GPIO14,GPIO15 pin  
	rpiGpio->GPPUD = 0;// Pull_UP/Pull_Down Clear.
	for(ra=0;ra<150;ra++) noOperation();
	rpiGpio->GPPUDCLK[0] = ((1<<14)|(1<<15));
	for(ra=0;ra<150;ra++) noOperation();
	rpiGpio->GPPUDCLK[0] = 0;	
		
        rpiGpio->GPFSEL[1] &= ~(7 << (14-10)*3);   //12 GPIO14 Clear
        rpiGpio->GPFSEL[1] |= (2 << (14-10)*3);   //12 GPIO14  Set ALT5
        rpiGpio->GPFSEL[1] &= ~(7 << (15-10)*3);   //15 GPIO15
        rpiGpio->GPFSEL[1] |= (2 << (15-10)*3);   //15 GPIO15  Set ALT5

		// Set mini_Serial Register

	rpiAux->ENABLES=0;	//disable all (miniUART,  (SPI1, SPI2))
	rpiAux->MU_IER0_REG=0;	//disable interrupt
	rpiAux->MU_CNTL_REG=0;	//01 Receive Enable 02 Transmit Enalbe
	
	rpiAux->MU_LCR_REG=3;	//0x 8bit mode 0x01	And
	rpiAux->MU_MCR_REG=0;	//Modem Control 0
//	rpiAux->MU_IER0_REG=0;	
	rpiAux->MU_IIR0_REG=0xC6;	// 0xC6 FIFO c:Enable/ 6:Clear
		//((250,000,000/115200)/8)-1 = 270
	rpiAux->MU_BAUD_REG=270;	
	rpiAux->MU_CNTL_REG=3; //01 Receive Enable 02 Transmit Enalbe

//	rpiIRQController->Enable_IRQs_1 = 0x01<<29
//	rpiAux->MU_IER0_REG=0x00;	// No Interrupt
	rpiAux->ENABLES=1;	//enable only miniUART, Not (SPI1, SPI2)
}
//----------------------------------------------------------------------
void m_Serial_begin(int dmy) {
  m_serialInit();
}

void	noOperation()
{
		// nop
		asm("mov r0,r0");
}

