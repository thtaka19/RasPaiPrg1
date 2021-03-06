/************************************************************************/
/*      GCC/LLCM ARM Baremetal Software / (C) Toshio MURAI  2012-2016   */
/*      This is Free Software.   You can redistribute this software     */
/*      and/or modify it ,under the terms of the GNU General Public     */
/*      License version 3, or (at your option) any later version.       */
/*      or under the terms of the BSD 3-Clause License.	(Dual Licence)  */
/************************************************************************/
//#include <stdint.h>
/*	Rapsberry PI2 Pin (2016/03/01-)
01 DC 3v			02 DC 5v
**/
struct rpiAux {
	volatile unsigned int	IRQ;		/*	5000	*/
	volatile unsigned int	ENABLES;	/*	5004	*/
	volatile unsigned int	NO0[16-2];	/*		*/
	volatile unsigned int	MU_IO_REG;	/*	5040	*/
//	volatile unsigned int	MU_IER_REG;	/*	5044	*/
	volatile unsigned int	MU_IER0_REG;	/*	5044	*/ // 2017 TT IIR_REG
//	volatile unsigned int	MU_IIR_REG;	/*	5048	*/
	volatile unsigned int	MU_IIR0_REG;	/*	5048	*/ // 2017 TT IER_REG
	volatile unsigned int	MU_LCR_REG;	/*	504C	*/
	volatile unsigned int	MU_MCR_REG;	/*	5050	*/
	volatile unsigned int	MU_LSR_REG;	/*	5054	*/
	volatile unsigned int	MU_MSR_REG;	/*	5058	*/
	volatile unsigned int	MU_SCRATCH;	/*	505C	*/
	volatile unsigned int	MU_CNTL_REG;	/*	5060	*/
	volatile unsigned int	MU_STAT_REG;	/*	5064	*/
	volatile unsigned int	MU_BAUD_REG;	/*	5068	*/
	volatile unsigned int	NO1[8-3];	/*		*/
	volatile unsigned int	SPI0_CNTL0_REG;	/*	5080	*/
	volatile unsigned int	SPI0_CNTL1_REG;	/*	5084	*/
	volatile unsigned int	SPI0_STAT_REG;	/*	5088	*/
	volatile unsigned int	SPI0_IO_REG;	/*	5090	*/
	volatile unsigned int	SPI0_PEEK_REG;	/*	5094	*/
	volatile unsigned int	NO2[16-5];	/*		*/
	volatile unsigned int	SPI1_CNTL0_REG;	/*	50C0	*/
	volatile unsigned int	SPI1_CNTL1_REG;	/*	50C4	*/
	volatile unsigned int	SPI1_STAT_REG;	/*	50C8	*/
	volatile unsigned int	SPI1_IO_REG;	/*	50D0	*/
	volatile unsigned int	SPI1_PEEK_REG;	/*	50D4	*/
};
#define RPI_AUX_BASE	(struct rpiAux *)(RPI_IO_BASE |0x00215000)
 
//	0x7E204000

struct rpiUart{
	volatile unsigned int	DR;	//0x00 Data Register
	volatile unsigned int	RSRECR;	//0x04 reserved
	volatile unsigned int	NONE00;	//0x08 reserved
	volatile unsigned int	NONE01;	//0x0C reserved
	volatile unsigned int	NONE02;	//0x10 reserved
	volatile unsigned int	NONE03;	//0x14 reserved
	volatile unsigned int	FR;	//0x18 Flag Register
	volatile unsigned int	NONE11;	//0x1C reserved
	volatile unsigned int	ILPR;	//0x20 not in use
	volatile unsigned int	IBRD;	//0x24 Integer Baud rate divisor
	volatile unsigned int	FBRD;	//0x28 Fractional Baud rate divisor
	volatile unsigned int	LCRH;	//0x2C
	volatile unsigned int	CR;	//0x30
	volatile unsigned int	IFLS;	//0x34
	volatile unsigned int	IMSC;	//0x38
	volatile unsigned int	RIS;	//0x3C
	volatile unsigned int	MIS;	//0x40
	volatile unsigned int	ICR;	//0x44
	volatile unsigned int	DMACR;	//0x48
	volatile unsigned int	NONE2[13];	//0x4C-0x7C
	volatile unsigned int	ITCR;	//0x80  Test Control Register
	volatile unsigned int	ITIP;	//0x84  Integration Test Input Register
	volatile unsigned int	ITOP;	//0x88  Integration Tet Output Register
	volatile unsigned int	TDR;	//0x8C  Test Data Register
};

