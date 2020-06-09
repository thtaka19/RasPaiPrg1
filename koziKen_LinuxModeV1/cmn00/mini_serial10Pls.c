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
void	m_putCharI(int data);
#define	BUFSIZET	1024
char txbuf[BUFSIZET];
void enQueT(int);
int deQueT(void);
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
static	int     rcvSndI[3]={0,0,0};
//void uartHandler1()
void m_serialRcvInterrupt(void)   //  Changed  9Pls.c 2017 TT
{
	int	data;
	int	irq;
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	if(!(rpiAux->IRQ & 0x01)) {// (rpiAux->IRQ & 0x01)) == 1: mini UART interrupt
		m_serialPutChar('?');	// not mini UART interrupt ?
		m_serialPutChar('1');	// not mini UART interrupt ?
	}

	//if(rpiAux->MU_LSR_REG & 0x01) {

	irq = rpiAux->MU_IIR0_REG & 0x06 ;// TT
//putxval0((unsigned long) irq,4);// Debug
	if( irq== 0x04) {// Receve Inturrupt 
	  rcvSndI[0]++;// Rcv. Int counter
      m_serialPutChar('+');//Debug
      data =rpiAux->MU_IO_REG;
	  enQueR(data);
/////**   Try to get Data againCheck LSR Bit0
	  if((rpiAux->MU_LSR_REG & 0x01)==1) { // More Receive Data
        data =rpiAux->MU_IO_REG;
	    enQueR(data);	
	  }
	} else if ( irq == 0x02) { // Transmit empty Trans Interrupt
	   rcvSndI[1]++;//Send Empty counter
	   m_serialPutChar('-');//Debug
//       m_serialPutChar('x');//Debug
//  **************111 ++ **********
	   data = deQueT(); 
	   if((data)  >= 0) {  // Good data from Que
//			rpiAux->MU_IER0_REG =0x01;	//Disable Send Interrupt only Rcv TT
//	   } else { // Normal process
		  if((!(rpiAux->MU_LSR_REG &0x20) ==0 )  ) { //Transfer FIFO Empty
		  if(outpT == inpT) rpiAux->MU_IER0_REG =0x01;//Next Que is Empty,then Disable Send Interrupt only Rcv TT
//          m_serialPutChar('-');//Debug
		  rpiAux->MU_IO_REG=data ;  //data to Trancefer FIFO
	      rcvSndI[2]++;//Real Send counter
	      } // if LSR check End
			else m_serialPutChar('#');  //Error, Transfer FIFO Full

	   } //End if Good data 
//  **************** 222 ++ ********************
		if(outpT == inpT) rpiAux->MU_IER0_REG =0x01;//Disable Send Interrupt only Rcv TT
		else 		  rpiAux->MU_IER0_REG =0x03; //Int Send and Rcv mode
/***

***/
	} 
/***	
	else { // not  {receive(irq== 0x04) &&  Send(irq == 0x02)}
		m_serialPutChar('?');	// not mini UART interrupt !
		m_serialPutChar('2');	// 
	}
***/

}
void rcvSndIcnt(int * tmp1) {
 tmp1[0]=rcvSndI[0];
 tmp1[1]=rcvSndI[1];
 tmp1[2]=rcvSndI[2];
//		printf("mini_Uart !! Rcv Int = %d ; Snd emptyInt = %d\r\n",rcvSndI[0],rcvSndI[1]);
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
void enable_m_serial_Int(){
   struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;	
	// 
	rpiIRQController->Enable_IRQs_1 |= 0x01<<29;

	//*TIMER_CONTROL |= TMR_INT_EN;
}

void disable_m_serial_Int(){
   struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	//
rpiIRQController->Enable_IRQs_1 &= ~(0x01<<29);	

//	*TIMER_CONTROL &= ~TMR_INT_EN;
}
//void initializeUART1( void )
void m_serialInit(void)
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
	struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	unsigned int ra;

//	rpiAux->ENABLES=1;	//enable only miniUART, Not (SPI1, SPI2)
	rpiAux->ENABLES=0;	//disable all (miniUART,  (SPI1, SPI2))
	
///**  Disable is Better ??	rpiAux->ENABLES=0;
//	rpiAux->MU_IER_REG=0;	//disable interrupt
	rpiAux->MU_IER0_REG=0;	//disable interrupt
	rpiAux->MU_CNTL_REG=0;	//01 Receive Enable 02 Transmit Enalbe
	rpiAux->MU_LCR_REG=3;	//0x 8bit mode	3?	DLAB access = 0x80
	rpiAux->MU_MCR_REG=0;	//Modem Control 0
//	rpiAux->MU_IER_REG=0;   //2017 TT
	rpiAux->MU_IER0_REG=0;	
//	rpiAux->MU_IIR_REG=0xC6;	// 0xC6 FIFO Enable/Clear
	rpiAux->MU_IIR0_REG=0x06;	// 0xC6 FIFO 6:Clear	
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
	rpiAux->MU_CNTL_REG=3; //01 Receive Enable 02 Transmit Enalbe


	rpiIRQController->Enable_IRQs_1 = 0x01<<29;
//	rpiAux->MU_IER_REG=0x03;	//Enable Receive Interrupt 0x03
//	rpiAux->MU_IER0_REG=0x01;	//Enable 1:Receive Interruptrrupi 2:trancemit Interrupt 1+2= 0x03 TT
	rpiAux->MU_IER0_REG=0x00;	// No Interrupt
					//Enable Transmit Interrupt 0x01
///**  Enable here is Better ??	rpiAux->ENABLES=1;
	rpiAux->ENABLES=1;	//enable only miniUART, Not (SPI1, SPI2)
        inpT=txbuf;         outpT=txbuf;
	inpR=rvbuf;         outpR=rvbuf;
}
void m_serialInitIrcv(void)  // Same as mini_serial9AdI.c
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	m_serialInit();
	rpiAux->MU_IER0_REG=0x01;// Over write =0x01 ; Debug =0x03
				//Enable 01:Receive Interruptrrupi 02:trancemit Interrupt 1+2= 0x03 TT

   enable_m_serial_Int();// Enable IRQ29 Int					
}

