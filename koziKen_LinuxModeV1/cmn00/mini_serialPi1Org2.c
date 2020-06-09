/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
#include "../cmn00/io10.h"
//#include "printf.h"

void	setLowVector(void);		
void	writeVectorBaseRegister(int);
void	reverseLED(void);
void	noOperation (void);

void	m_serialPutChar(int);
void	m_putChar(int);

#define	BUFSIZET	1024
char txbuf[BUFSIZET];
void enQueT(int);
int deQueT();
char *volatile inpT=txbuf;
char *volatile outpT=txbuf;

#define	BUFSIZE	128
char rvbuf[BUFSIZE];
void enQueR(int);
int deQueR();
char *volatile inpR=rvbuf;
char *volatile outpR=rvbuf;

/////////////////////////////////////////////////////////////////////

extern volatile int timer;
//static	int     rcvSndI[3]={0,0,0};
//void uartHandler1()
void m_serialRcvInterrupt(void)
{
	int	data;
	int	irq;
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	if(!(rpiAux->IRQ & 0x01)) {// (rpiAux->IRQ & 0x01)) == 1: mini UART interrupt
		m_serialPutChar('?');	// not mini UART interrupt ?
		m_serialPutChar('1');	// not mini UART interrupt ?
	}

	//if(rpiAux->MU_LSR_REG & 0x01) {
//	irq = rpiAux->MU_IIR_REG & 0x06 ;//??? TT	
	irq = rpiAux->MU_IIR0_REG & 0x06 ;

	if( irq== 0x04) {// Receve Inturrupt
	
                m_serialPutChar('+');
                data =rpiAux->MU_IO_REG;
//		m_serialPutChar((char)data);
		enQueR(data);
//		m_putCharI(data) ;// PutChar with Trans Interrupt
		//rpiAux->MU_IO_REG=data;
	} else if ( irq == 0x02) {// Transmit empty
	
               m_serialPutChar('-');
		if((data = deQueT())  < 0) {	// Disable Transmit Interrupt
//			rpiAux->MU_IER_REG=0x01;	//Enable Receive Only(1)
			rpiAux->MU_IER0_REG=0x01;	//Enable Receive Only(1)???   0x02?? TT
		//	putChar1('&');	// not mini UART interrupt ?
		} else {
			//if(rpiAux->MU_LSR_REG &0x20){
			//if(rpiAux->MU_IIR_REG & 0x02) {
//		m_serialPutChar('&');
			rpiAux->MU_IO_REG=data;
//			rpiAux->MU_IER_REG=0x03;	//Enable R(1)&T(2)
			rpiAux->MU_IER0_REG=0x01;	//Enable R(1)&T(2) TT
		//	putChar1('?');	// not mini UART interrupt ?
		}
	} else {
		m_serialPutChar('?');	// not mini UART interrupt ?
		m_serialPutChar('2');	// not mini UART interrupt ?
	}
}

int m_serialGetChar( void )
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	while(!(rpiAux->MU_LSR_REG & 0x01)) {
	}
	return(rpiAux->MU_IO_REG & 0xFF);
}

//------------------------------------------------------------------------
void m_serialPutChar (int c )
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	if(c == '\n') m_serialPutChar('\r');
	while(!(rpiAux->MU_LSR_REG &0x20)){
	}
	rpiAux->MU_IO_REG=c;
}
//------------------------------------------------------------------------

void m_serialPutStr(char const *pOutputStr)
{
    char const *pChar;
    /* Send each character of the string. */
    for (pChar = pOutputStr ; *pChar != '\0'; pChar++)
        m_serialPutChar(*pChar);
} 

//void initializeUART1( void )
void m_serialInit(void)
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
	struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	unsigned int ra;

	rpiAux->ENABLES=1;	//enable miniUART
//	rpiAux->MU_IER_REG=0;	//disable interrupt
	rpiAux->MU_IER0_REG=0;	//disable interrupt
	rpiAux->MU_CNTL_REG=0;	//01 Receive Enable 03 Transmit Enalbe
	rpiAux->MU_LCR_REG=3;	//0x 8bit mode	3?	DLAB access = 0x80
	rpiAux->MU_MCR_REG=0;	//Modem Control 0
//	rpiAux->MU_IER_REG=0;   //2017 TT
	rpiAux->MU_IER0_REG=0;	
