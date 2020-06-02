/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if !(TKERNEL_PRID == 0x0007U && (TKERNEL_PRVER & 0xf000U) == 0x3000U)
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives
 */

#include "target_timer.h"
#include "tTask_tecsgen.h"
#include "tISR_tecsgen.h"
#include "tInitializeRoutine_tecsgen.h"
#include "tTerminateRoutine_tecsgen.h"
#include "sample1.h"

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_TSKID_tTask_LogTask_Task[COUNT_STK_T(4096)];
static STK_T _kernel_stack_MAIN_TASK[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_EXC_TASK[COUNT_STK_T(STACK_SIZE)];
const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(&tTask_CB_tab[0]), (TASK)(tTask_start), INT_PRIORITY(3), ROUND_STK_T(4096), _kernel_stack_TSKID_tTask_LogTask_Task },
	{ (TA_ACT), (intptr_t)(0), (TASK)(main_task), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK },
	{ (TA_NULL), (intptr_t)(0), (TASK)(exc_task), INT_PRIORITY(EXC_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_EXC_TASK }
};

TCB _kernel_tcb_table[TNUM_TSKID];

const ID _kernel_torder_table[TNUM_TSKID] = { 
	TSKID_tTask_LogTask_Task, MAIN_TASK, EXC_TASK
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_NULL), (0), (1) },
	{ (TA_NULL), (1), (1) }
};

SEMCB _kernel_semcb_table[TNUM_SEMID];

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
TOPPERS_EMPTY_LABEL(FLGCB, _kernel_flgcb_table);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);
TOPPERS_EMPTY_LABEL(DTQCB, _kernel_dtqcb_table);

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB, _kernel_pdqcb_table);

/*
 *  Mutex Functions
 */

const ID _kernel_tmax_mtxid = (TMIN_MTXID + TNUM_MTXID - 1);

TOPPERS_EMPTY_LABEL(const MTXINIB, _kernel_mtxinib_table);
TOPPERS_EMPTY_LABEL(MTXCB, _kernel_mtxcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);

/*
 *  Cyclic Notification Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{ (TA_NULL), (intptr_t)(0), (NFYHDR)(cyclic_handler), (2000000), (0) }
};

CYCCB _kernel_cyccb_table[TNUM_CYCID];

/*
 *  Alarm Notification Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {
	{ (TA_NULL), (intptr_t)(0), (NFYHDR)(alarm_handler) }
};

ALMCB _kernel_almcb_table[TNUM_ALMID];

/*
 *  Interrupt Management Functions
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(isrid)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(isrid)
#endif /* LOG_ISR_LEAVE */

void
_kernel_inthdr_61(void)
{
	LOG_ISR_ENTER(ISRID_tISR_SIOPortTarget1_ISRInstance);
	((ISR)(tISR_start))((intptr_t)(&tISR_CB_tab[0]));
	LOG_ISR_LEAVE(ISRID_tISR_SIOPortTarget1_ISRInstance);
}

#define TNUM_CFG_INTNO	2
const uint_t _kernel_tnum_cfg_intno = TNUM_CFG_INTNO;

const INTINIB _kernel_intinib_table[TNUM_CFG_INTNO] = {
	{ (INTNO_TIMER), (TA_ENAINT|INTATR_TIMER), (-7) },
	{ (IRQ_UART), (TA_NULL), (-7) }
};

/*
 *  CPU Exception Management Functions
 */

/*
 *  Stack Area for Non-task Context
 */

static STK_T _kernel_istack[COUNT_STK_T(DEFAULT_ISTKSZ)];
const size_t _kernel_istksz = ROUND_STK_T(DEFAULT_ISTKSZ);
STK_T *const _kernel_istk = _kernel_istack;

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_istkpt = TOPPERS_ISTKPT(_kernel_istack, ROUND_STK_T(DEFAULT_ISTKSZ));
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_tmevt_heap[1 + TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_semaphore();
	_kernel_initialize_cyclic();
	_kernel_initialize_alarm();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(_kernel_target_hrt_initialize))((intptr_t)(0));
	((INIRTN)(tInitializeRoutine_start))((intptr_t)(NULL));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(tTerminateRoutine_start))((intptr_t)(NULL));
	((TERRTN)(_kernel_target_hrt_terminate))((intptr_t)(0));
}

