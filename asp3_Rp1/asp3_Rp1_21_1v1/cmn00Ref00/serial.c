
//#include "rpi_serial.h"
#include "../cmn00/rpi_peripherals.h"
//#include "rpi_gpio.h"

//#define SERIAL_CLOCK	3000000
#define uart0_putc serialPutChar
#define uart0_getc serialGetChar
// Set read/write timeout(us)
long long write_to = -1;
long long read_to = -1;

void delay150(int milliseconds)
{
    long volatile cycles = milliseconds;
	int volatile  cycle0 = 150;
     
    while (cycles != 0)
	{
        cycles--;
		cycle0 = 150;
	  while(cycle0 != 0)
		  cycle0--;
	}
}
int Serial_begin(int baudrate){
	unsigned int baudrate_temp[11]={300, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200 };
	unsigned int ib_list[] = {625, 156,78,39,19,13,9,6,4,3,1};
	unsigned int fb_list[] = {0,16,8,4,34,1,49,33,57,16,40};
	int flag=0;
	int i;
	// baudrate check
	for(i=0;i<11;i++){
		if(baudrate == baudrate_temp[i]){
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		return -1;
	
	/**** start Initialize setting***/
	// disable UART0
	*UART0_CR 	= 0;
	
	//Set GPIO port(GPIO14,GPIO15)
	vu32_t *res;
	vu32_t *res1;
	res = GPFSEL1;
	res1 = GPPUDCLK0;

//	setPullUpDownXX(14,INPUT_PULLDOWN);
		*GPPUD 	= 0x01;

//	for(i=0;i<150;i++){asm("mov r0,r0");} // wait 150 cycle
delay150(1);
	*res1 = (0x01 << (14));
delay150(1);
	*res &= GPFSEL_MASK_IN(14);

//	setPullUpDownXX(15,INPUT_PULLDOWN);//Comment v103
//	for(i=0;i<150;i++){asm("mov r0,r0");} // v108 Do NG, wait 150 cycle
delay150(1);
	*res1 = (0x01 << (15));
//	for(i=0;i<150;i++){asm("mov r0,r0");} //v107Ng// wait 150 cycle
delay150(1);
	*res &= GPFSEL_MASK_IN(15);

	*res |= GPFSEL_MASK_ALT0(14);
	*res |= GPFSEL_MASK_ALT0(15);

	// Set baud rate(exp. for 115200 bits/sec)
	*UART0_IBRD = ib_list[i];
	*UART0_FBRD = fb_list[i];
	
	// LCRH
	// stick parity dis, 8bit, FIFO en, two stop bit no, odd parity, parity dis, break no
	*UART0_LCRH = 0x70;

	// CR
	// CTS dis, RTS dis, OUT1-2=0, RTS dis, DTR dis, RXE en, TXE en, loop back dis, SIRLP=0, SIREN=0, UARTEN en
	*UART0_CR 	= 0x0301;
	/**** End Initialize setting ***/
	return 0;
}

void Serial_end(void){
	// UART disable
	*UART0_CR = 0;
}

int Serial_available(void){
	if(!(*UART0_FR & (0x01 << 4))){
		return 1;
	}
	return 0;
}

int Serial_write(char *buf,int len){
	int i=0;
	while(i < len){
		if(uart0_putc(*buf) < 0)
			break;
		i++;
		buf++;
	}
	return i;
}
int serialGetChar(void){
//int uart0_getc(void){
	unsigned long long to;

	// Waite until data comming
	//while(Serial_available() == 0){ //!(*UART0_FR & (0x01 << 4)) == 0
	while(!(*UART0_FR & (0x01 << 4)) == 0){ }
	// Read data
	int c = *UART0_DR;
	return c & 0xff;
}
int serialPutChar(int c){
//int uart0_putc(int c){
	unsigned long long to;

	// Wait transfer FIFO become empty
	while(!(*UART0_FR & (0x01 << 5)) == 0){ }	
	// Write to
	*UART0_DR = c;
	return 1;
}
void serialPutStr(char const *pOutputStr)
{
    char const *pChar;

    /* Send each character of the string. */
    for (pChar = pOutputStr; *pChar != '\0'; pChar++)
        serialPutChar(*pChar);
} 

int uart0_puts(char *s){
	int i=0;
	while(*s != '\n' && *s != '\0'){
		if(uart0_putc(*s) < 0)
			break;
		i++;
		s++;
	}
	if(*s == '\n'){
		uart0_putc('\n');
		i++;
	}
	return i;
}

char *uart0_gets(char *s,int len){
	int i=1;
	int c;
	do{
		c = uart0_getc();
		if(c == -1)
			return (void *)0;
		*s = c;
		s++;
		i++;
	
	}while(i < len && c != '\n' && c != '\r'); // 2017 TT
	*s = '\0';

	return s;
}