//	rpiAux->MU_IIR_REG=0xC6;	// 0xC6 FIFO Enable/Clear	
	rpiAux->MU_IIR0_REG=0xC6;	// 0xC6 FIFO c:Enable/ 6:Clear
		//((250,000,000/115200)/8)-1 = 270
	rpiAux->MU_BAUD_REG=270;

        rpiGpio->GPFSEL1 &= ~(7 << (14-10)*3);   //12 GPIO14
        rpiGpio->GPFSEL1 |= (2 << (14-10)*3);   //12 GPIO14
        rpiGpio->GPFSEL1 &= ~(7 << (15-10)*3);   //15 GPIO15
        rpiGpio->GPFSEL1 |= (2 << (15-10)*3);   //15 GPIO15

	rpiGpio->GPPUD = 0;
	for(ra=0;ra<150;ra++) noOperation();
	rpiGpio->GPPUDCLK0 = ((1<<14)|(1<<15));
	for(ra=0;ra<150;ra++) noOperation();
	rpiGpio->GPPUDCLK0 = 0;	
	rpiAux->MU_CNTL_REG=3; //01 Receive Enable 03 Transmit Enalbe


	rpiIRQController->Enable_IRQs_1 = 0x01<<29;
//	rpiAux->MU_IER_REG=0x03;	//Enable Receive Interrupt 0x03
//	rpiAux->MU_IER0_REG=0x01;	//Enable 2:Receive Interruptrrupi 1:trancemit Interrupt 1+2= 0x03 TT
	rpiAux->MU_IER0_REG=0x00;	// No Interrupt
					//Enable Transmit Interrupt 0x01

        inpT=txbuf;         outpT=txbuf;
	inpR=rvbuf;         outpR=rvbuf;
}

void m_Serial_begin(int dmy) {
  m_serialInit();
}
//#ifdef	AARCH64
void	m_putCharI(int data)	// put with Interrupt Transmit
{	
	if(data =='\n') {
		m_putCharI('\r');
	}
	enQueT(data);
}
//#else

//#endif

void enQueT(int data){ // For Interrupt Send( Transfer)
	char	*temp ;
	struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	struct rpiAux* rpiAux= RPI_AUX_BASE;
 	rpiAux->MU_IER0_REG=0x00;// mini_UART Interrupt Disable
	temp =inpT;
	if(++temp >= txbuf+sizeof(txbuf)) {
		temp= txbuf;
	}

	if(temp ==outpT) {   // 2017 TT
	  m_serialPutStr("\r\n Send Q (enQueT) over flow\r\n");
	  rpiAux->MU_IER0_REG=0x01;	//Enable Receive Interrupt 0x03	TT
	  return;  
	}   
  
	*inpT = data;
	inpT = temp;

//	rpiAux->MU_IER_REG=0x03;	//Enable Receive Interrupt 0x03
	rpiAux->MU_IER0_REG=0x01;	//Enable Receive Interrupt 0x03 TT
}

int	deQueT() { // For Interrupt Send( Transfer)
	int data;
 
	if(outpT == inpT) {
		data =  -1;
	} else {
		data = *outpT;
		if(++outpT >= txbuf+sizeof(txbuf)) {
			outpT= txbuf;
		}
	}
	return data;
}

int  m_getCharI(void) { // For Interrupt Receive
     return deQueR() ;
}
void enQueR(int data){ // For Interrupt Receive
	struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	char	*temp =inpR;
	if(++temp >= rvbuf+sizeof(rvbuf)) {
		temp= rvbuf;
	}
 
	if(temp ==outpR) {   // 2017 TT
	  m_serialPutStr("\r\n Rcv Q (enQueR) over flow\r\n");
	  rpiAux->MU_IER0_REG=0x01;	//Enable Receive Interrupt 0x03	
	  return;  
	}     
	*inpR = data;
	inpR = temp;

//	rpiAux->MU_IER_REG=0x03;	//Enable Receive Interrupt 0x03
	rpiAux->MU_IER0_REG=0x01;	//Enable Receive Interrupt 0x03
}

int	deQueR(void) { // For Interrupt Receive
	int data;

	if(outpR == inpR) {
		data =  -1;
	} else {
		data = *outpR;
		if(++outpR >= rvbuf+sizeof(rvbuf)) {
			outpR= rvbuf;
		}
	}
	return data;
}

void    m_serialGetStr(char *s,int len){
	int i=1;
	int c;
	do{
		c = m_serialGetChar();
		if(c == -1)
			return (void *)0;
		*s = c;
		s++;
		i++;
	
	}while(i < len && c != '\n' && c != '\r'); // 2017 TT
	*s = '\0';
	return ;
}
void	noOperation()
{
}

