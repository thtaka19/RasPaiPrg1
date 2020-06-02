/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tPutLogBCM283X_template.c => src/tPutLogBCM283X.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * Don't edit the comments between #[<...>]# and #[</...>]#
 * These comment are used by tecsmerege when merging.
 *
 * call port function #_TCPF_#
 * call port: cSIOPort signature: sSIOPort context:task
 *   void           cSIOPort_open( );
 *   void           cSIOPort_close( );
 *   bool_t         cSIOPort_putChar( char c );
 *   int_t          cSIOPort_getChar( );
 *   void           cSIOPort_enableCBR( uint_t cbrtn );
 *   void           cSIOPort_disableCBR( uint_t cbrtn );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tPutLogBCM283X_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# ePutLog
 * entry port: ePutLog
 * signature:  sPutLog
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# ePutLog_putChar
 * name:         ePutLog_putChar
 * global_name:  tPutLogBCM283X_ePutLog_putChar
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
ePutLog_putChar(char c)
{
}

/* #[<POSTAMBLE>]#
 *   Put non-entry functions below.
 * #[</POSTAMBLE>]#*/