struct rpiGpio{
	volatile unsigned int    GPFSEL[6];
//    volatile unsigned int    GPFSEL0;
//    volatile unsigned int    GPFSEL1;
//    volatile unsigned int    GPFSEL2;
//    volatile unsigned int    GPFSEL3;
//    volatile unsigned int    GPFSEL4;
//    volatile unsigned int    GPFSEL5;
    volatile const unsigned int    Reserved0;
volatile unsigned int    GPSET[2];	
//    volatile unsigned int    GPSET0;
//    volatile unsigned int    GPSET1;
    volatile const unsigned int    Reserved1;
	volatile unsigned int    GPCLR[2];
//    volatile unsigned int    GPCLR0;
//    volatile unsigned int    GPCLR1;
    volatile const unsigned int    Reserved2;
	    volatile unsigned int    GPLEV[2];
//    volatile unsigned int    GPLEV0;
//    volatile unsigned int    GPLEV1;
    volatile const unsigned int    Reserved3;
    volatile unsigned int    GPEDS0;
    volatile unsigned int    GPEDS1;
    volatile const unsigned int    Reserved4;
    volatile unsigned int    GPREN0;
    volatile unsigned int    GPREN1;
    volatile const unsigned int    Reserved5;
    volatile unsigned int    GPFEN0;
    volatile unsigned int    GPFEN1;
    volatile const unsigned int    Reserved6;
    volatile unsigned int    GPHEN0;
    volatile unsigned int    GPHEN1;
    volatile const unsigned int    Reserved7;
    volatile unsigned int    GPLEN0;
    volatile unsigned int    GPLEN1;
    volatile const unsigned int    Reserved8;
    volatile unsigned int    GPAREN0;
    volatile unsigned int    GPAREN1;
    volatile const unsigned int    Reserved9;
    volatile unsigned int    GPAFEN0;
    volatile unsigned int    GPAFEN1;
    volatile const unsigned int    Reserved10;
    volatile unsigned int    GPPUD;
	volatile unsigned int    GPPUDCLK[2];	
//    volatile unsigned int    GPPUDCLK0;
//    volatile unsigned int    GPPUDCLK1;
    volatile const unsigned int    Reserved11;
};

struct rpiSysTimer{
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare0;
    volatile unsigned int compare1;
    volatile unsigned int compare2;
    volatile unsigned int compare3;
};

extern void RPI_WaitMicroSeconds( unsigned int us );


/** @brief See the documentation for the ARM side timer (Section 14 of the
    BCM2835 Peripherals PDF) */

/** @brief 0 : 16-bit counters - 1 : 23-bit counter */
#define RPI_ARMTIMER_CTRL_23BIT         ( 1 << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256  ( 2 << 2 )

/** @brief 0 : Timer interrupt disabled - 1 : Timer interrupt enabled */
#define RPI_ARMTIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE   ( 0 << 5 )

/** @brief 0 : Timer disabled - 1 : Timer enabled */
#define RPI_ARMTIMER_CTRL_ENABLE        ( 1 << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE       ( 0 << 7 )


/** @brief Section 14.2 of the BCM2835 Peripherals documentation details
    the register layout for the ARM side timer */
struct rpiArmTimer{
    volatile unsigned int Load;
    volatile unsigned int Value;
    volatile unsigned int Control;
    volatile unsigned int IRQClear;
    volatile unsigned int RAWIRQ;
    volatile unsigned int MaskedIRQ;
    volatile unsigned int Reload;
    volatile unsigned int PreDivider;
    volatile unsigned int FreeRunningCounter;
};

/***************************************************************
	Interrup Header
***************************************************************/


/** @brief Bits in the Enable_Basic_IRQs register to enable various interrupts.
    See the BCM2835 ARM Peripherals manual, section 7.5 */
#define RPI_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define RPI_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define RPI_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define RPI_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define RPI_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define RPI_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define RPI_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define RPI_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)


/** @brief The interrupt controller memory mapped register set */
struct rpiIrqController{
    volatile unsigned int IRQ_basic_pending;
    volatile unsigned int IRQ_pending_1;
    volatile unsigned int IRQ_pending_2;
    volatile unsigned int FIQ_control;
    volatile unsigned int Enable_IRQs_1;
    volatile unsigned int Enable_IRQs_2;
    volatile unsigned int Enable_Basic_IRQs;
    volatile unsigned int Disable_IRQs_1;
    volatile unsigned int Disable_IRQs_2;
    volatile unsigned int Disable_Basic_IRQs;
};
///
// SPI0 peripheral
struct rpiSpi0{
//	SPI0_BASE		(0x00204000)
volatile unsigned int SPI0_CS		;	
volatile unsigned int SPI0_FIFO	;	
volatile unsigned int SPI0_CLK	;	
volatile unsigned int SPI0_DLEN	;	
volatile unsigned int SPI0_LTOH	;	
volatile unsigned int SPI0_DC		;	
};
// I2C(BSC1) peripheral
struct rpiBsc1{
// BSC1_BASE	(0x00804000)
volatile unsigned int BSC1_C		;
volatile unsigned int BSC1_S		;
volatile unsigned int BSC1_DLEN	;
volatile unsigned int BSC1_A		;
volatile unsigned int BSC1_FIFO	;
volatile unsigned int BSC1_DIV	;
volatile unsigned int BSC1_DEL	;
volatile unsigned int BSC1_CLKT	;
};
