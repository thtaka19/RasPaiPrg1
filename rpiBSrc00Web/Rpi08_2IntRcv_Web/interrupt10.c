/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
#include	"io10.h"
#include "mini_serial9Pls.h"
#include "startupAss.h"
#include "rpi_timer9.h"

void uartHandler0();
void uartHandler1();
void timerHandler();
void timerIRQ_func(void);
void delay(int );

void set_vector_table(void){
	extern void *_initial_vector_start;
	extern void *_initial_vector_end;

	volatile unsigned int *vec = 0;
	volatile unsigned int *p;
	volatile unsigned int *s = (unsigned int *)&_initial_vector_start;
	volatile unsigned int *e = (unsigned int *)&_initial_vector_end;
//        volatile unsigned int delayNop = 0;

	// printf("Vector table check\n");
	// printf("Addr : Hex\n");
	vec++;
	for (p = s+1; p < e; p++) {
		*vec = *p;
	//	 printf("0x%02x : 0x%08x\n",vec,*vec);
		vec++;
	}
}

void prt_vector_table(void){
	extern void *_initial_vector_start;
	extern void *_initial_vector_end;

	volatile unsigned int *vec = 0;
	volatile unsigned int *p;
	volatile unsigned int *s = (unsigned int *)&_initial_vector_start;
	volatile unsigned int *e = (unsigned int *)&_initial_vector_end;
//        volatile unsigned int delayNop = 0;

	 printf("Vector table check\r\n");
	 printf("Addr : Hex\r\n");
	vec++;
	for (p = s+1; p < e; p++) {
//		*vec = *p;
		 printf("0x%02x : 0x%08x\r\n",vec,*vec);
		vec++;
	}
}

extern volatile int timer;

static	int     irqP[3]={0,0,0};
static int i1=0;
static int i2=0; 
void interruptServiceRoutine(void)
{

        struct rpiIrqController *rpiIRQController =
                (struct rpiIrqController *)RPI_INTERRUPT_CONTROLLER_BASE;
	struct rpiArmTimer *rpiArmTimer = (struct rpiArmTimer *)RPI_ARMTIMER_BASE;
/////interruptDisable();
	disable_IRQ();
//	printf("interrupt called \r\n");
//	printf("1:%016lx\n",rpiIRQController->IRQ_pending_1 );
//	printf("2:%016lx\n",rpiIRQController->IRQ_pending_2 );

	if(rpiIRQController->IRQ_basic_pending & (0x01<<0)) {// Timer Int ?

		i1++;
		//timerInterrupt();
		timerIRQ_func();
		rpiArmTimer->IRQClear = 0; // Timer_IRQ_Flag clear 2017 TT
irqP[0]++;
	    	if(i1%500 == 0 ){
		  printf("Timer Int. %d times",i1);
		  printf("\r\nIRQ_basic_pending= 0x%08x== \r\n",rpiIRQController->IRQ_basic_pending );
		}
	};
/***

***/

	if(rpiIRQController->IRQ_pending_1 & (0x01<<29)) {// Pi3 mini_Serial Int29
		i2++;
		m_serialRcvInterrupt();
irqP[1]++;
		 if(i2%500 == 0){
		printf("Serial Int. %d times",i2);
		printf("\r\nIRQ_pending_1= 0x%08x== \r\n",rpiIRQController->IRQ_pending_1);
		}
	}



	enable_IRQ();
  //      setirqP00(irqP[0],irqP[1]);
}
void irqPcnt(int * tmp0) {
 tmp0[0]=irqP[0];
 tmp0[1]=irqP[1];
}

