#ifndef _DEFINES_H_INCLUDED_
#define _DEFINES_H_INCLUDED_

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#ifndef NULL
#define NULL            (void *)0
#endif
//#define NULL ((void *)0)
#define SERIAL_DEFAULT_DEVICE 1

#define ENABLE_INTR  asm volatile ("andc.b #0x3f,ccr")
#define DISABLE_INTR asm volatile ("orc.b #0xc0,ccr")



typedef unsigned char  uint8;
typedef unsigned short uint16;
//typedef unsigned long  uint32;


#ifndef _STDINT_H
#define _STDINT_H


typedef signed char    int8_t;
typedef unsigned char  uint8_t;

typedef short          int16_t;
typedef unsigned short uint16_t;

//typedef long            int32_t;// 2016 TT
//typedef unsigned long   uint32_t;// 2016 TT


#endif /* _STDINT_H */

#endif