void m_serialInitIsndrcv(void) // New function at mini_serial9APls.c
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	m_serialInit();
	rpiAux->MU_IER0_REG=0x03;// Over write Interrupt Receive and trans.
	//Enable 1:Receive Interruptrrupi 2:trancemit Interrupt 1+2= 0x03 TT
	enable_m_serial_Int();// Enable IRQ29 Int
}
void m_Serial_begin(int dmy) {
  m_serialInit();
}
//#ifdef	AARCH64

//void	m_putCharI(int data)	// put with Interrupt Transmit
void m_serialPutCharI(int data) // Changed 2017 TT 
{
int data1;
	struct rpiAux* rpiAux= RPI_AUX_BASE;	
/***
	if(data =='\n') {
		enQueT('\r');
	} else enQueT(data);
***/
	enQueT(data);	

	if((!(rpiAux->MU_LSR_REG &0x20) ==0 ) && (data1 =deQueT()) !=-1  ) {
		    rpiAux->MU_IO_REG=data1 ;
rcvSndI[2]++;// Debug 

	}
	  rpiAux->MU_IER0_REG=0x03;	//Enable Send And Receive Interrupt 0x03	TT	

}


void enQueT(int data){ // For Interrupt Send( Transfer) Changed at mini_serial9Pls.c
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

	  rpiAux->MU_IER0_REG=0x03;//Enable Send and Receive Interrupt
	  return;  
	}   
  
	*inpT = data;
	inpT = temp;
//m_serialPutChar('.');// Debug
	rpiAux->MU_IER0_REG=0x03;//Enable Send and Receive Interrupt 
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
//m_serialPutChar('*');// Debug
//m_serialPutChar(data);// Debug
	return data;
}
int datQueT(void) { 
	if(outpT == inpT) {// No data in the Que
		return 0;
	}
        else { if(outpT > inpT)  return (outpT - inpT);
		else 	         return (sizeof(txbuf) + outpT - inpT );
	     }
}


int m_serialGetCharI(void) { // For Interrupt Receive
//m_serialPutStr("m_serialGetCharI called \r\n");//Debug
     return deQueR() ;
}
void enQueR(int data){ // For Interrupt Receive
	struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	char	*temp =inpR;

//m_serialPutStr("enQueR called =");//Debug

	if(++temp >= rvbuf+sizeof(rvbuf)) {
		temp= rvbuf;
	}
 
	if(temp ==outpR) {   // 2017 TT
	  m_serialPutStr("\r\n Rcv Q (enQueR) over flow\r\n");
	  rpiAux->MU_IER0_REG |=0x01;	//Enable Receive Interrupt 0x03	
	  return;  
	}     
	*inpR = data;
	inpR = temp;

//	rpiAux->MU_IER_REG=0x03;	//Enable Receive Interrupt 0x03
	rpiAux->MU_IER0_REG |=0x01;	//Enable Receive Interrupt 0x03
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
//m_serialPutChar('#');// Debug
//m_serialPutChar(data);// Debug
	return data;

}


void	noOperation()
{
}

