/**********************************************************************
 *
 * Filename:    led10.c Same as Chapter3
 * 
 * Description: LED device driver.
 *
 * Notes:       This file is specific to the Pai2,3.
 * 
 *
 **********************************************************************/
//#define GPIO_4_DIRECTION_REG 	(*(unsigned char *) 0xFEE003)
//#define GPIO_4_REG  		(*(unsigned char *) 0xFFFFD3)
#include "gpio_LedAddress.h"
/***  gpio_LedAddress.h  Define

// ******* Pai1   B+ ,  Zero **
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

/*  2017 TT */
/* Number of decrement-and-test cycles. */

#define LED_GREEN16_DIR   	(0x01 << (3*6)) // Port16(10+6) OnBord_Led : Pai1 B
#define LED_GREEN20_DIR   	(0x01 << (3*(20-20))) // Port20(20+0) 
#define LED_RED021_DIR      	(0x01 << (3*(21-20))) // Port21(20+1)



#define LED_GREEN16   		(0x01 << 16) 	// Port16(10+6)
#define LED_GREEN20   		(0x01 << 20) 	// Port20
#define LED_RED21     		(0x01 << 21) 	// Port21


#define LED_ACT1_DIR      	0x01 << (3*6)   // GPIO16 =10+6  Pi1 B Act(on Board)LED
#define LED_ACT2_DIR      	0x01 << (3*7)   // GPIO47 =40+7  Pi1 B+,Pi2,and Zero Act(on Board)LED

#define LED_ACT1      	(0x01 << 16)   // GPIO16 =10+6
#define LED_ACT2      	(0x01 << 15)   // GPIO47 =32+15

#define LED_ON  		1
#define LED_OFF  		0

//#define ABWCR (*(unsigned char *) 0xFEE020)


/**********************************************************************
 *
 * Function:    ledInit
 *
 * Description: Initialize the GPIO pin that controls the LED.
 *
 * Notes:       This function is specific to the Raspberry Pi board.
 *
 * Returns:     None.
 *
 **********************************************************************/


void ledInit(void)
{
/*I/O board Port Initialoze 2015 */

	*(volatile unsigned int *)GPFSEL2 |= LED_GREEN20_DIR ;//port20 0x01 << (3*1)
	*(volatile unsigned int *)GPFSEL2 |= LED_RED021_DIR;//port21 0x01 << (3*0);//

	*(volatile unsigned int *)GPFSEL1 |= LED_ACT1_DIR;   // GPIO16  =10+6
	*(volatile unsigned int *)GPFSEL4 |= LED_ACT2_DIR;   // GPIO47  =40+7 Pi1 B+,Pi2,Zero on Board



	*(volatile unsigned int *)GPSET0 = 0;
	*(volatile unsigned int *)GPCLR0 =0 ;

//	*(volatile unsigned int *)GPSET0 = LED_GREEN16;
//	*(volatile unsigned int *)GPSET0 = LED_GREEN20;
	*(volatile unsigned int *)GPSET0 = LED_GREEN16;// Pai1 B LED light On
	*(volatile unsigned int *)GPCLR0 = LED_GREEN20;// Zero LED light On ; Pai1 B+,Pai2 LED light Off


}


/**********************************************************************
 *
 * Function:    ledToggle
 *
 * Description: Toggle the state of one LED.
 *
 * Notes:       This function is specific to the Raspberry Pi board.
 *
 * Returns:     None. 
 *
 **********************************************************************/
// static unsigned int ledcnt = 0;
int stateLED = 0;
int led_Grn = 0 ;// status Green Led
int led_Red =0;
void ledTogglePin(int );
void ledToggleOld() {	//Only for Raspberry Pi1 and Pi2  not for Pi3

 // Raspberry PI B+ , PI2 B , Zero : GPIO 47 on BoardLed
	if( *(volatile unsigned int *)GPLEV1 & (1 << 15) ) {	// Raspberry PI B+ /PI2 B 
		*(volatile unsigned int *)GPCLR1 = (1 << 15);
	} else {
		*(volatile unsigned int *)GPSET1 = (1 << 15);
	}
}

void ledTogglePi1(void) {	//Only for Pi1 B on Board LED or GPIO16

	if( *(volatile unsigned int *)GPLEV0 & LED_ACT1 )  
		*(volatile unsigned int *)GPCLR0 = LED_ACT1;
	 else 
		*(volatile unsigned int *)GPSET0 = LED_ACT1;
}

void ledTogglePi2(void) {	//Only for pi1 B+,Pi2 ,and Zero  on Board LED

	if( *(volatile unsigned int *)GPLEV1 & LED_ACT2 )  
		*(volatile unsigned int *)GPCLR1 = LED_ACT2;

	 else 
		*(volatile unsigned int *)GPSET1 = LED_ACT2;
}
void ledToggle(void) {	//Only for Raspberry Pi1 and Pi2  not for Pi3

   	ledTogglePin(20);
	ledTogglePin(21);

	ledTogglePi1();
	ledTogglePi2() ;
}

void ledTogglePin(int PinNo) {	//Only for Raspberry Pi1 and Pi2  not for Pi3
//	struct rpiGpio * rpiGpio = (struct rpiGpio*)RPI_GPIO_BASE;
   if( (PinNo == 16) || (PinNo == 20) || (PinNo == 21) ) {
	if( *(volatile unsigned int *)GPLEV0 & (1 << PinNo) ) {	 
		*(volatile unsigned int *)GPCLR0 = (1 << PinNo);
	} else {
		*(volatile unsigned int *)GPSET0 = (1 << PinNo);
	}
   }


}
/**********************************************************************
 *
 * Function:    ledOn
 *
 * Description: Turn on the specified LEDs.
 *
 *
 * Returns:     None.
 *
 **********************************************************************/
void ledOn(unsigned int mask)
{
 if( (mask & LED_GREEN16)| (mask & LED_GREEN20)| (mask & LED_RED21  )) {

 *(volatile unsigned int *)GPSET0 =  mask; 
 
 }
 else if ((mask & LED_ACT2)) *(volatile unsigned int *)GPSET1 =  mask; 
      else *(volatile unsigned int *)GPSET0 =  LED_GREEN16; 
 if (mask & LED_GREEN20) led_Grn = LED_ON;
 if (mask & LED_RED21  ) led_Red = LED_ON;
 
}


/**********************************************************************
 *
 * Function:    ledOff
 *
 * Description: Turn off the specified LEDs.
 *
 *
 * Returns:     None.
 *
 **********************************************************************/
void ledOff(unsigned int mask)
{

 if((mask & LED_GREEN16)| (mask & LED_GREEN20)| (mask & LED_RED21  )) {
   *(volatile unsigned int *)GPCLR0 =  mask;  
 }
 else if ((mask & LED_ACT2)) *(volatile unsigned int *)GPCLR1 =  mask; 
      else *(volatile unsigned int *)GPCLR0 =  LED_GREEN16; 

 if (mask & LED_GREEN20) led_Grn = LED_OFF;
 if (mask & LED_RED21  ) led_Red = LED_OFF;

}


