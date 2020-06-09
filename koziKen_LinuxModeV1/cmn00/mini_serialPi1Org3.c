/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
#include "../cmn00/io10.h"

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
	struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	unsigned int ra;

	rpiAux->ENABLES=0;	//disable all (miniUART,  (SPI1, SPI2))

	rpiAux->MU_IER0_REG=0;	//disable interrupt
	rpiAux->MU_CNTL_REG=0;	//01 Receive Enable 02 Transmit Enalbe
	rpiAux->MU_LCR_REG=3;	//0x 8bit mode	3?	DLAB access = 0x80
	rpiAux->MU_MCR_REG=0;	//Modem Control 0

	rpiAux->MU_IER0_REG=0;	
	rpiAux->MU_IIR0_REG=0xC6;	// 0xC6 FIFO c:Enable/ 6:Clear
		//((250,000,000/115200)/8)-1 = 270
	rpiAux->MU_BAUD_REG=270;
	// Set mini_Serial GPIO14,GPIO15 pin   
        rpiGpio->GPFSEL1 &= ~(7 << (14-10)*3);   //12 GPIO14
        rpiGpio->GPFSEL1 |= (2 << (14-10)*3);   //12 GPIO14
        rpiGpio->GPFSEL1 &= ~(7 << (15-10)*3);   //15 GPIO15
        rpiGpio->GPFSEL1 |= (2 << (15-10)*3);   //15 GPIO15

	rpiGpio->GPPUD = 0;
	for(ra=0;ra<150;ra++) noOperation();
	rpiGpio->GPPUDCLK0 = ((1<<14)|(1<<15));
	for(ra=0;ra<150;ra++) noOperation();
	rpiGpio->GPPUDCLK0 = 0;	
	
	rpiAux->MU_CNTL_REG=3; //01 Receive Enable 02 Transmit Enalbe

	rpiIRQController->Enable_IRQs_1 |= 0x01<<29;

	rpiAux->MU_IER0_REG=0x00;	// No Interrupt

	rpiAux->ENABLES=1;	//enable only miniUART, Not (SPI1, SPI2)
}
//----------------------------------------------------------------------
void m_Serial_begin(int dmy) {
  m_serialInit();
}

void	noOperation()
{
}

