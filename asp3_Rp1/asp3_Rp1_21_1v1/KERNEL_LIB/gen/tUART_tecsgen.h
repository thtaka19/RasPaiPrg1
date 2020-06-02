/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef tUART_TECSGEN_H
#define tUART_TECSGEN_H

/*
 * celltype          :  tUART
 * global name       :  tUART
 * idx_is_id(actual) :  no(no)
 * singleton         :  no
 * has_CB            :  true
 * has_INIB          :  true
 * rom               :  yes
 * CB initializer    :  yes
 */

/* グローバルヘッダ #_IGH_# */
#include "global_tecsgen.h"

/* シグニチャヘッダ #_ISH_# */
#include "sSIOPort_tecsgen.h"
#include "siSIOCBR_tecsgen.h"
#include "siHandlerBody_tecsgen.h"

#ifndef TOPPERS_MACRO_ONLY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* セル INIB 型宣言 #_CIP_# */
typedef const struct tag_tUART_INIB {
    /* call port #_TCP_# */ 
    /* call port #_NEP_# */ 
    /* attribute(RO) #_ATO_# */ 
    uint32_t       baudRate;
}  tUART_INIB;
/* セル CB 型宣言 #_CCTPA_# */
typedef struct tag_tUART_CB {
    tUART_INIB  *_inib;
    /* var #_VA_# */ 
    bool_t         initialized;
}  tUART_CB;
extern tUART_CB  tUART_CB_tab[];

/* セルタイプのIDX型 #_CTIX_# */
typedef struct tag_tUART_CB *tUART_IDX;

/* 受け口関数プロトタイプ宣言 #_EPP_# */
/* sSIOPort */
void         tUART_eSIOPort_open(tUART_IDX idx);
void         tUART_eSIOPort_close(tUART_IDX idx);
bool_t       tUART_eSIOPort_putChar(tUART_IDX idx, char c);
int_t        tUART_eSIOPort_getChar(tUART_IDX idx);
void         tUART_eSIOPort_enableCBR(tUART_IDX idx, uint_t cbrtn);
void         tUART_eSIOPort_disableCBR(tUART_IDX idx, uint_t cbrtn);
/* siHandlerBody */
void         tUART_eiISR_main(tUART_IDX idx);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TOPPERS_MACRO_ONLY */

/* 最適化のため参照するセルタイプの CB 型の定義を取込む #_ICT_# */
#ifndef  TOPPERS_CB_TYPE_ONLY
#define  tUART_CB_TYPE_ONLY
#define TOPPERS_CB_TYPE_ONLY
#endif  /* TOPPERS_CB_TYPE_ONLY */
#include "tSIOPortBCM283XMain_tecsgen.h"
#ifdef  tUART_CB_TYPE_ONLY
#undef TOPPERS_CB_TYPE_ONLY
#endif /* tUART_CB_TYPE_ONLY */
#ifndef TOPPERS_CB_TYPE_ONLY

#define tUART_ID_BASE               (1)  /* ID のベース  #_NIDB_# */
#define tUART_N_CELL                (1)  /* セルの個数  #_NCEL_# */

/* IDXの正当性チェックマクロ #_CVI_# */
#define tUART_VALID_IDX(IDX) (1)


/* セルCBを得るマクロ #_GCB_# */
#define tUART_GET_CELLCB(idx) (idx)

/* 属性アクセスマクロ #_AAM_# */
#define tUART_ATTR_baudRate( p_that )	((p_that)->_inib->baudRate)

#define tUART_GET_baudRate(p_that)	((p_that)->_inib->baudRate)


/* var アクセスマクロ #_VAM_# */
#define tUART_VAR_initialized(p_that)	((p_that)->initialized)

#define tUART_GET_initialized(p_that)	((p_that)->initialized)
#define tUART_SET_initialized(p_that,val)	((p_that)->initialized=(val))

 /* 呼び口関数マクロ #_CPM_# */
#define tUART_ciSIOCBR_readySend( p_that ) \
	  tSIOPortBCM283XMain_eiSIOCBR_readySend( \
	   (tSIOPortBCM283XMain_IDX)0 )
#define tUART_ciSIOCBR_readyReceive( p_that ) \
	  tSIOPortBCM283XMain_eiSIOCBR_readyReceive( \
	   (tSIOPortBCM283XMain_IDX)0 )

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

/* IDXの正当性チェックマクロ（短縮形） #_CVIA_# */
#define VALID_IDX(IDX)  tUART_VALID_IDX(IDX)


/* セルCBを得るマクロ(短縮形) #_GCBA_# */
#define GET_CELLCB(idx)  tUART_GET_CELLCB(idx)

/* CELLCB 型(短縮形) #_CCT_# */
#define CELLCB	tUART_CB

/* セルタイプのIDX型(短縮形) #_CTIXA_# */
#define CELLIDX	tUART_IDX


/* 属性アクセスマクロ(短縮形) #_AAMA_# */
#define ATTR_baudRate        tUART_ATTR_baudRate( p_cellcb )


/* var アクセスマクロ(短縮形) #_VAMA_# */
#define VAR_initialized      tUART_VAR_initialized( p_cellcb )

/* 呼び口関数マクロ（短縮形）#_CPMA_# */
#define ciSIOCBR_readySend( ) \
                      ((void)p_cellcb, tUART_ciSIOCBR_readySend( p_cellcb ))
#define ciSIOCBR_readyReceive( ) \
                      ((void)p_cellcb, tUART_ciSIOCBR_readyReceive( p_cellcb ))


/* 受け口関数マクロ（短縮形） #_EPM_# */
#define eSIOPort_open    tUART_eSIOPort_open
#define eSIOPort_close   tUART_eSIOPort_close
#define eSIOPort_putChar tUART_eSIOPort_putChar
#define eSIOPort_getChar tUART_eSIOPort_getChar
#define eSIOPort_enableCBR tUART_eSIOPort_enableCBR
#define eSIOPort_disableCBR tUART_eSIOPort_disableCBR
#define eiISR_main       tUART_eiISR_main

/* イテレータコード (FOREACH_CELL)の生成 #_FEC_# */
#define FOREACH_CELL(i,p_cb)   \
    for( (i) = 0; (i) < tUART_N_CELL; (i)++ ){ \
       (p_cb) = &tUART_CB_tab[i];

#define END_FOREACH_CELL   }

/* CB 初期化マクロ #_CIM_# */
#define INITIALIZE_CB(p_that)\
	(p_that)->initialized = false;
#define SET_CB_INIB_POINTER(i,p_that)\
	(p_that)->_inib = &tUART_INIB_tab[(i)];

#endif /* TOPPERS_CB_TYPE_ONLY */

#ifndef TOPPERS_MACRO_ONLY

#endif /* TOPPERS_MACRO_ONLY */

#endif /* tUART_TECSGENH */
