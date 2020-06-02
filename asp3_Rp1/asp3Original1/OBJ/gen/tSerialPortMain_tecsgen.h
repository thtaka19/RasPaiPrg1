/*
 * This file was automatically generated by tecsgen.
 * This file is not intended to be edited.
 */
#ifndef tSerialPortMain_TECSGEN_H
#define tSerialPortMain_TECSGEN_H

/*
 * celltype          :  tSerialPortMain
 * global name       :  tSerialPortMain
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  true
 * has_INIB          :  true
 * rom               :  yes
 * CB initializer    :  yes
 */

/* global header #_IGH_# */
#include "global_tecsgen.h"

/* signature header #_ISH_# */
#include "sSerialPort_tecsgen.h"
#include "snSerialPortManage_tecsgen.h"
#include "sSIOPort_tecsgen.h"
#include "siSIOCBR_tecsgen.h"
#include "sSemaphore_tecsgen.h"
#include "siSemaphore_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* cell INIB type definition #_CIP_# */
typedef const struct tag_tSerialPortMain_INIB {
    /* call port #_TCP_# */ 
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    uint_t         receiveBufferSize;
    uint_t         sendBufferSize;
    char*          receiveBuffer;
    char*          sendBuffer;
}  tSerialPortMain_INIB;
/* cell CB type definition #_CCTPA_# */
typedef struct tag_tSerialPortMain_CB {
    tSerialPortMain_INIB  *_inib;
    /* var #_VA_# */ 
    bool_t         openFlag;
    bool_t         errorFlag;
    uint_t         ioControl;
    uint_t         receiveReadPointer;
    uint_t         receiveWritePointer;
    uint_t         receiveCount;
    char           receiveFlowControl;
    bool_t         receiveStopped;
    uint_t         sendReadPointer;
    uint_t         sendWritePointer;
    uint_t         sendCount;
    bool_t         sendStopped;
}  tSerialPortMain_CB;
extern tSerialPortMain_CB  tSerialPortMain_CB_tab[];

/* celltype IDX type #_CTIX_# */
typedef struct tag_tSerialPortMain_CB *tSerialPortMain_IDX;

/* prototype declaration of entry port function #_EPP_# */
/* sSerialPort */
ER           tSerialPortMain_eSerialPort_open(tSerialPortMain_IDX idx);
ER           tSerialPortMain_eSerialPort_close(tSerialPortMain_IDX idx);
ER_UINT      tSerialPortMain_eSerialPort_read(tSerialPortMain_IDX idx, char* buffer, uint_t length);
ER_UINT      tSerialPortMain_eSerialPort_write(tSerialPortMain_IDX idx, const char* buffer, uint_t length);
ER           tSerialPortMain_eSerialPort_control(tSerialPortMain_IDX idx, uint_t ioControl);
ER           tSerialPortMain_eSerialPort_refer(tSerialPortMain_IDX idx, T_SERIAL_RPOR* pk_rpor);
/* snSerialPortManage */
bool_t       tSerialPortMain_enSerialPortManage_getChar(tSerialPortMain_IDX idx, char* p_char);
/* siSIOCBR */
void         tSerialPortMain_eiSIOCBR_readySend(tSerialPortMain_IDX idx);
void         tSerialPortMain_eiSIOCBR_readyReceive(tSerialPortMain_IDX idx);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* to get the definition of CB type of referenced celltype for optimization #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tSerialPortMain_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSIOPortBCM283XMain_tecsgen.h"
#include "tSemaphore_tecsgen.h"
#ifdef  tSerialPortMain_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tSerialPortMain_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define tSerialPortMain_ID_BASE        (1)  /* ID Base  #_NIDB_# */
#define tSerialPortMain_N_CELL        (1)  /*  number of cells  #_NCEL_# */

/* IDX validation macro #_CVI_# */
#define tSerialPortMain_VALID_IDX(IDX) (1)


/* celll CB macro #_GCB_# */
#define tSerialPortMain_GET_CELLCB(idx) (idx)

/* attr access  #_AAM_# */
#define tSerialPortMain_ATTR_receiveBufferSize( p_that )	((p_that)->_inib->receiveBufferSize)
#define tSerialPortMain_ATTR_sendBufferSize( p_that )	((p_that)->_inib->sendBufferSize)

