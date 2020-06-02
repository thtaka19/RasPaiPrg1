/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tSIOPortBCM283XMain_TECSGEN_H
#define tSIOPortBCM283XMain_TECSGEN_H

/*
 * celltype          :  tSIOPortBCM283XMain
 * global name       :  tSIOPortBCM283XMain
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 * CB initializer    :  no
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sSIOPort_tecsgen.h"
#include "siSIOCBR_tecsgen.h"
#include "sInterruptRequest_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tSIOPortBCM283XMain_CB {
    int  dummy;
} tSIOPortBCM283XMain_CB;
extern tSIOPortBCM283XMain_CB  tSIOPortBCM283XMain_CB_tab[];

/* セルタイプのIDX型 #_CTIX_# */
typedef int   tSIOPortBCM283XMain_IDX;

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sSIOPort */
Inline void         tSIOPortBCM283XMain_eSIOPort_open(tSIOPortBCM283XMain_IDX idx);
Inline void         tSIOPortBCM283XMain_eSIOPort_close(tSIOPortBCM283XMain_IDX idx);
Inline bool_t       tSIOPortBCM283XMain_eSIOPort_putChar(tSIOPortBCM283XMain_IDX idx, char c);
Inline int_t        tSIOPortBCM283XMain_eSIOPort_getChar(tSIOPortBCM283XMain_IDX idx);
Inline void         tSIOPortBCM283XMain_eSIOPort_enableCBR(tSIOPortBCM283XMain_IDX idx, uint_t cbrtn);
Inline void         tSIOPortBCM283XMain_eSIOPort_disableCBR(tSIOPortBCM283XMain_IDX idx, uint_t cbrtn);
/* siSIOCBR */
Inline void         tSIOPortBCM283XMain_eiSIOCBR_readySend(tSIOPortBCM283XMain_IDX idx);
Inline void         tSIOPortBCM283XMain_eiSIOCBR_readyReceive(tSIOPortBCM283XMain_IDX idx);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tSIOPortBCM283XMain_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSerialPortMain_tecsgen.h"
#include "tUART_tecsgen.h"
#include "tInterruptRequest_tecsgen.h"
#ifdef  tSIOPortBCM283XMain_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tSIOPortBCM283XMain_CB_TYPE_ONLY */
#define tSIOPortBCM283XMain_ID_BASE        (1)  /* ID のベース  #_NIDB_# */
#define tSIOPortBCM283XMain_N_CELL        (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tSIOPortBCM283XMain_VALID_IDX(IDX) (1)

/* optional 呼び口をテストするマクロ #_TOCP_# */
#define tSIOPortBCM283XMain_is_ciSIOCBR_joined(p_that) \
	  (1)

/* セルCBを得るマクロ #_GCB_# */
#define tSIOPortBCM283XMain_GET_CELLCB(idx) ((void *)0)
 /* 呼び口関数マクロ #_CPM_# */
#define tSIOPortBCM283XMain_ciSIOCBR_readySend( p_that ) \
	  tSerialPortMain_eiSIOCBR_readySend( \
	   &tSerialPortMain_CB_tab[0] )
#define tSIOPortBCM283XMain_ciSIOCBR_readyReceive( p_that ) \
	  tSerialPortMain_eiSIOCBR_readyReceive( \
	   &tSerialPortMain_CB_tab[0] )
#define tSIOPortBCM283XMain_cSIOPort_open( p_that ) \
	  tUART_eSIOPort_open( \
	   &tUART_CB_tab[0] )
#define tSIOPortBCM283XMain_cSIOPort_close( p_that ) \
	  tUART_eSIOPort_close( \
	   &tUART_CB_tab[0] )
#define tSIOPortBCM283XMain_cSIOPort_putChar( p_that, c ) \
	  tUART_eSIOPort_putChar( \
	   &tUART_CB_tab[0], (c) )
#define tSIOPortBCM283XMain_cSIOPort_getChar( p_that ) \
	  tUART_eSIOPort_getChar( \
	   &tUART_CB_tab[0] )
#define tSIOPortBCM283XMain_cSIOPort_enableCBR( p_that, cbrtn ) \
	  tUART_eSIOPort_enableCBR( \
	   &tUART_CB_tab[0], (cbrtn) )
#define tSIOPortBCM283XMain_cSIOPort_disableCBR( p_that, cbrtn ) \
	  tUART_eSIOPort_disableCBR( \
	   &tUART_CB_tab[0], (cbrtn) )
#define tSIOPortBCM283XMain_cInterruptRequest_disable( p_that ) \
	  tInterruptRequest_eInterruptRequest_disable( \
	   &tInterruptRequest_CB_tab[0] )