/*
 *  Interrupt Handler Table
 */

const FP _kernel_inh_table[TNUM_INHNO] = {
	/* 0x000 */ (FP)(_kernel_default_int_handler),
	/* 0x001 */ (FP)(_kernel_default_int_handler),
	/* 0x002 */ (FP)(_kernel_default_int_handler),
	/* 0x003 */ (FP)(_kernel_default_int_handler),
	/* 0x004 */ (FP)(_kernel_default_int_handler),
	/* 0x005 */ (FP)(_kernel_default_int_handler),
	/* 0x006 */ (FP)(_kernel_default_int_handler),
	/* 0x007 */ (FP)(_kernel_default_int_handler),
	/* 0x008 */ (FP)(_kernel_default_int_handler),
	/* 0x009 */ (FP)(_kernel_default_int_handler),
	/* 0x00a */ (FP)(_kernel_default_int_handler),
	/* 0x00b */ (FP)(_kernel_default_int_handler),
	/* 0x00c */ (FP)(_kernel_default_int_handler),
	/* 0x00d */ (FP)(_kernel_default_int_handler),
	/* 0x00e */ (FP)(_kernel_default_int_handler),
	/* 0x00f */ (FP)(_kernel_default_int_handler),
	/* 0x010 */ (FP)(_kernel_default_int_handler),
	/* 0x011 */ (FP)(_kernel_default_int_handler),
	/* 0x012 */ (FP)(_kernel_default_int_handler),
	/* 0x013 */ (FP)(_kernel_default_int_handler),
	/* 0x014 */ (FP)(_kernel_default_int_handler),
	/* 0x015 */ (FP)(_kernel_default_int_handler),
	/* 0x016 */ (FP)(_kernel_default_int_handler),
	/* 0x017 */ (FP)(_kernel_default_int_handler),
	/* 0x018 */ (FP)(_kernel_default_int_handler),
	/* 0x019 */ (FP)(_kernel_default_int_handler),
	/* 0x01a */ (FP)(_kernel_default_int_handler),
	/* 0x01b */ (FP)(_kernel_default_int_handler),
	/* 0x01c */ (FP)(_kernel_default_int_handler),
	/* 0x01d */ (FP)(_kernel_default_int_handler),
	/* 0x01e */ (FP)(_kernel_default_int_handler),
	/* 0x01f */ (FP)(_kernel_default_int_handler),
	/* 0x020 */ (FP)(_kernel_default_int_handler),
	/* 0x021 */ (FP)(_kernel_target_hrt_handler),
	/* 0x022 */ (FP)(_kernel_default_int_handler),
	/* 0x023 */ (FP)(_kernel_default_int_handler),
	/* 0x024 */ (FP)(_kernel_default_int_handler),
	/* 0x025 */ (FP)(_kernel_default_int_handler),
	/* 0x026 */ (FP)(_kernel_default_int_handler),
	/* 0x027 */ (FP)(_kernel_default_int_handler),
	/* 0x028 */ (FP)(_kernel_default_int_handler),
	/* 0x029 */ (FP)(_kernel_default_int_handler),
	/* 0x02a */ (FP)(_kernel_default_int_handler),
	/* 0x02b */ (FP)(_kernel_default_int_handler),
	/* 0x02c */ (FP)(_kernel_default_int_handler),
	/* 0x02d */ (FP)(_kernel_default_int_handler),
	/* 0x02e */ (FP)(_kernel_default_int_handler),
	/* 0x02f */ (FP)(_kernel_default_int_handler),
	/* 0x030 */ (FP)(_kernel_default_int_handler),
	/* 0x031 */ (FP)(_kernel_default_int_handler),
	/* 0x032 */ (FP)(_kernel_default_int_handler),
	/* 0x033 */ (FP)(_kernel_default_int_handler),
	/* 0x034 */ (FP)(_kernel_default_int_handler),
	/* 0x035 */ (FP)(_kernel_default_int_handler),
	/* 0x036 */ (FP)(_kernel_default_int_handler),
	/* 0x037 */ (FP)(_kernel_default_int_handler),
	/* 0x038 */ (FP)(_kernel_default_int_handler),
	/* 0x039 */ (FP)(_kernel_default_int_handler),
	/* 0x03a */ (FP)(_kernel_default_int_handler),
	/* 0x03b */ (FP)(_kernel_default_int_handler),
	/* 0x03c */ (FP)(_kernel_default_int_handler),
	/* 0x03d */ (FP)(_kernel_inthdr_61),
	/* 0x03e */ (FP)(_kernel_default_int_handler),
	/* 0x03f */ (FP)(_kernel_default_int_handler),
	/* 0x040 */ (FP)(_kernel_default_int_handler),
	/* 0x041 */ (FP)(_kernel_default_int_handler),
	/* 0x042 */ (FP)(_kernel_default_int_handler),
	/* 0x043 */ (FP)(_kernel_default_int_handler),
	/* 0x044 */ (FP)(_kernel_default_int_handler),
	/* 0x045 */ (FP)(_kernel_default_int_handler),
	/* 0x046 */ (FP)(_kernel_default_int_handler),
	/* 0x047 */ (FP)(_kernel_default_int_handler),
	/* 0x048 */ (FP)(_kernel_default_int_handler),
	/* 0x049 */ (FP)(_kernel_default_int_handler),
	/* 0x04a */ (FP)(_kernel_default_int_handler),
	/* 0x04b */ (FP)(_kernel_default_int_handler),
	/* 0x04c */ (FP)(_kernel_default_int_handler),
	/* 0x04d */ (FP)(_kernel_default_int_handler),
	/* 0x04e */ (FP)(_kernel_default_int_handler),
	/* 0x04f */ (FP)(_kernel_default_int_handler),
	/* 0x050 */ (FP)(_kernel_default_int_handler),
	/* 0x051 */ (FP)(_kernel_default_int_handler),
	/* 0x052 */ (FP)(_kernel_default_int_handler),
	/* 0x053 */ (FP)(_kernel_default_int_handler),
	/* 0x054 */ (FP)(_kernel_default_int_handler),
	/* 0x055 */ (FP)(_kernel_default_int_handler),
	/* 0x056 */ (FP)(_kernel_default_int_handler),
	/* 0x057 */ (FP)(_kernel_default_int_handler),
	/* 0x058 */ (FP)(_kernel_default_int_handler),
	/* 0x059 */ (FP)(_kernel_default_int_handler),
	/* 0x05a */ (FP)(_kernel_default_int_handler),
	/* 0x05b */ (FP)(_kernel_default_int_handler),
	/* 0x05c */ (FP)(_kernel_default_int_handler),
	/* 0x05d */ (FP)(_kernel_default_int_handler),
	/* 0x05e */ (FP)(_kernel_default_int_handler),
	/* 0x05f */ (FP)(_kernel_default_int_handler),
	/* 0x060 */ (FP)(_kernel_default_int_handler),
	/* 0x061 */ (FP)(_kernel_default_int_handler),
	/* 0x062 */ (FP)(_kernel_default_int_handler),
	/* 0x063 */ (FP)(_kernel_default_int_handler),
	/* 0x064 */ (FP)(_kernel_default_int_handler),
	/* 0x065 */ (FP)(_kernel_default_int_handler),
	/* 0x066 */ (FP)(_kernel_default_int_handler),
	/* 0x067 */ (FP)(_kernel_default_int_handler),
	/* 0x068 */ (FP)(_kernel_default_int_handler),
	/* 0x069 */ (FP)(_kernel_default_int_handler),
	/* 0x06a */ (FP)(_kernel_default_int_handler),
	/* 0x06b */ (FP)(_kernel_default_int_handler),
	/* 0x06c */ (FP)(_kernel_default_int_handler),
	/* 0x06d */ (FP)(_kernel_default_int_handler),
	/* 0x06e */ (FP)(_kernel_default_int_handler),
	/* 0x06f */ (FP)(_kernel_default_int_handler),
	/* 0x070 */ (FP)(_kernel_default_int_handler),
	/* 0x071 */ (FP)(_kernel_default_int_handler),
	/* 0x072 */ (FP)(_kernel_default_int_handler),
	/* 0x073 */ (FP)(_kernel_default_int_handler),
	/* 0x074 */ (FP)(_kernel_default_int_handler),
	/* 0x075 */ (FP)(_kernel_default_int_handler),
	/* 0x076 */ (FP)(_kernel_default_int_handler),
	/* 0x077 */ (FP)(_kernel_default_int_handler),
	/* 0x078 */ (FP)(_kernel_default_int_handler),
	/* 0x079 */ (FP)(_kernel_default_int_handler),
	/* 0x07a */ (FP)(_kernel_default_int_handler),
	/* 0x07b */ (FP)(_kernel_default_int_handler),
	/* 0x07c */ (FP)(_kernel_default_int_handler),
	/* 0x07d */ (FP)(_kernel_default_int_handler),
	/* 0x07e */ (FP)(_kernel_default_int_handler),
	/* 0x07f */ (FP)(_kernel_default_int_handler)
};

