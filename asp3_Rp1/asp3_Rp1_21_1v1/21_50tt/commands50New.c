/**********************************************************************
 *
 * Filename:    commands.c 
 * 
 * Description: Command functions for command line interface.
 *
 * Notes:       
 * 
 **********************************************************************/


#include "../cmn00/rpi_type.h"
#include "definesN00.h"
#include "cli.h"
#include "commands.h"
#include "common.h" 
#include "../cmn00/led.h"
#include "../cmn00/buzzer.h"
//#include "serial.h"
#include "../cmn00/button.h"
#include "../cmn00/mini_serial.h"
#ifndef NULL
#define NULL            (void *)0
#endif
//#define CPU_MAX_CNT       (600)
#define CPU_MAX_CNT       (520) //  
#define LCDclrscr aqm0802_cleardisplay // 2017
#include "../cmn00/AQM0802.h"
#include "../cmn00/ADT7310.h"
void delay(int);



int atoi(char *str)
 {
	int cnt;
	int num=0;
	for (cnt = 0; (str[cnt] >= '0') && (str[cnt] <= '9') ; cnt++){
	num = 10 * num + (str[cnt] - '0');
	}
	return num ;
 }
void itoax(int n,char s[]){
	 int i,j,sign;
	 char c;

	 if((sign = n) < 0) n = -n;
	 j = 0;
	 do {
		 s[j++] = "0123456789"[n % 10];
	
			n = n /10 ;
		 } while  ((n > 0) && j < 10);
	 
	 if (sign < 0) {s[j++] = '-';}
	 s[j]='\0';
	
	 for(i=0,j=j-1;i<j;i++,j--) {
		c = s[i]; 
		s[i] = s[j];
		s[j] = c ;			 
	 }

 }
 
void itoa10(int num, char * numC) 
{
	int i,idx;
char invNumC[10];
	if(num <=0){
		numC[0] = '0';
		numC[1] = '\0';
		return;
	}
	idx=0;
	for(i=0;i<6 && (num > 0);i++) {		
		invNumC[idx++]='0'+num%10;
		num=num/10;		
	}
	for(i=0;i<idx;i++)numC[i]=invNumC[idx-i-1];
	numC[i]='\0';	
}
/*Send HexDesimal Style*/
int putxval0(unsigned long value, int column)
{
  char buf[9];
  char *p;
  p = buf + sizeof(buf) - 1;
  *(p--) = '\0';

  if (!value && !column)
    column++;

  while (value || column) {
    *(p--) = "0123456789abcdef"[value & 0xf];
    value >>= 4;
    if (column) column--;
  }

  //puts(p + 1);
   m_serialPutStr(p+1);
  return 0;
}

/**********************************************************************
 *
 * Function:    commandsLed
 *
 * Description: Toggle the green LED command function.
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/
void commandsLed(void)
{
    ledToggle();
 //   ledTogglePin(20);
}

/**********************************************************************
 *
 * Function:    commandsBuzzer(No buzzer) , commandsLcdData , commandsLcdCler
 *
 * Description: Lcd Display ; LCD clear command function.
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/
void commandsBuzzer(void)
{
    buzzerToggle();
}
/***************************************************************/
void commandsLcdHello(void)
{
	m_serialPutStr("commandsLcdHello called \r\n datap=");// Debug
	LCDgotoxyint(0,0);	
	m_serialPutStr("\r\n");
	LCDputs("Hello ");
 
}

/***************************************************************/
void commandsLcdCler(void)
{
	m_serialPutStr("commandsLcdCler called\r\n");//Debug
	LCDclrscr();   
}
/**********************************************************************
 *
 * Function:    commandsSw
 *
 * Description: SW command function. Display SW(Port5 4pins) state to LCD
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/
void commandsSw(void)
{
	unsigned char SW_status;
	LCDclrscr();
	SW_status = buttonRead();// Read Port5 4pins status
 
	LCDgotoxyint(0,0);
delay(10);	
    LCDputs("SW1 SW2 ");// 8 charcters/line
 // if (LCD_sw) {
//	LCD_column=0;
						/* reset LCD column number */	  
	LCDgotoxyint(1,1);//SW1						/* Display SW1 status */
	if (SW_status&0x01) {
		LCDputs("ON ");

	m_serialPutStr("SW1(GPIO13) ON \r\n");
	} else { 
		LCDputs("-- ");
	m_serialPutStr("SW1(GPIO13) Off \r\n");
	}	LCDgotoxyint(4,1);//SW1						/* Display SW1 status */
	if (SW_status&0x02) {
		LCDputs("ON ");

	m_serialPutStr("SW2(GPIO18) ON \r\n");
	} else { 
		LCDputs("-- ");
	m_serialPutStr("SW2(GPIO18) Off \r\n");
	}
