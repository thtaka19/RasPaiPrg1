/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#include "tUART_tecsgen.h"
#include "tUART_factory.h"

/* 受け口ディスクリプタ型 #_EDT_# */
/* eSIOPort : omitted by entry port optimize */

/* eiISR : omitted by entry port optimize */

/* 受け口スケルトン関数 #_EPSF_# */
/* eSIOPort : omitted by entry port optimize */
/* eiISR : omitted by entry port optimize */

/* 受け口スケルトン関数テーブル #_EPSFT_# */
/* eSIOPort : omitted by entry port optimize */
/* eiISR : omitted by entry port optimize */

/* 呼び口の参照する受け口ディスクリプタ(実際の型と相違した定義) #_CPEPD_# */

/* 呼び口配列 #_CPA_# */

/* 属性・変数の配列 #_AVAI_# */
/* セル INIB #_INIB_# */
tUART_INIB tUART_INIB_tab[] = {
    /* cell: tUART_CB_tab[0]:  SIOPortTarget1_UART id=1 */
    {
        /* call port #_CP_# */ 
        /* entry port #_EP_# */ 
        /* attribute(RO) */ 
        115200,                                  /* baudRate */
    },
};

/* セル CB #_CB_# */
struct tag_tUART_CB tUART_CB_tab[1];
/* 受け口ディスクリプタ #_EPD_# */
/* eSIOPort : omitted by entry port optimize */
/* eiISR : omitted by entry port optimize */
/* CB 初期化コード #_CIC_# */
void
tUART_CB_initialize()
{
    tUART_CB	*p_cb;
    int		i;
    FOREACH_CELL(i,p_cb)
        SET_CB_INIB_POINTER(i,p_cb)
        INITIALIZE_CB(p_cb)
    END_FOREACH_CELL
}