/*
 *  Interrupt Configuration Table
 */

const uint8_t _kernel_intcfg_table[TNUM_INTNO] = {
	/* 0x000 */ 0U,
	/* 0x001 */ 0U,
	/* 0x002 */ 0U,
	/* 0x003 */ 0U,
	/* 0x004 */ 0U,
	/* 0x005 */ 0U,
	/* 0x006 */ 0U,
	/* 0x007 */ 0U,
	/* 0x008 */ 0U,
	/* 0x009 */ 0U,
	/* 0x00a */ 0U,
	/* 0x00b */ 0U,
	/* 0x00c */ 0U,
	/* 0x00d */ 0U,
	/* 0x00e */ 0U,
	/* 0x00f */ 0U,
	/* 0x010 */ 0U,
	/* 0x011 */ 0U,
	/* 0x012 */ 0U,
	/* 0x013 */ 0U,
	/* 0x014 */ 0U,
	/* 0x015 */ 0U,
	/* 0x016 */ 0U,
	/* 0x017 */ 0U,
	/* 0x018 */ 0U,
	/* 0x019 */ 0U,
	/* 0x01a */ 0U,
	/* 0x01b */ 0U,
	/* 0x01c */ 0U,
	/* 0x01d */ 0U,
	/* 0x01e */ 0U,
	/* 0x01f */ 0U,
	/* 0x020 */ 0U,
	/* 0x021 */ 1U,
	/* 0x022 */ 0U,
	/* 0x023 */ 0U,
	/* 0x024 */ 0U,
	/* 0x025 */ 0U,
	/* 0x026 */ 0U,
	/* 0x027 */ 0U,
	/* 0x028 */ 0U,
	/* 0x029 */ 0U,
	/* 0x02a */ 0U,
	/* 0x02b */ 0U,
	/* 0x02c */ 0U,
	/* 0x02d */ 0U,
	/* 0x02e */ 0U,
	/* 0x02f */ 0U,
	/* 0x030 */ 0U,
	/* 0x031 */ 0U,
	/* 0x032 */ 0U,
	/* 0x033 */ 0U,
	/* 0x034 */ 0U,
	/* 0x035 */ 0U,
	/* 0x036 */ 0U,
	/* 0x037 */ 0U,
	/* 0x038 */ 0U,
	/* 0x039 */ 0U,
	/* 0x03a */ 0U,
	/* 0x03b */ 0U,
	/* 0x03c */ 0U,
	/* 0x03d */ 1U,
	/* 0x03e */ 0U,
	/* 0x03f */ 0U,
	/* 0x040 */ 0U,
	/* 0x041 */ 0U,
	/* 0x042 */ 0U,
	/* 0x043 */ 0U,
	/* 0x044 */ 0U,
	/* 0x045 */ 0U,
	/* 0x046 */ 0U,
	/* 0x047 */ 0U,
	/* 0x048 */ 0U,
	/* 0x049 */ 0U,
	/* 0x04a */ 0U,
	/* 0x04b */ 0U,
	/* 0x04c */ 0U,
	/* 0x04d */ 0U,
	/* 0x04e */ 0U,
	/* 0x04f */ 0U,
	/* 0x050 */ 0U,
	/* 0x051 */ 0U,
	/* 0x052 */ 0U,
	/* 0x053 */ 0U,
	/* 0x054 */ 0U,
	/* 0x055 */ 0U,
	/* 0x056 */ 0U,
	/* 0x057 */ 0U,
	/* 0x058 */ 0U,
	/* 0x059 */ 0U,
	/* 0x05a */ 0U,
	/* 0x05b */ 0U,
	/* 0x05c */ 0U,
	/* 0x05d */ 0U,
	/* 0x05e */ 0U,
	/* 0x05f */ 0U,
	/* 0x060 */ 0U,
	/* 0x061 */ 0U,
	/* 0x062 */ 0U,
	/* 0x063 */ 0U,
	/* 0x064 */ 0U,
	/* 0x065 */ 0U,
	/* 0x066 */ 0U,
	/* 0x067 */ 0U,
	/* 0x068 */ 0U,
	/* 0x069 */ 0U,
	/* 0x06a */ 0U,
	/* 0x06b */ 0U,
	/* 0x06c */ 0U,
	/* 0x06d */ 0U,
	/* 0x06e */ 0U,
	/* 0x06f */ 0U,
	/* 0x070 */ 0U,
	/* 0x071 */ 0U,
	/* 0x072 */ 0U,
	/* 0x073 */ 0U,
	/* 0x074 */ 0U,
	/* 0x075 */ 0U,
	/* 0x076 */ 0U,
	/* 0x077 */ 0U,
	/* 0x078 */ 0U,
	/* 0x079 */ 0U,
	/* 0x07a */ 0U,
	/* 0x07b */ 0U,
	/* 0x07c */ 0U,
	/* 0x07d */ 0U,
	/* 0x07e */ 0U,
	/* 0x07f */ 0U
};

/*
 *  CPU Exception Handler Table
 */

const FP _kernel_exc_table[TNUM_EXCNO] = {
	/* 0 */ (FP)(_kernel_default_exc_handler),
	/* 1 */ (FP)(cpuexc_handler),
	/* 2 */ (FP)(_kernel_default_exc_handler),
	/* 3 */ (FP)(_kernel_default_exc_handler),
	/* 4 */ (FP)(_kernel_default_exc_handler),
	/* 5 */ (FP)(_kernel_default_exc_handler)
};

/*
 *  Interrupt Handler Mask Table (for Raspberry Pi)
 */

const uint32_t _kernel_ipm_mask_tbl[TNUM_INTPRI][4] = {
	/* 0 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -1 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -2 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -3 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -4 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -5 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -6 */ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
	/* -7 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -8 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -9 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -10 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -11 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -12 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -13 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -14 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
	/* -15 */ {0x00000000, 0x20000002, 0x00000000, 0x00000000},
};

