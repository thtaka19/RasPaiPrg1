/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
#include "io10.h"

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

extern volatile int timer;
static	int     rcvSndI[3]={0,0,0};

void m_serialRcvInterrupt(void)   //  Changed  9Pls.c 2017 TT
{
	int	data;
	int	irq;
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	if(!(rpiAux->IRQ & 0x01)) {// (rpiAux->IRQ & 0x01)) == 1: mini UART interrupt
		m_serialPutChar('?');	// not mini UART interrupt ?
		m_serialPutChar('1');	// not mini UART interrupt ?
	}

	irq = rpiAux->MU_IIR0_REG & 0x06 ;// TT
	//putxval0((unsigned long) irq,4);// Debug
	if( irq== 0x04) {// Receve Inturrupt 
	  rcvSndI[0]++;// Rcv. Int counter up
      m_serialPutChar('+');//Debug
      data =rpiAux->MU_IO_REG;
	  enQueR(data);

	  if((rpiAux->MU_LSR_REG & 0x01)==1) { // More Receive Data?
        data =rpiAux->MU_IO_REG;
	    enQueR(data);	
	  }
	} else if ( irq == 0x02) { // Send(Transmit empty) Interrupt
	   rcvSndI[1]++;//Send Empty counter up
	   m_serialPutChar('-');//Debug

//  **************111 ++ **********
	   data = deQueT(); 
	   if((data)  >= 0) {  // Available data from Que

		  if((!(rpiAux->MU_LSR_REG &0x20) ==0 )  ) { //Transfer FIFO Empty
//		    if(outpT == inpT) rpiAux->MU_IER0_REG =0x01;//Next Que is Empty,then Disable Send Interrupt only Rcv TT
//          m_serialPutChar('-');//Debug
		    rpiAux->MU_IO_REG=data ;  //data to Trancefer FIFO
	        rcvSndI[2]++;//Real Send counter up
	      } // if LSR check End
			else m_serialPutChar('#');  //Error, Transfer FIFO Full

	   } //End if Available data 
//  **************** 222 ++ ********************
		if(outpT == inpT) rpiAux->MU_IER0_REG =0x01;//Next Que is Empty,then Disable Send Interrupt only Rcv TT
		else 		  rpiAux->MU_IER0_REG =0x03; //Int Send and Rcv mode

	} 

}
void rcvSndIcnt(int * tmp1) {
 tmp1[0]=rcvSndI[0];
 tmp1[1]=rcvSndI[1];
 tmp1[2]=rcvSndI[2];

}

void enable_m_serial_Int(){ //IRQ29
   struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;	
 
	rpiIRQController->Enable_IRQs_1 |= 0x01<<29;


}

void disable_m_serial_Int(){ //IRQ29
   struct rpiIrqController *rpiIRQController = 
		(struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	
rpiIRQController->Enable_IRQs_1 &= ~(0x01<<29);	


}

void m_serialInitIrcv(void)  // Same as mini_serial9AdI.c
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;

	m_serialInit();
	rpiAux->MU_IER0_REG=0x01;// Over write =0x01 ; Debug =0x03
				//Enable 01:Receive Interruptrrupi 02:trancemit Interrupt 1+2= 0x03 TT
	inpR=rvbuf;         outpR=rvbuf;
   enable_m_serial_Int();// Enable IRQ29 Int					
}

void m_serialInitIsndrcv(void) // New function at mini_serial9APls.c
{
	struct rpiAux* rpiAux= RPI_AUX_BASE;
	m_serialInit();
	rpiAux->MU_IER0_REG=0x03;// Over write Interrupt Receive and trans.
	//Enable 1:Receive Interrupt 2:trancemit Interrupt 1+2= 0x03 
        inpT=txbuf;         outpT=txbuf;
	inpR=rvbuf;         outpR=rvbuf;
	enable_m_serial_Int();// Enable IRQ29 Int
}



void m_serialPutCharI(int data) // Changed 2017 TT 
{
int data1;
	struct rpiAux* rpiAux= RPI_AUX_BASE;	

	enQueT(data);	

	if((!(rpiAux->MU_LSR_REG &0x20) ==0 ) && (data1 =deQueT()) !=-1  ) {
		    rpiAux->MU_IO_REG=data1 ;
		    rcvSndI[2]++;// Real Send count up
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
	if(temp ==outpT) {   // 
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
int datQueT(void) { // Output Que count
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


