/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tPutLogBCM283X_TECSGEN_H
#define tPutLogBCM283X_TECSGEN_H

/*
 * celltype          :  tPutLogBCM283X
 * global name       :  tPutLogBCM283X
 * idx_is_id(actual) :  no(no)
 * singleton         :  yes
 * has_CB            :  false
 * has_INIB          :  false
 * rom               :  yes
 * CB initializer    :  no
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sPutLog_tecsgen.h"
#include "sSIOPort_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル CB (ダミー)型宣言 #_CCDP_# */
typedef struct tag_tPutLogBCM283X_CB {
    int  dummy;
} tPutLogBCM283X_CB;
/* シングルトンセル CB プロトタイプ宣言 #_SCP_# */


/* セルタイプのIDX型 #_CTIX_# */
typedef int   tPutLogBCM283X_IDX;

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sPutLog */
void         tPutLogBCM283X_ePutLog_putChar( char c);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tPutLogBCM283X_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSIOPortBCM283XMain_tecsgen.h"
#ifdef  tPutLogBCM283X_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tPutLogBCM283X_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ #_GCB_# */
#define tPutLogBCM283X_GET_CELLCB(idx) ((void *)0)
 /* 呼び口関数マクロ #_CPM_# */
#define tPutLogBCM283X_cSIOPort_open( ) \
	  tSIOPortBCM283XMain_eSIOPort_open( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tPutLogBCM283X_cSIOPort_close( ) \
	  tSIOPortBCM283XMain_eSIOPort_close( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tPutLogBCM283X_cSIOPort_putChar( c ) \
	  tSIOPortBCM283XMain_eSIOPort_putChar( \
	   (tSIOPortBCM283XMain_IDX)0, (c) )
#define tPutLogBCM283X_cSIOPort_getChar( ) \
	  tSIOPortBCM283XMain_eSIOPort_getChar( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tPutLogBCM283X_cSIOPort_enableCBR( cbrtn ) \
	  tSIOPortBCM283XMain_eSIOPort_enableCBR( \
	   (tSIOPortBCM283XMain_IDX)0, (cbrtn) )
#define tPutLogBCM283X_cSIOPort_disableCBR( cbrtn ) \
	  tSIOPortBCM283XMain_eSIOPort_disableCBR( \
	   (tSIOPortBCM283XMain_IDX)0, (cbrtn) )

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 受け口スケルトン関数プロトタイプ宣言（VMT不要最適化により参照するもの） #_EPSP_# */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

#ifndef TOPPERS_CB_TYPE_ONLY


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tPutLogBCM283X_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tPutLogBCM283X_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tPutLogBCM283X_IDX

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define cSIOPort_open( ) \
                      tPutLogBCM283X_cSIOPort_open( )
#define cSIOPort_close( ) \
                      tPutLogBCM283X_cSIOPort_close( )
#define cSIOPort_putChar( c ) \
                      tPutLogBCM283X_cSIOPort_putChar( c )
#define cSIOPort_getChar( ) \
                      tPutLogBCM283X_cSIOPort_getChar( )
#define cSIOPort_enableCBR( cbrtn ) \
                      tPutLogBCM283X_cSIOPort_enableCBR( cbrtn )
#define cSIOPort_disableCBR( cbrtn ) \
                      tPutLogBCM283X_cSIOPort_disableCBR( cbrtn )


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define ePutLog_putChar  tPutLogBCM283X_ePutLog_putChar

/* CB 初期化マクロ #_CIM_# */
#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tPutLogBCM283X_TECSGENH */