/***
	LCDgotoxyint(8,1);						// Display SW2 status 
	if (SW_status&0x02) {
		LCDputs("ON ");
	} else { 
		LCDputs("-- ");
	}
	LCDgotoxyint(12,1);						// Display SW3 status 
	if (SW_status&0x04) {
		LCDputs("ON ");
	} else { 
		LCDputs("-- ");
	}
	LCDgotoxyint(0,1);					// Display SW0 status 
	if (SW_status&0x01) {
		LCDputs("ON ");
	} else { 
		LCDputs("-- ");
	}
**/	
  
}

/***************************************************************/
void commandsTemp(void)
{
	// オ(0xB5),ン(0xDD),ド(0xC4 + 0xDE), \0(0x00)
	uint8_t tempStr[] = {0xB5,0xDD,0xC4,0xDE,0x00};
	uint8_t tempVal[10];
	float temp;
//	int tempUp;
        int tmpLw;
		// Clear LCD Display
		LCDclrscr();//aqm0802_cleardisplay();

		// Get temperature
		temp = adt7310_getTemperature(ADT7310_MODE_CONRINUOUS);

		// Show temperature
//		sprintf(tempVal,"%4.1f dec",temp);
itoax((int)temp,tempVal);
tmpLw = (int)(temp*10) - ((int)temp)*10;
		 LCDputs(tempStr);//aqm0802_print_line(tempStr, 1);
	LCDgotoxyint(0,1);
		 LCDputs(tempVal);//aqm0802_print_line(tempVal, 2);
	  LCDputchar('.');
 // LCDputchar('.');
 LCDputchar('0'+tmpLw );
//	m_serialPutStr(tempStr);
	m_serialPutStr("Temp=");
	m_serialPutStr(tempVal);
	m_serialPutChar('.');
	m_serialPutChar('0'+tmpLw);
	m_serialPutStr("\r\n");
}
/**********************************************************************
 *
 * Function:    commandsAdLcd
 *
 * Description: Ad input(An0,An1)-> Lcd Display ; Ad input Display Serial
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/

/**********
void commandsAdLcd(void) {
	unsigned short an01[2];
	char numC[10];
	int i ;
	LCDclrscr();// LCD clear
	
	adConvert( an01);// Read An0,An1 pin input 
	
	LCDgotoxy(0,0);	
	itoa10((int)an01[0], numC) ;

	LCDputs("Ad0=");
	LCDputs(numC);
	
	LCDgotoxy(0,1);
	itoa10((int)an01[1], numC) ;

	LCDputs("Ad1=");
	LCDputs(numC);
	for(i=0;i<10;i++) { 		
	adstart(); // Read Read An0,An1 pin input and display serial 
	}	
}
***********/

/***************************************************************/
void commandsLcdData(char * datap)
{
	m_serialPutStr("commandsLcdData called \r\n datap=");// Debug
	m_serialPutStr(datap);//Debug
	m_serialPutStr("\r\n");
	LCDputs(datap);
    //buzzerToggle();
}
// /**********************************************************************
/**********************************************************************/
void commandsTimerprt(unsigned long timemili) {
	int hour,min,sec,mili,timedt ;
    
	char hourC[4],minC[4],secC[4],miliC[5];
	//serialPutStr("Not Install yet \r\n");
	  timedt = (int) (timemili/1000);
	  hour = (int) timedt/3600 ;
	  min  = (int)(timedt % 3600) / 60 ;
	  sec  = (int)(timedt % 3600) % 60 ;
      mili = (int)(timemili%1000);
	  itoa10(hour, hourC) ;
	  itoa10(min, minC) ;
	  itoa10(sec, secC) ;
	   itoa10(mili, miliC) ; 
	   
	  m_serialPutStr(minC);
	  m_serialPutChar(':');
	  m_serialPutStr(secC);
	  m_serialPutStr(".");
	  m_serialPutStr(miliC);
	  m_serialPutStr(" ");
}

