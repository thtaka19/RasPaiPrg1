/**********************************************************************
 *
 * Filename:    moncont.c
 * 
 * Description: Monitor and Control program.
 *
 * Notes:       
 *
  **********************************************************************/
#include <kernel.h>
#include "kernel_cfg.h"

#include "syssvc/serial.h"
#include "syssvc/syslog.h"
//#include "sample1.h"
#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* 文字入力するシリアルポートID */
#endif /* TASK_PORTID */

//#include "definesN.h"
#include "cli.h"
//#include "serial.h"
//#include "rpi_type.h"  // 2017
// device

#include "../cmn00/AQM0802.h"
#include "../cmn00/ADT7310.h"
/*******Init****************/
#include "../cmn00/buzzer.h"
//#include "led.h"
#include "../cmn00/led.h"
#include "../cmn00/button.h"

#include "../cmn00/mini_serial.h"
//#include "lcd.h"
//#include "adda.h"

#define CYCLES_PER_MS               (10000) // 2015 05
#define LCDclrscr aqm0802_cleardisplay // 2017
//#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

void delay(int milliseconds)
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
void delay_ms(unsigned int milliseconds)
{
  delay(milliseconds);
}
/**********************************************************************
 *
 * Function:    main
 *
 * Description: Monitor and control command line interface program.
 * 
 * Notes:       
 *
 * Returns:     This routine contains an infinite loop.
 *
 **********************************************************************/
int mainInit(void)
{
//    char rcvChar;
//    int  bCommandReady = FALSE;
//	m_serialInit();// Serial Init 2018 06 TT


//	m_serialInit();// Serial Init 
ledInit();
	// SPI initialize
	SPI0_begin(SPI_SS_CS0);
	SPI0_setDataMode(SPI_MODE3);

	// I2C initialize
	Wire1_begin();

	// device initialize
	aqm0802_init();
	adt7310_initialize();
//	LCD_init();
	buttonInit();
//	addaInit();
		// LCD display clear
} // End maininit

void cliCommandTask3(intptr_t exinf)
{
    char rcvChar;
    int  bCommandReady = FALSE;

   m_serialPutStr("Monitor and Control Program 21_70 S\r\n");
		aqm0802_cleardisplay();
LCDputs("21_7 v1");//aqm0802_print_tart
  m_serialPutStr("21_7 5\r\n");	
	
    m_serialPutStr("Monitor and Control Program 21_70 \r\n");
m_serialPutStr("Exp.  LCD=xxx \r\n");
m_serialPutStr("Exp.  Help \r\n");
    m_serialPutChar('>');
	LCDgotoxyint(0,0);
	LCDputchar('V');
	LCDputchar('2');
	LCDputchar('1');
	LCDputchar('_');
	LCDputchar('7');
    while (1)
    {
        /* Wait for a character. */
//        rcvChar = m_serialGetChar();
		SVC_PERROR(serial_rea_dat(TASK_PORTID, &rcvChar, 1));
        /* Echo the character back to the serial port. */
        m_serialPutChar(rcvChar);

        /* Build a new command. */
        bCommandReady = cliBuildCommand(rcvChar);

        /* Call the CLI command processing routine to verify the command entered 
         * and call the command function; then output a new prompt. */
        if (bCommandReady == TRUE)
        {
            bCommandReady = FALSE;
            cliProcessCommand();

            m_serialPutChar('>');
        }
    }

    return ;
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