#define tSerialPortMain_GET_receiveBufferSize(p_that)	((p_that)->_inib->receiveBufferSize)
#define tSerialPortMain_GET_sendBufferSize(p_that)	((p_that)->_inib->sendBufferSize)


/* var access macro #_VAM_# */
#define tSerialPortMain_VAR_openFlag(p_that)	((p_that)->openFlag)
#define tSerialPortMain_VAR_errorFlag(p_that)	((p_that)->errorFlag)
#define tSerialPortMain_VAR_ioControl(p_that)	((p_that)->ioControl)
#define tSerialPortMain_VAR_receiveBuffer(p_that)	((p_that)->_inib->receiveBuffer)
#define tSerialPortMain_VAR_receiveReadPointer(p_that)	((p_that)->receiveReadPointer)
#define tSerialPortMain_VAR_receiveWritePointer(p_that)	((p_that)->receiveWritePointer)
#define tSerialPortMain_VAR_receiveCount(p_that)	((p_that)->receiveCount)
#define tSerialPortMain_VAR_receiveFlowControl(p_that)	((p_that)->receiveFlowControl)
#define tSerialPortMain_VAR_receiveStopped(p_that)	((p_that)->receiveStopped)
#define tSerialPortMain_VAR_sendBuffer(p_that)	((p_that)->_inib->sendBuffer)
#define tSerialPortMain_VAR_sendReadPointer(p_that)	((p_that)->sendReadPointer)
#define tSerialPortMain_VAR_sendWritePointer(p_that)	((p_that)->sendWritePointer)
#define tSerialPortMain_VAR_sendCount(p_that)	((p_that)->sendCount)
#define tSerialPortMain_VAR_sendStopped(p_that)	((p_that)->sendStopped)

#define tSerialPortMain_GET_openFlag(p_that)	((p_that)->openFlag)
#define tSerialPortMain_SET_openFlag(p_that,val)	((p_that)->openFlag=(val))
#define tSerialPortMain_GET_errorFlag(p_that)	((p_that)->errorFlag)
#define tSerialPortMain_SET_errorFlag(p_that,val)	((p_that)->errorFlag=(val))
#define tSerialPortMain_GET_ioControl(p_that)	((p_that)->ioControl)
#define tSerialPortMain_SET_ioControl(p_that,val)	((p_that)->ioControl=(val))
#define tSerialPortMain_GET_receiveBuffer(p_that)	((p_that)->receiveBuffer)
#define tSerialPortMain_SET_receiveBuffer(p_that,val)	((p_that)->receiveBuffer=(val))
#define tSerialPortMain_GET_receiveReadPointer(p_that)	((p_that)->receiveReadPointer)
#define tSerialPortMain_SET_receiveReadPointer(p_that,val)	((p_that)->receiveReadPointer=(val))
#define tSerialPortMain_GET_receiveWritePointer(p_that)	((p_that)->receiveWritePointer)
#define tSerialPortMain_SET_receiveWritePointer(p_that,val)	((p_that)->receiveWritePointer=(val))
#define tSerialPortMain_GET_receiveCount(p_that)	((p_that)->receiveCount)
#define tSerialPortMain_SET_receiveCount(p_that,val)	((p_that)->receiveCount=(val))
#define tSerialPortMain_GET_receiveFlowControl(p_that)	((p_that)->receiveFlowControl)
#define tSerialPortMain_SET_receiveFlowControl(p_that,val)	((p_that)->receiveFlowControl=(val))
#define tSerialPortMain_GET_receiveStopped(p_that)	((p_that)->receiveStopped)
#define tSerialPortMain_SET_receiveStopped(p_that,val)	((p_that)->receiveStopped=(val))
#define tSerialPortMain_GET_sendBuffer(p_that)	((p_that)->sendBuffer)
#define tSerialPortMain_SET_sendBuffer(p_that,val)	((p_that)->sendBuffer=(val))
#define tSerialPortMain_GET_sendReadPointer(p_that)	((p_that)->sendReadPointer)
#define tSerialPortMain_SET_sendReadPointer(p_that,val)	((p_that)->sendReadPointer=(val))
#define tSerialPortMain_GET_sendWritePointer(p_that)	((p_that)->sendWritePointer)
#define tSerialPortMain_SET_sendWritePointer(p_that,val)	((p_that)->sendWritePointer=(val))
#define tSerialPortMain_GET_sendCount(p_that)	((p_that)->sendCount)
#define tSerialPortMain_SET_sendCount(p_that,val)	((p_that)->sendCount=(val))
#define tSerialPortMain_GET_sendStopped(p_that)	((p_that)->sendStopped)
#define tSerialPortMain_SET_sendStopped(p_that,val)	((p_that)->sendStopped=(val))

 /* call port function macro #_CPM_# */
