/**********************************************************************
 *
 * Filename:    mailbox API.c
 * 
 * Description: ITRON  mailbox program.
 *
 * Notes:       
 *
 * 
 *
 **********************************************************************/
//#include <stdio.h>
//#include "itron.h"

//#include "kernel.h"
//#include "kernel_id.h"
#include <kernel.h>
#include "kernel_cfg.h"
//#include "serial.h"
#include "mailboxApi.h"
#include "../cmn00/mini_serial.h"
#define  Sci_PutChar    m_serialPutChar

/* Declare the task variables. */

typedef struct
{
 // T_MSG  pk_msg;    /* For OS Area */
  int    size;      /* Message Size */
  ID    dtqid;        /* Message send Task ID */
  char  buf[64];    /* Message Buffer */
} MESSAGE,*MESSAGEptr;


 static MESSAGE  msgs;
 static MESSAGEptr mpts= &msgs;	

/**********************************************************************
 *
 * Function:    producerTask
 *
 * Description: This task monitors button SW0. Once pressed, the button
 *              is debounced and a message is sent to the waiting
 *              consumer task.
 *
 * Notes:       This function is specific to the Arcom board. 
 *
 * Returns:     None.
 *
 **********************************************************************/ 
//void makeMsg(MESSAGE , char[]) ;

//void appli(VP_INT exinf)
void makeMsgXX( MESSAGEptr mpt,char msgBody[]) 
{
//MESSAGE msg ;
//  ID    tid;
int i=0;
mpt->buf[0]=msgBody[0];
for(i=1;i<64;i++){
 if(msgBody[i]<=0) break;
 mpt->buf[i]=msgBody[i];
}
//msgBody[i]='\0' ;
msgBody[i]=0;
mpt->size = i+1;


Sci_PutChar(mpt->buf[0]);
Sci_PutChar('\r');
Sci_PutChar('\n');

return ;
}

//  ****************
ER_UINT	ercd;
	intptr_t	data;
 char  mCmd[4]="X";
void mboxPutChar(char cmd){
 //MESSAGE  msgs;
 //MESSAGEptr mpts= &msgs;	
// char  mCmd[4]="X";
 
 mCmd[0]= cmd;
// makeMsg(mpts,mCmd); 
// snd_mbx(MAILBOX1, (T_MSG *)&msgs );  // Send Mail Message 
// serialPutChar(mpts -> buf[0]);
ercd = snd_dtq(DTQ1, (intptr_t)mCmd);	
m_serialPutChar(mCmd[0]);
 m_serialPutStr( "Send to data Q \r\n");// Debug
//cyg_mbox_put(mailboxHdl, (void *)(mCmd));
}

char * mboxGetStr(void){
 //MESSAGE  msgs;
 //MESSAGEptr mpts= &msgs;	
 char * mCmdp;
 char  mCmd[4]="X";

 ercd = rcv_dtq(DTQ1, &data);
//	msgp= msg -> buf ;
mCmdp=(char *)data;
mCmd[0]= *mCmdp;mCmdp++;
mCmd[1]= *mCmdp;mCmdp++;
mCmd[2]= *mCmdp;

// makeMsg(mpts,mCmd); 
// snd_mbx(MAILBOX1, (T_MSG *)&msgs );  // Send Mail Message 
// serialPutChar(mpts -> buf[0]);

m_serialPutStr(mCmd);
 m_serialPutStr( " Rcv from data Q \r\n");// Debug
//cyg_mbox_put(mailboxHdl, (void *)(mCmd));
 return  &mCmd[0];
}
void mboxPutCharX(char cmd){
 //MESSAGE  msgs;
 //MESSAGEptr mpts= &msgs;	
 char mCmd[2]="X";
 
 mCmd[0]= cmd;
 makeMsgXX(mpts,mCmd); 
 //snd_mbx(MAILBOX1, (T_MSG *)&msgs );  // Send Mail Message 
 m_serialPutChar(mpts -> buf[0]);
 m_serialPutStr( "Send to MailBox \r\n");// Debug
//cyg_mbox_put(mailboxHdl, (void *)(mCmd));
}

char * mboxGetStrX(void){
 MESSAGE  *msgr;
 char *ptrC ;
 m_serialPutStr("Wait to Receive from MailBox \r\n");
 //rcv_mbx(MAILBOX1, (T_MSG **)&msgr );// Get Mail Message	
 ptrC= msgr -> buf ;
 m_serialPutChar(*ptrC);
 m_serialPutStr( "Received from MailBox \r\n");// Debug
 return  ptrC;
}
