#ifndef LED_ADDRESS00_H
#define LED_ADDRESS00_H 

// GPIO Peripheral for Led.c, button.c
/******* Pai1   B+ ,  Zero **/
#define GPFSEL0  0x20200000
#define GPFSEL1  0x20200004
#define GPFSEL2  0x20200008
#define GPFSEL3  0x2020000c
#define GPFSEL4  0x20200010

#define GPSET0	 0x2020001C
#define GPSET1	 0x20200020
#define GPCLR0	 0x20200028
#define GPCLR1	 0x2020002c

#define GPLEV0   0x20200034 // Input
#define GPLEV1   0x20200038 // Input 


// ********  Rsp. Pi1  *** OutPut
#define GPPUD	 0x20200094
#define GPPUDCLK0	 0x20200098
// ********  Rsp. Pi1  *** System cloc
#define SYST_CLO	0x20003004  // System clock LOW
#define SYST_CHI	0x20003008  // System clock HIGH
/******* Pai2  Pai 3 
#define GPFSEL0		0x3F200000
#define GPFSEL1		0x3F200004
#define GPFSEL2		0x3F200008
#define GPFSEL3		0x3F20000c
#define GPFSEL4 	0x3F200010

#define GPSET0	 	0x3F20001C
#define GPSET1  	0x3F200020

#define GPCLR0	 	0x3F200028
#define GPCLR1  	0x3F20002C

#define GPLEV0		0x3F200034  // Input 
#define GPLEV1		0x3F200038  // Input 

// *******  Rsp. Pi2 Pi3  *** Output
#define GPPUD	0x3F200094
#define GPPUDCLK0	 0x3F200098

// ********  Rsp. Pi2 Pi3 *** System cloc
#define SYST_CLO	0x3F003004  // System clock LOW
#define SYST_CHI	0x3F003008  // System clock HIGH

****/

#endif

