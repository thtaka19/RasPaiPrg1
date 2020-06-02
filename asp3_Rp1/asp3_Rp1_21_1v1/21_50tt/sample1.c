/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2016 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: sample1.c 711 2016-03-29 14:45:54Z ertl-hiro $
 */

/* 
 *  サンプルプログラム(1)の本体

 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "sample1.h"

//#include "serial.h" //2018 TT
#include "../cmn00/mini_serial.h"
//#include "led.h" //2018 TT
#include "../cmn00/led.h"
void writeVectorBaseRegister(int);
void setHighVector(void);
void setLowVector(void);
#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif
/*
 *  サービスコールのエラーのログ出力
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))


/*
 *  ループ回数
 */
ulong_t	task_loop;		/* タスク内でのループ回数 */



/*
 *  割込みハンドラ
 */
#ifdef INTNO1

void intno1_isr(intptr_t exinf)
{
	intno1_clear();
	SVC_PERROR(rot_rdq(HIGH_PRIORITY));
	SVC_PERROR(rot_rdq(MID_PRIORITY));
	SVC_PERROR(rot_rdq(LOW_PRIORITY));
}

#endif /* INTNO1 */

/*
 *  CPU例外ハンドラ
 */
ID	cpuexc_tskid;		/* CPU例外を起こしたタスクのID */

#ifdef CPUEXC1

void
cpuexc_handler(void *p_excinf)
{
	syslog(LOG_NOTICE, "CPU exception handler (p_excinf = %08p).", p_excinf);
	if (sns_ctx() != true) {
		syslog(LOG_WARNING,
					"sns_ctx() is not true in CPU exception handler.");
	}
	if (sns_dpn() != true) {
		syslog(LOG_WARNING,
					"sns_dpn() is not true in CPU exception handler.");
	}
	syslog(LOG_INFO, "sns_loc = %d sns_dsp = %d xsns_dpn = %d",
								sns_loc(), sns_dsp(), xsns_dpn(p_excinf));

	if (xsns_dpn(p_excinf)) {
		syslog(LOG_NOTICE, "Sample program ends with exception.");
		SVC_PERROR(ext_ker());
		assert(0);
	}

#ifdef PREPARE_RETURN_CPUEXC
	PREPARE_RETURN_CPUEXC;
	SVC_PERROR(get_tid(&cpuexc_tskid));
	SVC_PERROR(act_tsk(EXC_TASK));
#else /* PREPARE_RETURN_CPUEXC */
	syslog(LOG_NOTICE, "Sample program ends with exception.");
	SVC_PERROR(ext_ker());
	assert(0);
#endif /* PREPARE_RETURN_CPUEXC */
}

#endif /* CPUEXC1 */

/*
 *  周期ハンドラ
 *
 *  HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY の各優先度のレディキュー
 *  を回転させる．
 */
//void blinkLedTask(VP_INT exinf)
void blinkLedTask(void)// not use in 21_50
//void blinkLedTask(cyg_addrword_t data)
{
	m_serialPutStr("Start blinkLedTask ");
//	m_serialPutChar('0'+exinf);
	m_serialPutStr("\r\n");
	
//    while (1)
    {
    /* Delay for 500 milliseconds. */
    //    cyg_thread_delay(TICKS_PER_SECOND / 2);
//		dly_tsk(500);
        ledToggle( );
//	ledToggle47();// Only for Pi1 Pi2 
// 	ledToggleRed( );
    }
}

void cyclic_handler(intptr_t exinf)
{  // 2sec
//m_serialPutChar('Z');
	SVC_PERROR(rot_rdq(HIGH_PRIORITY));
	SVC_PERROR(rot_rdq(MID_PRIORITY));
	SVC_PERROR(rot_rdq(LOW_PRIORITY));
//blinkLedTask();
//timerDsr( );// TT 2018
}
int cntcycle = 0;
void cyclic_handler10(intptr_t exinf)
{  // 10msec
//m_serialPutChar('X');
cntcycle++;
if(cntcycle >= 20){
cntcycle = 0;// Debug
}
//blinkLedTask();
timerDsr( );// TT 2018
}
/*
 *  アラームハンドラ
 *
 *  HIGH_PRIORITY，MID_PRIORITY，LOW_PRIORITY の各優先度のレディキュー
 *  を回転させる．
 */
void alarm_handler(intptr_t exinf)
{
	SVC_PERROR(rot_rdq(HIGH_PRIORITY));
	SVC_PERROR(rot_rdq(MID_PRIORITY));
	SVC_PERROR(rot_rdq(LOW_PRIORITY));
}

/*
 *  例外処理タスク
 */
void exc_task(intptr_t exinf)
{
	SVC_PERROR(ras_ter(cpuexc_tskid));
}

/*
 *  メインタスク
 */
