
#include <stdio.h>
#include <stdint.h>

// device
#include "../cmn00/ADT7310.h"
#include "../cmn00/AQM0802.h"
#include "../cmn00/led.h"
#include "../cmn00/button.h"
#include "../cmn00/mini_serial.h"
#include "../cmn00/raspGPIO.h"
#define LED_RED16   		(0x01 << 16) 	// Port16(10+6)
#define LED_GREEN20   		(0x01 << 20) 	// Port20
#define LED_RED21     		(0x01 << 21) 	// Port21

#define CYCLES_PER_MS               (3000) // 2015 05
#define LCDclrscr aqm0802_cleardisplay // 2017
void delay_ms(int milliseconds)
{
    long volatile cycles = milliseconds;
	int volatile  cycle0 = CYCLES_PER_MS;
     
    while (cycles != 0)
	{
        cycles--;
		cycle0 = CYCLES_PER_MS;
	  while(cycle0 != 0)
		  cycle0--;
	}
}
void delay(unsigned int milliseconds)
{
  delay_ms(milliseconds);
}
int main7100(void){
	// オ(0xB5),ン(0xDD),ド(0xC4 + 0xDE), \0(0x00)
	uint8_t tempStr[] = {0xB5,0xDD,0xC4,0xDE,0x00};
	uint8_t tempVal[10];
	float temp;
    char rcvChar = 0;
//	rpi_init();
 printf("main7100_0 Start v1\n");
	m_serialInit();// Serial Init 
	ledInit();// Gpio 16, Gpio20
	buttonInit();// Gpio18,Gpio19
printf("main7100_1 will Spi Init v1\n");
	// SPI initialize
	SPI0_begin(SPI_SS_CS0);
	SPI0_setDataMode(SPI_MODE3);
printf("main7100_2 will I2c Init v1\n");
	// I2C initialize
	Wire1_begin();

	// device initialize
	aqm0802_init();// I2C LCD
	adt7310_initialize();// SPI Temperature

	printf("07_10 All GPIO hard Check V1 main Start \r\n"); //2017 TT
	m_serialPutStr("a  LED On  (Gpio16, Gpio20) \r\n");//ledOn(unsigned int mask)
	m_serialPutStr("b  LED Off (Gpio16, Gpio20) \r\n");//ledOff(unsigned int mask)
	m_serialPutStr("C  Sw status (Gpio18,Gpio19) \r\n");//uint8_t buttonRead(void)

	m_serialPutStr("d  Write (I2C)LCD Hello \r\n");
	m_serialPutStr("e  Write (I2C)LCD World  \r\n");
	m_serialPutStr("f  Read (SPI)Temperature  \r\n");//LCD cleardisplay
	m_serialPutStr("g  Clear LCD  \r\n");	

	m_serialPutStr("q  quit \r\n");
	m_serialPutStr("Others LED brink (Gpio20 and OnBoard(Zero or Pai1 B+))\r\n>");

		// Clear LCD display
		aqm0802_cleardisplay();

       rcvChar = m_serialGetChar();
   while (rcvChar != 'q')
    {
        /* Wait for an incoming character. */
 

        /* Echo the character back along with a carriage return and line feed. */
 
        if((rcvChar == -1) || (rcvChar == '\n') ||(rcvChar == '\t') ){
	m_serialPutStr("Bs/-1/Rtn Retern-Key read Break\r\n");		
	    if(rcvChar == -1) m_serialPutStr( "..-1 read Break\r\n");	
	      if(rcvChar == '\n') m_serialPutStr( "..BkN read Break\r\n");	
	      if(rcvChar == '\t') m_serialPutStr( "..BkT read Break\r\n");			
	  }
	  else {
		         m_serialPutChar(rcvChar);        
        m_serialPutChar('\r');
        m_serialPutChar('\n');
	delay_ms(300);

if(rcvChar == 'a') {
		ledOn(LED_RED16);
		ledOn(LED_GREEN20);
		ledOn(LED_RED21);
		ledTogglePi2();
m_serialPutStr("ledOn(LED_RED16);ledOn(LED_GREEN20); \r\n>");
}
else if(rcvChar == 'b') {
		ledOff(LED_RED16);
		ledOff(LED_GREEN20);
		ledOff(LED_RED21);
		ledTogglePi2();
m_serialPutStr("ledOff(LED_RED16);ledOff(LED_GREEN20);");
}
else if(rcvChar == 'c') {
uint8_t Sw_status;
 		Sw_status=buttonRead() & 0x0f;
printf("Sw Status (SW0(GPIO13)On == 1 ,SW1(GPIO18)On ==2) = %X \r\n",Sw_status);	

}
else if(rcvChar == 'd') {
// print "Hello"
		LCDputs("Hello1");//aqm0802_print_line("Hello1", 6);
m_serialPutStr("LCDputs(Hello1)\r\n");
}
else if(rcvChar == 'e') {
// print "World"
//		LCDputs("World");//aqm0802_print_line("World", 5);
		aqm0802_print_line("World", 2);
m_serialPutStr("LCDputs(World)\r\n");
}
else if(rcvChar == 'f') {
// print "World"
//		LCDputs("World");//aqm0802_print_line("World", 5);
		aqm0802_cleardisplay();

		// get temperature value
		temp = adt7310_getTemperature(ADT7310_MODE_CONRINUOUS);

		// Show temperature
		sprintf(tempVal,"%4.1f dec",temp);
		aqm0802_print_line(tempStr, 1);
		aqm0802_print_line(tempVal, 2);
		printf("Temperatur=%f\r\n",temp);

m_serialPutStr("Read (SPI)Temperature\r\n");
}
else if(rcvChar == 'g') {
		aqm0802_cleardisplay();

m_serialPutStr("LCD cleardisplay\r\n");
}
else if(rcvChar == '\n') {
	m_serialPutStr("Bk N Retern-Key read\r\n");
}
else if(rcvChar == 'x') {//dToggle( );
	ledTogglePin(20);
	m_serialPutStr("xCalled ledToggle( )\r\n>");
	}
else {
ledToggle( );// GPIO20,GPIO21,GPIO47
//ledTogglePin(20);
m_serialPutStr("Others Called \r\n>");
}
} //No return-Key else End
		// wait 0.3sec
		delay_ms(3000);
       rcvChar = m_serialGetChar();

	} // While End
	SPI0_end();
	m_serialPutStr("End Program: Bye! \r\n");
	return 0;
}


//***********************************************************************/
//*	GNU Linker .text/.bss Initialize routine before main function.	*/
//***********************************************************************/
/***
extern char etext[], sdata[], edata[], sbss[] , ebss[];
void initializeMemory()   // Memoru clear called from starup10.s
{
	char *src, *dst;
	
	for( src = etext, dst = sdata ; dst< edata ; )  // Initial data copy
		*dst++ = *src++;
		
	for( dst=sbss                 ; dst< ebss  ; )   // Bss 0 clead
		*dst++ =0;

}

void interruptServiceRoutine(void) { ///// Dummy for Interrupt called from startup10.s

}
***/
