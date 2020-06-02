/*  1 "./gen/tmp_C_src.c" */
/*  1 "<command-line>" */
/*  1 "./gen/tmp_C_src.c" */
/*  27 "./gen/tmp_C_src.c" */
typedef struct { int dummy; } va_list;

/*  1 "../include/t_syslog.h" 1 */
/*  69 "../include/t_syslog.h" */
/*  1 "../include/t_stddef.h" 1 */
/*  65 "../include/t_stddef.h" */
/*  1 "../target/rp1_gcc/target_stddef.h" 1 */
/*  59 "../target/rp1_gcc/target_stddef.h" */
/*  1 "../arch/arm_gcc/bcm283x/chip_stddef.h" 1 */
/*  56 "../arch/arm_gcc/bcm283x/chip_stddef.h" */
/*  1 "../arch/arm_gcc/common/core_stddef.h" 1 */
/*  57 "../arch/arm_gcc/bcm283x/chip_stddef.h" 2 */
/*  60 "../target/rp1_gcc/target_stddef.h" 2 */
/*  69 "../target/rp1_gcc/target_stddef.h" */
/*  1 "../arch/gcc/tool_stddef.h" 1 */
/*  81 "../arch/gcc/tool_stddef.h" */
/*  1 "/usr/lib/gcc/arm-none-eabi/4.8.2/include/stddef.h" 1 3 4 */
/*  147 "/usr/lib/gcc/arm-none-eabi/4.8.2/include/stddef.h" 3 4 */
typedef int ptrdiff_t;
/*  212 "/usr/lib/gcc/arm-none-eabi/4.8.2/include/stddef.h" 3 4 */
typedef unsigned int size_t;
/*  324 "/usr/lib/gcc/arm-none-eabi/4.8.2/include/stddef.h" 3 4 */
typedef unsigned int wchar_t;
/*  82 "../arch/gcc/tool_stddef.h" 2 */
/*  1 "/usr/lib/gcc/arm-none-eabi/4.8.2/include-fixed/limits.h" 1 3 4 */
/*  83 "../arch/gcc/tool_stddef.h" 2 */
/*  102 "../arch/gcc/tool_stddef.h" */
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed long long int64_t;
typedef unsigned long long uint64_t;

typedef int8_t int_least8_t;
typedef uint8_t uint_least8_t;

typedef long intptr_t;
typedef unsigned long uintptr_t;
/*  191 "../arch/gcc/tool_stddef.h" */
typedef float float32_t;
typedef double double64_t;
/*  70 "../target/rp1_gcc/target_stddef.h" 2 */
/*  66 "../include/t_stddef.h" 2 */
/*  84 "../include/t_stddef.h" */
struct TOPPERS_dummy_t { int TOPPERS_dummy_field; };
typedef void (*TOPPERS_fp_t)(struct TOPPERS_dummy_t);






typedef int bool_t;

typedef signed int int_t;
typedef unsigned int uint_t;

typedef signed long long_t;
typedef unsigned long ulong_t;

typedef int_t FN;
typedef int_t ER;
typedef int_t ID;
typedef uint_t ATR;
typedef uint_t STAT;
typedef uint_t MODE;
typedef int_t PRI;
typedef uint32_t TMO;
typedef uint32_t RELTIM;

typedef uint64_t SYSTIM;



typedef uint32_t PRCTIM;
typedef uint32_t HRTCNT;

typedef TOPPERS_fp_t FP;

typedef int_t ER_BOOL;
typedef int_t ER_ID;
typedef int_t ER_UINT;

typedef uintptr_t MB_T;

typedef uint32_t ACPTN;
typedef struct acvct {
 ACPTN acptn1;
 ACPTN acptn2;
 ACPTN acptn3;
 ACPTN acptn4;
} ACVCT;
/*  70 "../include/t_syslog.h" 2 */
/*  119 "../include/t_syslog.h" */
typedef struct {
 uint_t logtype;
 HRTCNT logtim;
 intptr_t logpar[6];
} SYSLOG;
/*  134 "../include/t_syslog.h" */
typedef struct t_syslog_rlog {
 uint_t count;
 uint_t lost;
 uint_t logmask;
 uint_t lowmask;
} T_SYSLOG_RLOG;
/*  149 "../include/t_syslog.h" */
extern ER tSysLog_eSysLog_write(uint_t prio, const SYSLOG *p_syslog) ;

static __inline__ void
_syslog_0(uint_t prio, uint_t type)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}

static __inline__ void
_syslog_1(uint_t prio, uint_t type, intptr_t arg1)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 logbuf.logpar[0] = arg1;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}

static __inline__ void
_syslog_2(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 logbuf.logpar[0] = arg1;
 logbuf.logpar[1] = arg2;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}

static __inline__ void
_syslog_3(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 logbuf.logpar[0] = arg1;
 logbuf.logpar[1] = arg2;
 logbuf.logpar[2] = arg3;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}

static __inline__ void
_syslog_4(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
           intptr_t arg3, intptr_t arg4)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 logbuf.logpar[0] = arg1;
 logbuf.logpar[1] = arg2;
 logbuf.logpar[2] = arg3;
 logbuf.logpar[3] = arg4;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}

static __inline__ void
_syslog_5(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
        intptr_t arg3, intptr_t arg4, intptr_t arg5)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 logbuf.logpar[0] = arg1;
 logbuf.logpar[1] = arg2;
 logbuf.logpar[2] = arg3;
 logbuf.logpar[3] = arg4;
 logbuf.logpar[4] = arg5;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}

static __inline__ void
_syslog_6(uint_t prio, uint_t type, intptr_t arg1, intptr_t arg2,
     intptr_t arg3, intptr_t arg4, intptr_t arg5, intptr_t arg6)
{
 SYSLOG logbuf;

 logbuf.logtype = type;
 logbuf.logpar[0] = arg1;
 logbuf.logpar[1] = arg2;
 logbuf.logpar[2] = arg3;
 logbuf.logpar[3] = arg4;
 logbuf.logpar[4] = arg5;
 logbuf.logpar[5] = arg6;
 (void) tSysLog_eSysLog_write(prio, &logbuf);
}




extern void syslog(uint_t prio, const char *format, ...) ;
/*  29 "./gen/tmp_C_src.c" 2 */