void main_task(intptr_t exinf)
{
	char	c;
//	ID		tskid = TASK1; //2018 TT
//	int_t	tskno = 1; //2018 TT
	ER_UINT	ercd;
	PRI		tskpri;
   int  bCommandReady = FALSE;
#ifndef TASK_LOOP
	volatile ulong_t	i;
	SYSTIM	stime1, stime2;
#endif /* TASK_LOOP */
//	HRTCNT	hrtcnt1, hrtcnt2; //2018 TT
/////   Vecter address Set 2018 TT
	writeVectorBaseRegister(0x0000);
	setLowVector();

//	SVC_PERROR(syslog_msk_log(LOG_UPTO(LOG_INFO), LOG_UPTO(LOG_EMERG)));
	syslog(LOG_NOTICE, "RP1_21_50 1v1 4Tasks Sample program starts (exinf = %d).", (int_t) exinf);

	/*
	 *  シリアルポートの初期化
	 *
	 *  システムログタスクと同じシリアルポートを使う場合など，シリアル
	 *  ポートがオープン済みの場合にはここでE_OBJエラーになるが，支障は
	 *  ない．
	 */
	ercd = serial_opn_por(TASK_PORTID);
	if (ercd < 0 && MERCD(ercd) != E_OBJ) {
		syslog(LOG_ERROR, "%s (%d) reported by `serial_opn_por'.",
									itron_strerror(ercd), SERCD(ercd));
	}
	SVC_PERROR(serial_ctl_por(TASK_PORTID,
							(IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCRCV)));

	/*
 	 *  ループ回数の設定
	 *
	 *  並行実行されるタスク内での空ループの回数（task_loop）は，空ルー
	 *  プの実行時間が約0.4秒になるように設定する．この設定のために，
	 *  LOOP_REF回の空ループの実行時間を，その前後でget_timを呼ぶことで
	 *  測定し，その測定結果から空ループの実行時間が0.4秒になるループ回
	 *  数を求め，task_loopに設定する．
	 *
	 *  LOOP_REFは，デフォルトでは1,000,000に設定しているが，想定したよ
	 *  り遅いプロセッサでは，サンプルプログラムの実行開始に時間がかか
	 *  りすぎるという問題を生じる．逆に想定したより速いプロセッサでは，
	 *  LOOP_REF回の空ループの実行時間が短くなり，task_loopに設定する値
	 *  の誤差が大きくなるという問題がある．
	 *
	 *  そこで，そのようなターゲットでは，target_test.hで，LOOP_REFを適
	 *  切な値に定義するのが望ましい．
	 *
	 *  また，task_loopの値を固定したい場合には，その値をTASK_LOOPにマ
	 *  クロ定義する．TASK_LOOPがマクロ定義されている場合，上記の測定を
	 *  行わずに，TASK_LOOPに定義された値を空ループの回数とする．
	 *
	 * ターゲットによっては，空ループの実行時間の1回目の測定で，本来よ
	 * りも長めになるものがある．このようなターゲットでは，MEASURE_TWICE
	 * をマクロ定義することで，1回目の測定結果を捨てて，2回目の測定結果
	 * を使う．
	 */
#ifdef TASK_LOOP
	task_loop = TASK_LOOP;
#else /* TASK_LOOP */

#ifdef MEASURE_TWICE
	task_loop = LOOP_REF;
	SVC_PERROR(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC_PERROR(get_tim(&stime2));
#endif /* MEASURE_TWICE */

	task_loop = LOOP_REF;
	SVC_PERROR(get_tim(&stime1));
	for (i = 0; i < task_loop; i++);
	SVC_PERROR(get_tim(&stime2));
	task_loop = LOOP_REF * 400LU / (ulong_t)(stime2 - stime1) * 1000LU;

#endif /* TASK_LOOP */
//	serialInit(); //2018 TT
//	ledInit(); //2018 TT	
mainInit();//2018 TT moncont94.c

	/*
 	 *  タスクの起動
	 
	SVC_PERROR(act_tsk(TASK1));
	SVC_PERROR(act_tsk(TASK2));
	SVC_PERROR(act_tsk(TASK3));
****/
	SVC_PERROR(act_tsk(TASK1));// Timer100ms  Task
	SVC_PERROR(act_tsk(TASK2));// Timer500ms Task
	SVC_PERROR(act_tsk(TASK3));//Read Key-in command  
	SVC_PERROR(act_tsk(TASK4));//mail Read task
//	SVC_PERROR(act_tsk(TASK5));// Idle task

	/*
 	 *  メインループ
	 */
	syslog(LOG_INFO, "#sta_cyc(1)");
			SVC_PERROR(sta_cyc(CYCHDR1));
	SVC_PERROR(sta_cyc(CYCHDR2));// 10ms TT

m_serialPutChar('>');
	do {
//m_serialPutChar('?');
//		SVC_PERROR(serial_rea_dat(TASK_PORTID, &c, 1));
//m_serialPutChar(c);
 //delay(1000000);
SVC_PERROR(tslp_tsk(1000000*10));//Debug 2020 May
/***  Serial port read by Task3
		SVC_PERROR(serial_rea_dat(TASK_PORTID, &c, 1));
		m_serialPutChar('M'); // Debug 2020 May
m_serialPutChar(c);
      bCommandReady = cliBuildCommand(c);

        // Call the CLI command processing routine to verify the command entered 
        // and call the command function; then output a new prompt. 
        if (bCommandReady == TRUE)
        {
            bCommandReady = FALSE;
            cliProcessCommand();

            m_serialPutChar('>');
        }
***/
	} while (c != '\003' && c != 'Q');

	syslog(LOG_NOTICE, "Sample program ends.");
	SVC_PERROR(ext_ker());
	assert(0);
}
