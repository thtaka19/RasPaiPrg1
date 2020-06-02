/**********************************************************************
 *
 * Filename:    mailbox.c
 * 
 * Description: ITRON mailbox program.
 *
 * Notes:         
 *
 **********************************************************************/
//#include "kernel.h"
#include <kernel.h>
#include "kernel_cfg.h"
//nclude <cyg/kernel/kapi.h>
//nclude <cyg/infra/diag.h>
//#include "definesN00.h"

//#include "../cmn00/button.h"
//#include "../cmn00/led.h"
#include "commands.h"
//#include "../cmn00/serial.h"
#include "../cmn00/mini_serial.h"
#include "mailbox.h"


/**********************************************************************
 *
 * Function:    processTask4
 *
 * Description: This task waits for a message from the producer task.
 *              Once the message is received via the mailbox, it
 *              outputs a message and toggles the green LED.
 * Returns:     None.
 *
 **********************************************************************/ 
//void processTask4(cyg_addrword_t data)

void processTask4(intptr_t exinf)
{
    //uint32_t rcvMsg;
	char * msgp ;
	
     //unsigned  int ledcnt=0;
    while (1)
    {
        /* Wait for a new message. */
      //  rcvMsg = (uint32_t)cyg_mbox_get(mailboxHdl);

      //  diag_printf("Button SW0 pressed %d times.\n", rcvMsg);
		
	//	msgp = (char *)cyg_mbox_get(mailbox1Hdl);
msgp = (char *)mboxGetStr();	
	//	diag_printf("MailBox Msg= %s.\n", msgp);
		
		if(*msgp == '1'){
		  commandsSw();	
		} else if (*msgp == '2'){
		  commandsTemp();
		} else if (*msgp == '3'){
		   //serialPutStr("\r\n Timer Command not yet... MailBox \r\n Command=");	
		   commandsTimer();
		} else  {
		  m_serialPutStr("\r\nCommand not found. MailBox \r\n Command=");
		  m_serialPutStr(msgp);
		  m_serialPutStr("\r\n ");	
		}		
        //ledToggle( );
    }
}


