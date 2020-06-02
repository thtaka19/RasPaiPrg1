/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tSysLog_template.c => src/tSysLog.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * Don't edit the comments between #[<...>]# and #[</...>]#
 * These comment are used by tecsmerege when merging.
 *
 * attr access macro #_CAAM_#
 * logBufferSize    uint_t           ATTR_logBufferSize
 * initLogMask      uint_t           ATTR_initLogMask
 * initLowMask      uint_t           ATTR_initLowMask
 * logBuffer        SYSLOG*          VAR_logBuffer   
 * count            uint_t           VAR_count       
 * head             uint_t           VAR_head        
 * tail             uint_t           VAR_tail        
 * lost             uint_t           VAR_lost        
 * logMask          uint_t           VAR_logMask     
 * lowMask          uint_t           VAR_lowMask     
 *
 * call port function #_TCPF_#
 * call port: cPutLog signature: sPutLog context:task
 *   void           cPutLog_putChar( char c );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tSysLog_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eSysLog
 * entry port: eSysLog
 * signature:  sSysLog
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eSysLog_write
 * name:         eSysLog_write
 * global_name:  tSysLog_eSysLog_write
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eSysLog_write(uint_t priority, const SYSLOG* p_syslog)
{
}

/* #[<ENTRY_FUNC>]# eSysLog_read
 * name:         eSysLog_read
 * global_name:  tSysLog_eSysLog_read
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER_UINT
eSysLog_read(SYSLOG* p_syslog)
{
}

/* #[<ENTRY_FUNC>]# eSysLog_mask
 * name:         eSysLog_mask
 * global_name:  tSysLog_eSysLog_mask
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eSysLog_mask(uint_t logMask, uint_t lowMask)
{
}

/* #[<ENTRY_FUNC>]# eSysLog_refer
 * name:         eSysLog_refer
 * global_name:  tSysLog_eSysLog_refer
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eSysLog_refer(T_SYSLOG_RLOG* pk_rlog)
{
}

/* #[<ENTRY_FUNC>]# eSysLog_flush
 * name:         eSysLog_flush
 * global_name:  tSysLog_eSysLog_flush
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eSysLog_flush()
{
}

/* #[<POSTAMBLE>]#
 *   Put non-entry functions below.
 * #[</POSTAMBLE>]#*/
