/**********************************************************************
 *
 * Filename:    interrupt.c
 * 
 * Description: eCos interrupt program.
 *
 * Notes:       
 *
 *
 **********************************************************************/
//#include "kernel.h"
//#include "kernel_id.h"
#include <kernel.h>
#include "kernel_cfg.h"
//#include <cyg/kernel/kapi.h>
//#include "definesN00.h"

//#include "timer.h"
//#include "led.h"
#include "common.h"
//#include "button.h"
//#include "adda.h"
#include "commands.h"
//#include "mailboxApi.h"
//#include "serial.h"
#include "../cmn00/led.h"
#include "../cmn00/button.h"


#include "../cmn00/mini_serial.h"
#define CMFA_INTERRUPT_FLAG_CLEAR		    (0x00)
//#define TIMER1_INT                      (38) // 2016 TT
#define TIMER16_INT                     (24) //Vector24 =  Timer16 Ch0  Timer


/* Declare the task variables. */

/**********************************************************************
 *
 * Function:    t100msTask1
 *
 * Description: This task handles toggling the LED when it is
 *              signaled from the timer interrupt handler.
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/ 
 
//void t100msTask1(cyg_addrword_t data)
void t100msTask1(intptr_t exinf)
	
{
 //unsigned int ledcnt=0;  
 m_serialPutStr("Start 100ms Task1\r\n");
  while (1)
    {
        /* Wait for the signal that it is time to toggle the LED. */
     //   cyg_semaphore_wait(&Semaphore1);
//m_serialPutChar('2');
		wai_sem(Semaphore1);
//m_serialPutChar('3');
        /* Change the state of the green LED. */
        ledTogglePin(20);
    }
}


//void t500msTask2(cyg_addrword_t data) //  500ms  period Task2
void commandsTimer00(int ) ;
void commandsIDLE(void);
long cnt0 = 0;
void t500msTask2(intptr_t exinf)
{
 //unsigned int ledcnt=0;
   unsigned int icnt=0; 
  unsigned int oldIDLEcnt =0; 
  unsigned char  SW_statusNow; 
	char s[10];
 //char s[10];
//	cnt0++;
  m_serialPutStr("Start 500ms Task2\r\n");
  while (1)
    {
        /* Wait for the signal that it is time to toggle the LED. */
    //    cyg_semaphore_wait(&Semaphore2);
//m_serialPutChar('6');
		wai_sem(Semaphore2);
//m_serialPutChar('7');
	//SW_status = buttonRead();// Set Sw status on Common Area
	SW_statusNow = buttonRead();// Set Sw status on Common Area
	
	if((SW_status & 0x0f)!=(SW_statusNow & 0x0f)){
		mboxPutChar('1');// SW Command
		m_serialPutStr("Sw status Changed\r\n");
	}
	SW_status =	SW_statusNow ;	
//	adConvert( AD01);// Set Ad ch0 Value(Tempruture) on Common Area 
/***	
//  Save Idle  counts to array
    	if(cnt0 == 1) IDLE_time[IDLE_timep] = 0;
	if(IDLE_cnt2 >= oldIDLEcnt)
		IDLE_time[IDLE_timep]= IDLE_cnt2 - oldIDLEcnt;
	else IDLE_time[IDLE_timep]= 10000+IDLE_cnt2 - oldIDLEcnt;
	if(IDLE_time[IDLE_timep]> 500) { // Debug
		m_serialPutStr(" IDLE Over 500! = ");	
		//putxval0((unsigned long)IDLE_time[IDLE_timep],4);
		//m_serialPutStr("\r\n");		
	}
	if(IDLE_time[IDLE_timep] < 451) { // Debug
		m_serialPutStr(" CPU Over 10% = ");
	itoax( (IDLE_time[IDLE_timep]),s);//: Max count(500:100%)
		m_serialPutStr(s);
		m_serialPutStr(" ");	
		//putxval0((unsigned long)IDLE_time[IDLE_timep],4);
		//m_serialPutStr("\r\n");
 commandsTimer00(0);// No LCD output		
	}

	IDLE_timep++;
	IDLE_cnt++;
			oldIDLEcnt = IDLE_cnt2;
		if(IDLE_timep >= MAX_IDLE_TIME){
			IDLE_timep = 0;
			
	//		commandsIDLE();//  Show  Idle Array
		}
	***/
		icnt++;
//		m_serialPutChar('0'+icnt);//Debug
	if(icnt >=20) {

		commandsTimer00(0);//Only serial Output
		m_serialPutStr("\r\n");
//		commandsIDLE();
		icnt=0;		
	} 

    //cyg_mbox_put(mailboxHdl, (void *)(con));// every 1 sec Access to LCD-Output Tas    
        /* Change the state of the green LED. */
//        ledToggleRed();
	ledTogglePin(21);
    } // while End
}

/**********************************************************************
 *
 * Function:    idleTask0
 **********************************************************************/
 /***
#define CYCLES_PER_MS               (7200) // 1msecond 
//void idleTask5(cyg_addrword_t data)
void idleTask5(intptr_t exinf)
{	
	int volatile  cycle0 = CYCLES_PER_MS;//millisecond
 //unsigned int ledcnt=0;  
  while (1)
    {
		//i++;
        IDLE_cnt2++;
        if(IDLE_cnt2 >= 10000)	IDLE_cnt2=0; 
		if((IDLE_cnt2 % 1000)==999) ;//serialPutStr("-"); // Debug
	  cycle0 = CYCLES_PER_MS;
	  while(cycle0 != 0)   cycle0--;
	} 
    
}
***/
/**********************************************************************
 *
 * Function:    timerDsr
 *
 * Description: Deferred service routine for the timer interrupt.
 * 
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/
void timerSet(void){

	if(SRmPtr <= 60)SRmPtr++;//common.c define Max 200 but
	REAL_secAry[SRmPtr] = REAL_sec;
	Sys_REAL_micro[SRmPtr] = get_systime();	
	}
	
 static int count_1000ms = 0;
 static int wait_bgn = 0;
//void timerDsr(cyg_vector_t vector, cyg_ucount32 count, cyg_addrword_t data)
void timerDsr(void )
{
    /* Signal the task to toggle the LED. */
 if(wait_bgn <= 10) {//Waite until task1 and task2 do wai_sem(SemaphoreX);
//m_serialPutChar('0');
	wait_bgn++;
 	if (wait_bgn == 5) {
 	m_serialPutStr("Timer 100 and 500 Start\r\n");
	SRmPtr = 0;
	REAL_secAry[0] = REAL_sec;
	Sys_REAL_micro[0] = get_systime();	
//		REAL_sec++ ;
	}
	return;
  }
	  count_1000ms+=10;//  ISR call 10ms
//	 count_1000ms++;
	  if(count_1000ms > 1000) {									
	    count_1000ms=0;					/* reset 1000ms counter */
		REAL_sec++ ;
		timerSet();
//		commandsTimer00(0);//Debug 
	  }
      if( (count_1000ms % 100 ) == 10) {
	//	cyg_semaphore_post(&Semaphore1);
	 sig_sem(Semaphore1); 
//m_serialPutChar('1');
	  }
	  if( count_1000ms  == 250  || count_1000ms  == 750) {
		sig_sem(Semaphore2); 
//m_serialPutChar('5'); 		  
	//	cyg_semaphore_post(&Semaphore2);
	  } 
	  
 
}


