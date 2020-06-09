cmn00 is not same for (Pi Zero , Pi1 ) and( Pi2, Pi3)
This cmn00 is for (Pi Zero , Pi1 ).

So 
---<rpi_periAddress00.h>---
for (Pi Zero , Pi1 )
 #define PHY_PERI_ADDR(x) (0x20000000 + (x))
But for ( Pi2, Pi3)
// #define PHY_PERI_ADDR(x) (0x3F000000 + (x))  for Pi2 , Pi3

---<gpio_LedAddress.h>---
// GPIO Peripheral for Led10.c, button.c
for (Pi Zero , Pi1 )
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

But for ( Pi2, Pi3)
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
 *******/ 
//  ********  Rsp. Pi2 Pi3  *** Output
#define GPPUD	0x3F200094
#define GPPUDCLK0	 0x3F200098
****/

