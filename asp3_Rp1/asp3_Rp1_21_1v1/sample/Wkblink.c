/**********************************************************************
 *
 * Filename:    blink.c
 * 
 * Description: ITRON Blinking LED program.
 *
 * Notes:       
 *
 *
 **********************************************************************/
#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"

//#include "h83069f.h"

#include "serial.h"

#include "led.h"

//#define Sci_PutChar    serialPutChar 

//	extern  void hos_vector024(void) ;
//	extern void OsTimer_TimerHandler(VP_INT) ;


/**********************************************************************
 *
 * Function:    blinkLedTask
 *
 * Description: This task handles toggling the green LED at a
 *              constant interval.
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/ 
//void Task1(VP_INT exinf)
void blinkLedTask(VP_INT exinf)
//void blinkLedTask(cyg_addrword_t data)
{
	serialPutStr("Start blinkLedTask ");
	serialPutChar('0'+exinf);
	serialPutStr("\r\n");
	
    while (1)
    {
    /* Delay for 500 milliseconds. */
    //    cyg_thread_delay(TICKS_PER_SECOND / 2);
		dly_tsk(500);
        ledToggle( );
    }
}


