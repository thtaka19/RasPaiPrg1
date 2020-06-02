#ifndef _COMMON_H_INCLUDED_
#define _COMMON_H_INCLUDED_
#define MAX_IDLE_TIME               (21)
extern unsigned char SW_status;
extern 	unsigned short AD01[];
extern unsigned short LCD_status;
extern unsigned int REAL_sec;
extern unsigned int REAL_msec;
//extern unsigned int IDLE_time[];
//extern unsigned int IDLE_timep ;
//extern unsigned int   IDLE_cnt ;
//extern volatile unsigned int IDLE_cnt2;
extern unsigned short TASK_status[];
extern unsigned short INTERUPT_status[];
extern unsigned long long int Sys_REAL_micro[];// get_systime(void) every sec time
extern unsigned int SRmPtr;
extern unsigned int REAL_secAry[];
#endif
