/*
 * This file was automatically generated by tecsgen.
 * This file is not intended to be edited.
 */
#include "tSysLog_tecsgen.h"
#include "tSysLog_factory.h"

/* entry port descriptor type #_EDT_# */
/* eSysLog : omitted by entry port optimize */

/* entry port skelton function #_EPSF_# */
/* eSysLog : omitted by entry port optimize */

/* entry port skelton function table #_EPSFT_# */
/* eSysLog : omitted by entry port optimize */

/* entry port descriptor referenced by call port (differ from actual definition) #_CPEPD_# */

/* call port array #_CPA_# */

/* array of attr/var #_AVAI_# */
SYSLOG tSysLog_SINGLE_CELL_CB_logBuffer_INIT[32];
/* cell INIB #_INIB_# */
tSysLog_INIB tSysLog_SINGLE_CELL_INIB = 
{
    /* call port #_CP_# */ 
    /* entry port #_EP_# */ 
    /* attribute(RO) */ 
    32,                                      /* logBufferSize */
    LOG_UPTO(LOG_NOTICE),                    /* initLogMask */
    LOG_UPTO(LOG_EMERG),                     /* initLowMask */
    tSysLog_SINGLE_CELL_CB_logBuffer_INIT,   /* logBuffer */
};

/* cell CB #_CB_# */
struct tag_tSysLog_CB tSysLog_SINGLE_CELL_CB;
/* entry port descriptor #_EPD_# */
/* eSysLog : omitted by entry port optimize */
/* CB initialize code #_CIC_# */
void
tSysLog_CB_initialize()
{
    SET_CB_INIB_POINTER(i,p_cb)
    INITIALIZE_CB()
}
