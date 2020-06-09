
#include <stdio.h>
#include <stdint.h>
#define CYCLES_PER_MS               (3000) // 2017 05
//#define mini0_puts m_serialPutStr
#define LED_GREEN16   		(0x01 << 16) 	// Port16(10+6)
void clearBss(void);

//void m_serialPutStr(char const *pOutputStr)
void serialPutStrXXX(char const *pOutputStr)
{
    char const *pChar;
    /* Send each character of the string. */
    for (pChar = pOutputStr; *pChar != '\0'; pChar++)
        m_serialPutChar(*pChar);
//       serialPutChar(*pChar);
} 

void delay_ms(int milliseconds)
{
    long volatile cycles = milliseconds;
	int volatile  cycle0 = CYCLES_PER_MS;
     
    while (cycles != 0) {
        cycles--;
		cycle0 = CYCLES_PER_MS;
	  while(cycle0 != 0)
		  cycle0--;
	}
}
void delay(int milliseconds){ delay_ms( milliseconds);}

int main(void){
	disableInstructionCache();
	disableDataCache();
	disableMMU();


	// disable interrupt(IRQ)
//	disable_all_IRQ();
	interruptDisable();
	// Set vectortable
//	set_vector_table();

	// Initialize system timer
//	init_syst();

	
	ledInit();
	ledOn(LED_GREEN16);

	// Enable UART1(mini_UART) 
	m_serialInit();
//	Serial_begin(115200);// Serial Init 

//	timerInit();

//	delay_ms(10);


	m_serialPutStr("Start Main Rpi00_0 Pai3 Main V11\r\n");
//	serialPutStr("Start Main Rpi00_0 Pai3 Main V11\r\n");

//	writeVectorBaseRegister(0x0000);
//	setLowVector();
//	setHighVector();

	// Enable IRQ interrupt
//	enable_IRQ();

//	printf("VectorBaseRegister (in Main2) = 0x%08x\r\n",readVectorBaseRegister());
//	printf("CPSR (in Main2) = 0x%08x\r\n",getmode());


	printf("\r\n Type EchoBack Characerr\n");
	while(1){
	 char rcvc;

	  rcvc=m_serialGetChar();
	  m_serialPutChar(rcvc);
//	  rcvc=serialGetChar();
//	  serialPutChar(rcvc);
 	  delay_ms(10);
	}
	return 0;
}

//***********************************************************************/
//*	GNU Linker .text/.bss Initialize routine before main function.	*/
//***********************************************************************/

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
/***
void print01(void){
 printf("XX");
}
void print02(void){
 printf("-2");
}
void print03(void){
 printf("-3");
}void print09(void){
 printf("++");
}
***/
