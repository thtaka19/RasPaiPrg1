２０１８年６月時点での作成方法　　Rsp21_の作成方法
Exp.
１）sampleフォルダーをコピーして、21_0blkフォルダーを作成。
2)21_0BLKフォルダーに、昔の_21のソース類をコピー。旧ｍｕｔｅｘ．ｃの＃ｉｎｃｌｕｄｅに<kernel.h>と<ｋｅｒｎｅｌｃｆｇ．h>を追加。
　sample1.cfgを修正してコンフィグファイル作成。このときｓａｍｐｌｅ１．ｈも同時修正必要。
3)sample1.cファイルのメインも調整。task を　act に。また旧main.c　はリンクしないため　各種初期設定　ｌｅｄＩｎｉｔ（）等もsample1.cに追記。ｖｅｃｔｅｒテーブル設定は当面なし。
    m_serialPutStr への修正も必要。

４）ｂｕｉｌｄ21_0BLKフォルダー作成。　ｃｄ　して　../rubyでMakeファイル作成。Ｍａｋｅファイルのアプリのディレクトリ等修正。
５）makeで　．ｓｒｅｃをビルドする。

Exp2　　ＯｒｉｇｉｎａｌーSample　と　２１＿０ｍｔｘの差
１）全共通
１−１）　Sample1.c　の　基本差分　　ｌｏｇ出力、とU-Boot用のベクター設定を追加。
> /////   Vecter address Set 2018 TT
> 	writeVectorBaseRegister(0x0000);
> 	setLowVector();
304c307
< 	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));
---
> //	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));

2)syssvc/tBannerMain.c　には以下を追加。　ログ出力のため
>        syslog_msk_log(LOG_UPTO(LOG_DEBUG), LOG_UPTO(LOG_DEBUG));  // 2018_06 TT
なおｕｓｅｒ．ｔｘｔには以下の記述
○Sample1のシステムログの出力だった。　syssvc/banner.c　ーー＞　syssvc/tBannerMain.c　

・syssvc/banner.c
==============================
[変更前]
void
print_banner_copyright(intptr_t exinf)
{
	syslog_3(LOG_NOTICE, banner,
------------------------------
[変更後]
void
print_banner_copyright(intptr_t exinf)
{
	syslog_msk_log(LOG_UPTO(LOG_DEBUG), LOG_UPTO(LOG_DEBUG));
	syslog_3(LOG_NOTICE, banner,
==============================

２）個別　差分
2-1)  Make File OBJNAME と　 APPLDIRS　と　 APPL_COBJS 
$ diff buildRp1_21_00Org/Makefile build21_0smp/Makefile 
111c111,112
< OBJNAME = asp
---
> OBJNAME = 21_0smp
> #OBJNAME = asp
175c176
< APPLDIRS = $(SRCDIR)/sample
---
> APPLDIRS = $(SRCDIR)/21_0smp
185c186
< 	APPL_COBJS := sample1.o mini_serialPi1.o
---
> 	APPL_COBJS := sample1.o semaphore21.o mini_serialPi1.o led.o buttonPi1.o

２−２）sample1.cfg　は　H8のsystewm.cfgを参照に　Origunal　の　taskとイベントを修正。
diff sampleOrg/sample1.cfg 21_0smp/sample1.cfg
9,11c9,15
< CRE_TSK(TASK1, { TA_NULL, 1, task, MID_PRIORITY, STACK_SIZE, NULL });
< CRE_TSK(TASK2, { TA_NULL, 2, task, MID_PRIORITY, STACK_SIZE, NULL });
< CRE_TSK(TASK3, { TA_NULL, 3, task, MID_PRIORITY, STACK_SIZE, NULL });
---
> //CRE_TSK(TASK1, { TA_NULL, 1, decrementTask, MID_PRIORITY, STACK_SIZE, NULL });
> //CRE_TSK(TASK2, { TA_NULL, 2, incrementTask, MID_PRIORITY, STACK_SIZE, NULL });
> //CRE_TSK(TASK3, { TA_NULL, 3, task, MID_PRIORITY, STACK_SIZE, NULL });
> //CRE_TSK(MAIN_TASK, { TA_ACT, 0, blk_task, MAIN_PRIORITY, STACK_SIZE, NULL });
> CRE_TSK(TASK1, {TA_NULL, 1,producerTask, MID_PRIORITY, STACK_SIZE, NULL});//Create Task 
> CRE_TSK(TASK2, {TA_NULL, 2,consumerTask,  MID_PRIORITY,STACK_SIZE, NULL});//Create Task 
> 
13a18,21
> 
> /*Semaphore*/
> CRE_SEM(Semaphore1, {TA_NULL, 0, 1});
> 
14a23
> 
15a25,26
> 
> //CRE_MTX(MTX1,{TA_NULL});

２−３）sample1.hは　追加関数のｅｘｔｅｒｎを
$ diff sampleOrg/sample1.h 21_0smp/sample1.h
83c83
<  *  関数のプロトタイプ宣言
---
>  *  関数のプロトタイプ宣言  incrementTask
86c86,91
< 
---
> extern void producerTask(intptr_t exinf);
> extern void 	consumerTask(intptr_t exinf);
> extern void	incrementTask(intptr_t exinf);
> extern void	decrementTask(intptr_t exinf);
> extern void	blk_task(intptr_t exinf);
> extern void	task1(intptr_t exinf);

２−４）　sample.hは、H8の。ｈで　asp3では使わない。
２−５）　メインタスクは迷うところだが、当面追加する。H8のタスクに、mainタスク、エラータスクは追加となる。ｓａｍｐｌｅ１．ｃは健在ということ。



