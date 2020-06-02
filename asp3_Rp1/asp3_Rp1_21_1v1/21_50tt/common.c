/*								*/
/*		common variables		*/
/*								*/
//#define MAX_IDLE_TIME               (30)
#include "common.h" 
unsigned char  SW_status;
unsigned short AD01[4];
unsigned short LCD_status;
unsigned int   REAL_sec = 0;
unsigned int   REAL_msec = 0;
//volatile unsigned int   IDLE_cnt2 =0;
//unsigned int   IDLE_time[MAX_IDLE_TIME+1];
//unsigned int   IDLE_timep = 0;
//unsigned int   IDLE_cnt = 0 ;//
unsigned short TASK_status[10];
unsigned short INTERUPT_status[5];
unsigned long long int Sys_REAL_micro[200];// get_systime(void) every sec time
unsigned int   REAL_secAry[200];
unsigned int SRmPtr = 0;
#define MAX_COMMAND_LEN             (20)