void commandsTimerSys(void) {

	unsigned long timedtmili;
	timedtmili = (unsigned long)(REAL_secAry[SRmPtr]*1000);
	 m_serialPutStr(" R_sec= ");
	commandsTimerprt(timedtmili);
	
//	timedtmili = (unsigned long)((Sys_REAL_micro[SRmPtr]-Sys_REAL_micro[0])/1000);
	timedtmili = (unsigned long)((Sys_REAL_micro[SRmPtr])/1000);
	 m_serialPutStr(" Sys_time= ");
	commandsTimerprt(timedtmili);
	m_serialPutStr("\r\n");
}

void commandsTimer00(int out) { // out >0  LCD output
	int hour,min,sec ;
	char hourC[4],minC[4],secC[4];
	//serialPutStr("Not Install yet \r\n");
	
	  hour = REAL_sec/3600 ;
	  min  = (REAL_sec % 3600) / 60 ;
	  sec  = (REAL_sec % 3600) % 60 ;
	 //sec = REAL_sec ;
	  itoa10(hour, hourC) ;
	  itoa10(min, minC) ;
	  itoa10(sec, secC) ;
	  if(out>0) {//LCD Output
	  LCDclrscr();// LCD clear
	  LCDgotoxyint(0,0);	
	  LCDputs("Time=");
  LCDgotoxyint(0,1);	
	  LCDputs(hourC);

	  LCDputchar(':');
	  LCDputs(minC);
	  LCDputchar(':');
	  LCDputs(secC);
	  }
	  m_serialPutStr(minC);
	  m_serialPutChar(':');
	  m_serialPutStr(secC);
	  m_serialPutStr(" ");
	//  serialPutStr("\r\n");
	  commandsTimerSys();
}
void commandsTimer(void) { //REAL_sec
  commandsTimer00(1);//Output LCD
  m_serialPutStr("\r\n");
}

/**********************************************************************/

void commandsIDLE(void){
	m_serialPutStr("commandsIDLE is not support yet! \r\n");
	/***
	char s[10];
	int i;
	int nowp;
	// int j;
	m_serialPutStr("CPU usage (%) / 500ms Now= ");
	if(IDLE_timep > 0) nowp = IDLE_timep -1;
	else nowp = MAX_IDLE_TIME -1;
	itoax((CPU_MAX_CNT-IDLE_time[nowp])*100/CPU_MAX_CNT,s);//460: Max count(100%)
	m_serialPutStr(s);
	m_serialPutStr("%\r\n");
	//serialPutStr("% nowp=");
	//serialPutChar('a'+nowp);
	//serialPutStr("\r\n");

   m_serialPutStr("CPU usage (%) every 500msec: ");
   if(IDLE_cnt >= MAX_IDLE_TIME) {
   	for(i=IDLE_timep;i<MAX_IDLE_TIME;i++){
//	for(i=IDLE_timep;i<MAX_IDLE_TIME;i=i+2){
	//	if(IDLE_time[i] >=460)IDLE_time[i]=460;
		itoax((CPU_MAX_CNT-IDLE_time[i])*100/CPU_MAX_CNT,s);//460: Max count(100%)
//		itoax( (CPU_MAX_CNT*2-(IDLE_time[i]+IDLE_time[i+1]) )*100/CPU_MAX_CNT/2,s);//: CPU_MAX_CNT8500ms)

		m_serialPutStr(s);
		m_serialPutStr(" ");
	}
   }
	//serialPutStr("\r\n");
	if(IDLE_timep !=0) {
		for(i=0;i<IDLE_timep;i++){
	//			if(IDLE_time[i] >=460)IDLE_time[i]=460;
			itoax((CPU_MAX_CNT-IDLE_time[i])*100/CPU_MAX_CNT,s);//itoa is OK ??
//		itoax( (CPU_MAX_CNT*2-(IDLE_time[i]+IDLE_time[i+1]) )*100/CPU_MAX_CNT/2,s);//: CPU_MAX_CNT8500ms)
	//				serialPutChar('a'+i);// Debug
	//				serialPutStr(":");//Debug
			m_serialPutStr(s);
			m_serialPutStr(" ");
		}
	}	 
	m_serialPutStr("\r\n");	
	***/
}
/**********************************************************************
 *
 * Function:    commandsHelp
 *
 * Description: Help command function.
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/
void commandsHelp(void)
{
    int idx;

    /* Loop through each command in the table and send out the command
     * name to the serial port. */
    for (idx = 0; gCommandTable[idx].name != NULL; idx++)
    {
        m_serialPutStr(gCommandTable[idx].name);
        m_serialPutStr("\r\n");
    }
}

