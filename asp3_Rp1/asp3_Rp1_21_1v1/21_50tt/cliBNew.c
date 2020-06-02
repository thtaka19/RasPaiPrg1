/**********************************************************************
 *
 * Filename:    cliB.c  for 21_70
 * 
 * Description: Command line interface module.
 *
 * Notes:       
 **********************************************************************/

//#include <string.h>
//#include "stdint.h"
//#include "viperlite.h"
#include "definesN00.h"

//#include "serial.h"
#include "mailbox.h"
#include "commands.h"
#include "cli.h"
#include "../cmn00/mini_serial.h"

#define MAX_COMMAND_LEN             (20)
#define COMMAND_TABLE_SIZE          (15)

#define TO_UPPER(x)                 (((x >= 'a') && (x <= 'z')) ? ((x) - ('a' - 'A')) : (x))

void commandsLcdData0(void);
void commandsSwMl(void);
void commandsTempMl(void);
void commandsTimerMl(void);
void commandsIDLE(void);
void commandsAll(void);
command_t const gCommandTable[COMMAND_TABLE_SIZE] = 
{
    {"HELP",    commandsHelp,},
    {"LED",     commandsLed, },
    {"BUZZER",  commandsBuzzer, },
	{"LCDH", commandsLcdHello, },	
	{"CLR",  commandsLcdCler, },
	{"SW",  commandsSwMl, },	

	{"TEMP",  commandsTempMl, },
	{"TIMER", commandsTimerMl, },	
	{"IDLE", commandsIDLE, },

//	{"SW",  commandsSw, },	
//	{"TEMP",  commandsTemp, },
	{"ALL",  commandsAll, },	
	{"LCD", commandsLcdData0, },

    {NULL,      NULL }
};
extern void mboxPutChar(char );
extern char* mboxGetStr(void );
static char gCommandBuffer[MAX_COMMAND_LEN + 1];
static char gDataBuffer[MAX_COMMAND_LEN + 1];

/**********************************************************************
 *
 * Function:    cliBuildCommand
 *
 * Description: Put received characters into the command buffer. Once
 *              a complete command is received return TRUE.
 * Returns:     TRUE if a command is complete, otherwise FALSE.
 *
 **********************************************************************/

    void separateData() {
	 int i,j,id ;
	 gDataBuffer[0] = '\0';
	 for(i=0;(i<MAX_COMMAND_LEN)&& (gCommandBuffer[i] != '\0');i++){
		if( gCommandBuffer[i] == '='){
			gCommandBuffer[i] = '\0' ;
			for(id=0;((i+id+1)< MAX_COMMAND_LEN)&& (gCommandBuffer[i+id+1] != '\0') ;id++) {
			  gDataBuffer[id] = gCommandBuffer[i+id+1];
			}
			gDataBuffer[id] = '\0';
			break;
		};
	 }
	 for(i=0,j=0;(i<MAX_COMMAND_LEN)&& (gCommandBuffer[i] != '\0');i++){ 	// backspace			 
	     if((gCommandBuffer[i]== '\b') && (j>0)){ j=j-1; }
		 else {  gCommandBuffer[j++] = TO_UPPER(gCommandBuffer[i]);	 }
	 }
	 gCommandBuffer[j] = '\0' ;	
 }
 
	 
	 
//******************************************************************** 
 int cliBuildCommand(char nextChar)
{
    static uint8_t idx = 0;

    /* Don't store any new line characters or spaces. */
    if ((nextChar == '\n') || (nextChar == ' ') || (nextChar == '\t'))
        return FALSE;

    /* The completed command has been received. Replace the final carriage
     * return character with a NULL character to help with processing the
     * command. */
    if (nextChar == '\r')
    {
        gCommandBuffer[idx] = '\0';
        idx = 0;
		separateData();
        return TRUE;
    }

    /* Convert the incoming character to upper case. This matches the case
     * of commands in the command table. Then store the received character
     * in the command buffer. */
    gCommandBuffer[idx] = TO_UPPER(nextChar);
    idx++;

    /* If the command is too long, reset the index and process
     * the current command buffer. */
    if (idx > MAX_COMMAND_LEN)
    {
        idx = 0;
		separateData();
        return TRUE;
    }

    return FALSE;
}
 /*********************************************************************/

/**************** strcmp **************************************************/
int strcmp0(const char *s1, const char *s2)
{
  while (*s1 || *s2) {
    if (*s1 != *s2)
      return (*s1 > *s2) ? 1 : -1;
    s1++;
    s2++;
  }
  return 0;
}

/**********************************************************************
 *
 * Function:    cliProcessCommand
 *
 * Description: Look up the command in the command table. If the
 *              command is found, call the command's function. If the
 *              command is not found, output an error message.
 *
 * Notes:       
 *
 * Returns:     None.
 *
 **********************************************************************/
void cliProcessCommand(void)
{
    int bCommandFound = FALSE;
    int idx;

    /* Search for the command in the command table until it is found or
     * the end of the table is reached. If the command is found, break
     * out of the loop. */
    for (idx = 0; gCommandTable[idx].name != NULL; idx++)
    {
        if (strcmp0(gCommandTable[idx].name, gCommandBuffer) == 0)
        {
            bCommandFound = TRUE;
			
			//m_serialPutStr("\r\nCommand found.\r\n Command=");//Debug
			m_serialPutStr("\r\n Command=");//Debug
			m_serialPutStr(gCommandBuffer);
			m_serialPutStr("\r\n");
			
			
		    break;
        }
    }

    /* If the command was found, call the command function. Otherwise,
     * output an error message. */
    if (bCommandFound == TRUE)
    {
        m_serialPutStr("\r\n");
		if(idx < 15) 
			{				
        (*gCommandTable[idx].function)();
			}
		else {

			}
    }
    else
	{   m_serialPutStr("\r\nCommand not found.\r\n Command=");
	m_serialPutStr(gCommandBuffer);
	m_serialPutStr("\r\n Data=");
	m_serialPutStr(gDataBuffer);
	m_serialPutStr("\r\n");
	}
}

void commandsLcdData0(void) {
	commandsLcdData(gDataBuffer);
}
void commandsSwMl(void){
	//int i ;
	
	mboxPutChar('1');
	
}
void commandsTempMl(void){ 
	mboxPutChar('2');	
}
void commandsTimerMl(void){ 
	mboxPutChar('3');	
}
void commandsAll(void) {
m_serialPutStr("Command All\r\n");
m_serialPutStr("LcdCler,Led,Buzzer,LcdHello,Sw,Temp,Timer,IDLE,LCD=777,Help\r\n");
 commandsLcdCler();
// commandsHelp();
commandsLed();
 commandsBuzzer();
commandsLcdHello();
commandsSwMl();
commandsTempMl();
commandsTimerMl();
commandsIDLE();
commandsLcdData("777");
 commandsHelp();
}



