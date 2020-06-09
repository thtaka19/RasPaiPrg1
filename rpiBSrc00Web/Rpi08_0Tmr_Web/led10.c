/**********************************************************************
 *
 * Filename:    led10.c 
 * 		only [#include "gpio_LedAddress.h" is not same
 * Description: LED device driver.
 *
 * Notes:  Gpio20,Gpio21 pin on the target Raspberry Pi board are connecter Leds. 
 *         On board Led: PIO47    Pi1 B+,Pi2 are HIGH on; Pi Zero is Low on.
 *	
 **********************************************************************/

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
#define GPIO_OUTPUT   0x1       //  出力
#define LED_GREEN16_DIR   	(0x01 << (3*6)) // Poet16(0+16)
#define LED_GREEN20_DIR   	(0x01 << (3*(20-20))) // Port20(20+0) 
#define LED_RED021_DIR      	(0x01 << (3*(21-20))) // Port21(20+1)

#define LED_GREEN16   		(0x01 << 16) 	// Port16(10+6)
#define LED_GREEN20   		(0x01 << 20) 	// Port20
#define LED_RED21     		(0x01 << 21) 	// Port21

#define LED_ACT2_DIR      	0x01 << (3*7)   // GPIO47 =40+7  Pi1 B+,Pi2,and Zero Act(on Board)LED

#define LED_ACT2      	(0x01 << 15)   // GPIO47 =32+15


/**********************************************************************
 *
 * Function:    ledInit
 *
 * Description: Initialize the GPIO pin that controls the LED.
 *
 * Notes:       This function is specific to the Raspberry Pi board.
 *		Gpio20,Gpio21,and Gpio47
 * Returns:     None.
 *
 **********************************************************************/
void ledInit(void)
{
/*I/O board Port Initialoze 2015 */

gpio_configure(20, GPIO_OUTPUT);
gpio_configure(21, GPIO_OUTPUT);
gpio_configure(47, GPIO_OUTPUT);


	*(volatile unsigned int *)GPCLR0 = LED_GREEN20;// LED light Off
	*(volatile unsigned int *)GPCLR0 = LED_RED21;  // LED light Off
gpio_clear(20);
gpio_clear(21);
	}
/**********************************************************************
 *
 * Function:    ledToggle
 *
 * Description: Toggle the state of one LED.
 *
 * Notes:       This function is specific to the Raspberry Pi board.
 *     		Only for GPIO16,GPIO20,GPIO21, and GPIO47(On Board)
 * Returns:     None. 
 *
 **********************************************************************/
// static unsigned int ledcnt = 0;

void ledTogglePin(int );

void ledTogglePi2(void) {	//Only for pi1 B+,Pi2 ,and Zero  on Board LED

	   // GPIO47 =32+15 --> (0x01 << 15)
	if( gpio_read(47) ) // If GPIO47 On 
		gpio_clear(47); // 	GPIO47 clear
	 else 
		gpio_set(47);// 		GPIO47 Set
}
void ledToggle(void) {	//Only for Raspberry Pi1 and Pi2  not for Pi3

   	ledTogglePin(20);
	ledTogglePin(21);

	ledTogglePi2() ;
}

void ledTogglePin(int PinNo) {	//Only for GPIO 16,20,21
//	struct rpiGpio * rpiGpio = (struct rpiGpio*)RPI_GPIO_BASE;
   if(  (PinNo == 20) || (PinNo == 21) ) {

	if( gpio_read(PinNo) ) // If GPIO47 On 
		gpio_clear(PinNo); // 	GPIO47 clear
	 else 
		gpio_set(PinNo);// 		GPIO47 Set
   }

}
/**********************************************************************
 *
 * Function:    ledOn
 *
 * Description: Turn on the specified LEDs.
 *		Only for GPIO16,GPIO20,GPIO21
 *
 * Returns:     None.
 *
 **********************************************************************/
void ledOn(unsigned int mask)
{
 if (mask  & LED_GREEN20) {gpio_set(20); }
 if (mask  & LED_RED21)   {gpio_set(21); }
 if (mask  & LED_ACT2)    {gpio_set(47); }
}

/**********************************************************************
 *
 * Function:    ledOff
 *
 * Description: Turn off the specified LEDs.
 *		Only for GPIO16,GPIO20,GPIO21
 *
 * Returns:     None.
 *
 **********************************************************************/
void ledOff(unsigned int mask)
{

 if (mask  & LED_GREEN20) {gpio_clear(20); }
 if (mask  & LED_RED21)   {gpio_clear(21); }
 if (mask  & LED_ACT2)    {gpio_clear(47); }
}