#define tSerialPortMain_cSIOPort_open( p_that ) \
	  tSIOPortBCM283XMain_eSIOPort_open( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tSerialPortMain_cSIOPort_close( p_that ) \
	  tSIOPortBCM283XMain_eSIOPort_close( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tSerialPortMain_cSIOPort_putChar( p_that, c ) \
	  tSIOPortBCM283XMain_eSIOPort_putChar( \
	   (tSIOPortBCM283XMain_IDX)0, (c) )
#define tSerialPortMain_cSIOPort_getChar( p_that ) \
	  tSIOPortBCM283XMain_eSIOPort_getChar( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tSerialPortMain_cSIOPort_enableCBR( p_that, cbrtn ) \
	  tSIOPortBCM283XMain_eSIOPort_enableCBR( \
	   (tSIOPortBCM283XMain_IDX)0, (cbrtn) )
#define tSerialPortMain_cSIOPort_disableCBR( p_that, cbrtn ) \
	  tSIOPortBCM283XMain_eSIOPort_disableCBR( \
	   (tSIOPortBCM283XMain_IDX)0, (cbrtn) )
#define tSerialPortMain_cSendSemaphore_signal( p_that ) \
	  tSemaphore_eSemaphore_signal( \
	   &tSemaphore_CB_tab[1] )
#define tSerialPortMain_cSendSemaphore_wait( p_that ) \
	  tSemaphore_eSemaphore_wait( \
	   &tSemaphore_CB_tab[1] )
#define tSerialPortMain_cSendSemaphore_waitPolling( p_that ) \
	  tSemaphore_eSemaphore_waitPolling( \
	   &tSemaphore_CB_tab[1] )
#define tSerialPortMain_cSendSemaphore_waitTimeout( p_that, timeout ) \
	  tSemaphore_eSemaphore_waitTimeout( \
	   &tSemaphore_CB_tab[1], (timeout) )
#define tSerialPortMain_cSendSemaphore_initialize( p_that ) \
	  tSemaphore_eSemaphore_initialize( \
	   &tSemaphore_CB_tab[1] )
#define tSerialPortMain_cSendSemaphore_refer( p_that, pk_semaphoreStatus ) \
	  tSemaphore_eSemaphore_refer( \
	   &tSemaphore_CB_tab[1], (pk_semaphoreStatus) )
#define tSerialPortMain_ciSendSemaphore_signal( p_that ) \
	  tSemaphore_eiSemaphore_signal( \
	   &tSemaphore_CB_tab[1] )
#define tSerialPortMain_cReceiveSemaphore_signal( p_that ) \
	  tSemaphore_eSemaphore_signal( \
	   &tSemaphore_CB_tab[0] )
#define tSerialPortMain_cReceiveSemaphore_wait( p_that ) \
	  tSemaphore_eSemaphore_wait( \
	   &tSemaphore_CB_tab[0] )
#define tSerialPortMain_cReceiveSemaphore_waitPolling( p_that ) \
	  tSemaphore_eSemaphore_waitPolling( \
	   &tSemaphore_CB_tab[0] )
#define tSerialPortMain_cReceiveSemaphore_waitTimeout( p_that, timeout ) \
	  tSemaphore_eSemaphore_waitTimeout( \
	   &tSemaphore_CB_tab[0], (timeout) )
#define tSerialPortMain_cReceiveSemaphore_initialize( p_that ) \
	  tSemaphore_eSemaphore_initialize( \
	   &tSemaphore_CB_tab[0] )
#define tSerialPortMain_cReceiveSemaphore_refer( p_that, pk_semaphoreStatus ) \
	  tSemaphore_eSemaphore_refer( \
	   &tSemaphore_CB_tab[0], (pk_semaphoreStatus) )
#define tSerialPortMain_ciReceiveSemaphore_signal( p_that ) \
	  tSemaphore_eiSemaphore_signal( \
	   &tSemaphore_CB_tab[0] )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* prototype declaration of entry port function (referenced when VMT useless optimise enabled) #_EPSP_# */
/* eSerialPort */
ER             tSerialPortMain_eSerialPort_open_skel( const struct tag_sSerialPort_VDES *epd);
ER             tSerialPortMain_eSerialPort_close_skel( const struct tag_sSerialPort_VDES *epd);
ER_UINT        tSerialPortMain_eSerialPort_read_skel( const struct tag_sSerialPort_VDES *epd, char* buffer, uint_t length);
ER_UINT        tSerialPortMain_eSerialPort_write_skel( const struct tag_sSerialPort_VDES *epd, const char* buffer, uint_t length);
ER             tSerialPortMain_eSerialPort_control_skel( const struct tag_sSerialPort_VDES *epd, uint_t ioControl);
ER             tSerialPortMain_eSerialPort_refer_skel( const struct tag_sSerialPort_VDES *epd, T_SERIAL_RPOR* pk_rpor);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY

/* IDX validation macro (abbrev.) #_CVIA_# */
#define VALID_IDX(IDX)  tSerialPortMain_VALID_IDX(IDX)


/* cell CB macro (abbrev) #_GCBA_# */
#define GET_CELLCB(idx)  tSerialPortMain_GET_CELLCB(idx)

/* CELLCB type (abbrev) #_CCT_# */
#define CELLCB	tSerialPortMain_CB

/* celltype IDX type (abbrev) #_CTIXA_# */
#define CELLIDX	tSerialPortMain_IDX


/* attr access macro (abbrev) #_AAMA_# */
#define ATTR_receiveBufferSize tSerialPortMain_ATTR_receiveBufferSize( p_cellcb )
#define ATTR_sendBufferSize  tSerialPortMain_ATTR_sendBufferSize( p_cellcb )


/* var access macro (abbrev) #_VAMA_# */
#define VAR_openFlag         tSerialPortMain_VAR_openFlag( p_cellcb )
#define VAR_errorFlag        tSerialPortMain_VAR_errorFlag( p_cellcb )
#define VAR_ioControl        tSerialPortMain_VAR_ioControl( p_cellcb )
#define VAR_receiveBuffer    tSerialPortMain_VAR_receiveBuffer( p_cellcb )
#define VAR_receiveReadPointer tSerialPortMain_VAR_receiveReadPointer( p_cellcb )
#define VAR_receiveWritePointer tSerialPortMain_VAR_receiveWritePointer( p_cellcb )
#define VAR_receiveCount     tSerialPortMain_VAR_receiveCount( p_cellcb )
#define VAR_receiveFlowControl tSerialPortMain_VAR_receiveFlowControl( p_cellcb )
#define VAR_receiveStopped   tSerialPortMain_VAR_receiveStopped( p_cellcb )
#define VAR_sendBuffer       tSerialPortMain_VAR_sendBuffer( p_cellcb )
#define VAR_sendReadPointer  tSerialPortMain_VAR_sendReadPointer( p_cellcb )
#define VAR_sendWritePointer tSerialPortMain_VAR_sendWritePointer( p_cellcb )
#define VAR_sendCount        tSerialPortMain_VAR_sendCount( p_cellcb )
#define VAR_sendStopped      tSerialPortMain_VAR_sendStopped( p_cellcb )

/* call port function macro (abbrev) #_CPMA_# */
#define cSIOPort_open( ) \
                      ((void)p_cellcb, tSerialPortMain_cSIOPort_open( p_cellcb ))
#define cSIOPort_close( ) \
                      ((void)p_cellcb, tSerialPortMain_cSIOPort_close( p_cellcb ))
#define cSIOPort_putChar( c ) \
                      ((void)p_cellcb, tSerialPortMain_cSIOPort_putChar( p_cellcb, c ))
#define cSIOPort_getChar( ) \
                      ((void)p_cellcb, tSerialPortMain_cSIOPort_getChar( p_cellcb ))
#define cSIOPort_enableCBR( cbrtn ) \
                      ((void)p_cellcb, tSerialPortMain_cSIOPort_enableCBR( p_cellcb, cbrtn ))
#define cSIOPort_disableCBR( cbrtn ) \
                      ((void)p_cellcb, tSerialPortMain_cSIOPort_disableCBR( p_cellcb, cbrtn ))
#define cSendSemaphore_signal( ) \
                      ((void)p_cellcb, tSerialPortMain_cSendSemaphore_signal( p_cellcb ))
#define cSendSemaphore_wait( ) \
                      ((void)p_cellcb, tSerialPortMain_cSendSemaphore_wait( p_cellcb ))
#define cSendSemaphore_waitPolling( ) \
                      ((void)p_cellcb, tSerialPortMain_cSendSemaphore_waitPolling( p_cellcb ))
#define cSendSemaphore_waitTimeout( timeout ) \
                      ((void)p_cellcb, tSerialPortMain_cSendSemaphore_waitTimeout( p_cellcb, timeout ))
#define cSendSemaphore_initialize( ) \
                      ((void)p_cellcb, tSerialPortMain_cSendSemaphore_initialize( p_cellcb ))
#define cSendSemaphore_refer( pk_semaphoreStatus ) \
                      ((void)p_cellcb, tSerialPortMain_cSendSemaphore_refer( p_cellcb, pk_semaphoreStatus ))
#define ciSendSemaphore_signal( ) \
                      ((void)p_cellcb, tSerialPortMain_ciSendSemaphore_signal( p_cellcb ))
#define cReceiveSemaphore_signal( ) \
                      ((void)p_cellcb, tSerialPortMain_cReceiveSemaphore_signal( p_cellcb ))
#define cReceiveSemaphore_wait( ) \
                      ((void)p_cellcb, tSerialPortMain_cReceiveSemaphore_wait( p_cellcb ))
#define cReceiveSemaphore_waitPolling( ) \
                      ((void)p_cellcb, tSerialPortMain_cReceiveSemaphore_waitPolling( p_cellcb ))
#define cReceiveSemaphore_waitTimeout( timeout ) \
                      ((void)p_cellcb, tSerialPortMain_cReceiveSemaphore_waitTimeout( p_cellcb, timeout ))
#define cReceiveSemaphore_initialize( ) \
                      ((void)p_cellcb, tSerialPortMain_cReceiveSemaphore_initialize( p_cellcb ))
#define cReceiveSemaphore_refer( pk_semaphoreStatus ) \
                      ((void)p_cellcb, tSerialPortMain_cReceiveSemaphore_refer( p_cellcb, pk_semaphoreStatus ))
#define ciReceiveSemaphore_signal( ) \
                      ((void)p_cellcb, tSerialPortMain_ciReceiveSemaphore_signal( p_cellcb ))


/* entry port function macro (abbrev) #_EPM_# */
#define eSerialPort_open tSerialPortMain_eSerialPort_open
#define eSerialPort_close tSerialPortMain_eSerialPort_close
#define eSerialPort_read tSerialPortMain_eSerialPort_read
#define eSerialPort_write tSerialPortMain_eSerialPort_write
#define eSerialPort_control tSerialPortMain_eSerialPort_control
#define eSerialPort_refer tSerialPortMain_eSerialPort_refer
#define enSerialPortManage_getChar tSerialPortMain_enSerialPortManage_getChar
#define eiSIOCBR_readySend tSerialPortMain_eiSIOCBR_readySend
#define eiSIOCBR_readyReceive tSerialPortMain_eiSIOCBR_readyReceive

/* iteration code (FOREACH_CELL) #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tSerialPortMain_N_CELL; (i)++ ){ \
       (p_cb) = &tSerialPortMain_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB initialize macro #_CIM_# */
#define INITIALIZE_CB(p_that)\
	(p_that)->openFlag = false;
#define SET_CB_INIB_POINTER(i,p_that)\
	(p_that)->_inib = &tSerialPortMain_INIB_tab[(i)];

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tSerialPortMain_TECSGENH */