#define tSIOPortBCM283XMain_cInterruptRequest_enable( p_that ) \
	  tInterruptRequest_eInterruptRequest_enable( \
	   &tInterruptRequest_CB_tab[0] )

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tSIOPortBCM283XMain_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tSIOPortBCM283XMain_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tSIOPortBCM283XMain_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tSIOPortBCM283XMain_IDX

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define ciSIOCBR_readySend( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_ciSIOCBR_readySend( p_cellcb ))
#define ciSIOCBR_readyReceive( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_ciSIOCBR_readyReceive( p_cellcb ))
#define cSIOPort_open( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cSIOPort_open( p_cellcb ))
#define cSIOPort_close( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cSIOPort_close( p_cellcb ))
#define cSIOPort_putChar( c ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cSIOPort_putChar( p_cellcb, c ))
#define cSIOPort_getChar( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cSIOPort_getChar( p_cellcb ))
#define cSIOPort_enableCBR( cbrtn ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cSIOPort_enableCBR( p_cellcb, cbrtn ))
#define cSIOPort_disableCBR( cbrtn ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cSIOPort_disableCBR( p_cellcb, cbrtn ))
#define cInterruptRequest_disable( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cInterruptRequest_disable( p_cellcb ))
#define cInterruptRequest_enable( ) \
                      ((void)p_cellcb, tSIOPortBCM283XMain_cInterruptRequest_enable( p_cellcb ))

/* optional 呼び口をテストするマクロ（短縮形） #_TOCPA_# */
#define is_ciSIOCBR_joined()\
		tSIOPortBCM283XMain_is_ciSIOCBR_joined(p_cellcb)

/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eSIOPort_open    tSIOPortBCM283XMain_eSIOPort_open
#define eSIOPort_close   tSIOPortBCM283XMain_eSIOPort_close
#define eSIOPort_putChar tSIOPortBCM283XMain_eSIOPort_putChar
#define eSIOPort_getChar tSIOPortBCM283XMain_eSIOPort_getChar
#define eSIOPort_enableCBR tSIOPortBCM283XMain_eSIOPort_enableCBR
#define eSIOPort_disableCBR tSIOPortBCM283XMain_eSIOPort_disableCBR
#define eiSIOCBR_readySend tSIOPortBCM283XMain_eiSIOCBR_readySend
#define eiSIOCBR_readyReceive tSIOPortBCM283XMain_eiSIOCBR_readyReceive

/* イテレータコード (FOREACH_CELL)の生成(CB,INIB は存在しない) #_NFEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for((i)=0;(i)<0;(i)++){

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#ifndef TOPPERS_MACRO_ONLY

/* inline ヘッダの include #_INL_# */
#include "tSIOPortBCM283XMain_inline.h"

#endif /* TOPPERS_MACRO_ONLY */

#ifdef TOPPERS_CB_TYPE_ONLY

/* inline のための undef #_UDF_# */
#undef VALID_IDX
#undef GET_CELLCB
#undef CELLCB
#undef CELLIDX
#undef tSIOPortBCM283XMain_IDX
#undef FOREACH_CELL
#undef END_FOREACH_CELL
#undef INITIALIZE_CB
#undef SET_CB_INIB_POINTER
#undef is_ciSIOCBR_joined
#undef tSIOPortBCM283XMain_ciSIOCBR_readySend
#undef ciSIOCBR_readySend
#undef tSIOPortBCM283XMain_ciSIOCBR_readyReceive
#undef ciSIOCBR_readyReceive
#undef tSIOPortBCM283XMain_cSIOPort_open
#undef cSIOPort_open
#undef tSIOPortBCM283XMain_cSIOPort_close
#undef cSIOPort_close
#undef tSIOPortBCM283XMain_cSIOPort_putChar
#undef cSIOPort_putChar
#undef tSIOPortBCM283XMain_cSIOPort_getChar
#undef cSIOPort_getChar
#undef tSIOPortBCM283XMain_cSIOPort_enableCBR
#undef cSIOPort_enableCBR
#undef tSIOPortBCM283XMain_cSIOPort_disableCBR
#undef cSIOPort_disableCBR
#undef tSIOPortBCM283XMain_cInterruptRequest_disable
#undef cInterruptRequest_disable
#undef tSIOPortBCM283XMain_cInterruptRequest_enable
#undef cInterruptRequest_enable
#undef eSIOPort_open
#undef eSIOPort_close
#undef eSIOPort_putChar
#undef eSIOPort_getChar
#undef eSIOPort_enableCBR
#undef eSIOPort_disableCBR
#undef eiSIOCBR_readySend
#undef eiSIOCBR_readyReceive
#endif /* TOPPERS_CB_TYPE_ONLY */

#endif /* tSIOPortBCM283XMain_TECSGENH */
