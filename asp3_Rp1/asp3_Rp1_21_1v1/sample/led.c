/**********************************************************************
 *
 * Filename:    led.c Chapter3 Plus --> Same as chapter6
 * 
 * Description: LED device driver.
 *
 * Notes:       This file is specific to the Raspberry Pai Zero GPIO 20 - GPIO 29 .
 * 
 *
 **********************************************************************/

//#define ABWCR (*(unsigned char *) 0xFEE020)

//#define GPIO_4_DIRECTION_REG 	(*(unsigned char *) 0xFEE003)
//#define GPIO_4_REG  		(*(unsigned char *) 0xFFFFD3)
#define GPFSEL1  0x20200004
#define GPFSEL2  0x20200008
#define GPFSEL4  0x20200010

#define GPSET0	 0x2020001C
#define GPSET1	 0x20200020
#define GPCLR0	 0x20200028
#define GPCLR1	 0x2020002c

#define GPLEV0   0x20200034
#define GPLEV1   0x20200038

#define LED_GREEN20   (0x01 << 20) // GPIO 20
#define LED_RED21     (0x01 << 21)  // GPIO 21
#define LED_ON        (1)
#define LED_OFF       (0)

//#define LED_GREEN   (0x80) // bit:7
//#define LED_RED     (0x40)  //bit:6
//#define CLEAR	    (0x00)
void ledOn(unsigned int mask);
void ledOff(unsigned int mask);
/**********************************************************************
 *
 * Function:    ledInit
 *
 * Description: Initialize the GPIO pin that controls the LED.
 *
 * 
 * Returns:     None.
 *
 **********************************************************************/
int led_Grn , led_Red ;

void ledInit(void)
{
/*I/O board Port Initialoze 2015 */
//ABWCR = 0xff ;//  8 bit mode
	// All Input
	*(volatile unsigned int *)GPFSEL2 = 0; // GPIO 20-29

	*(volatile unsigned int *)GPFSEL4 |= (1 << (47-40)*3);	//21 GPIO47 // Raspberry PI B+ /PI2 B 
	// GPIO20,21をOutputにセット
	*(volatile unsigned int *)GPFSEL2 |= 0x01 << (3*0);// GPIO 20 LED Green
	*(volatile unsigned int *)GPFSEL2 |= 0x01 << (3*1);// GPIO 21 LED Red
//GPIO_4_DIRECTION_REG |= (LED_GREEN|LED_RED);// Set  Led OutPut Mode
//GPIO_4_DIRECTION_REG = 0xff; //  LCD  Set Here ?? 2016 01 
  led_Grn = LED_ON;
  led_Red = LED_OFF;
*(volatile unsigned int *)GPSET0 = ( 0x01 << 20);
// *(volatile unsigned int *)GPSET0 = 0x00100000 ;
}


/**********************************************************************
 *
 * Function:    ledToggle  Green Led 
 *
 * Description: Toggle the state of one LED.
 *
 *
 * Returns:     None. 
 *
 **********************************************************************/

void ledToggle(void)
{
//  Toggle Green
    /* Check the current state of the LED control pin. Then change the
     * state accordingly. */


 if(led_Grn == LED_OFF)  { ledOn(LED_GREEN20);}

 else {ledOff((unsigned int)LED_GREEN20);}

}
/**********************************************************************/

void ledToggleRed(void)
{
//  Toggle Red
    /* Check the current state of the LED control pin. Then change the
     * state accordingly. */ 

 if(led_Red== LED_OFF)  { ledOn(LED_RED21);}

 else {ledOff(LED_RED21);led_Red = LED_OFF;}
}

void ledToggle1(void)
{
//  Toggle Both (Green and Red)
    /* Check the current state of the LED control pin. Then change the
     * state accordingly. */


 if(led_Grn== LED_OFF) {	
  ledOn(LED_GREEN20);
  ledOn(LED_RED21);
 }
 else {
  ledOff(LED_GREEN20);
  ledOff(LED_RED21);
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
 *(volatile unsigned int *)GPSET0 =  mask; 
// *(volatile unsigned int *)GPSET0 |=  mask;

 if (mask == LED_GREEN20) led_Grn = LED_ON;
 else led_Red = LED_ON;
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
*(volatile unsigned int *)GPCLR0 =  mask; 
 // *(volatile unsigned int *)GPCLR0 |=  mask;  


 if (mask == LED_GREEN20) led_Grn = LED_OFF;
 else led_Red = LED_OFF;
 ;
}

void ledToggle47(void) {
	//Only for Raspberry Pi1 and Pi2  not for Pi3
	//struct rpiGpio * rpiGpio = (struct rpiGpio*)RPI_GPIO_BASE;

//	if( *(volatile unsigned int *)GPLEV0 & (1 << 16) ) {	// Raspberry PI B 
//		*(volatile unsigned int *)GPCLR0 = (1 << 16);
//	} else {
//		*(volatile unsigned int *)GPSET0 = (1 << 16);
//	}

	if( *(volatile unsigned int *)GPLEV1 & (1 << (47-32)) ) {	// Raspberry PI B+ /PI2 B Zero
		*(volatile unsigned int *)GPCLR1 = (1 << (47-32));
	} else {
		*(volatile unsigned int *)GPSET1 = (1 << (47-32));
	}
} 

void ledOn47(void) {
	*(volatile unsigned int *)GPSET1 = (1 << (47-32));
}
void ledOff47(void) {
	*(volatile unsigned int *)GPCLR1 = (1 << (47-32));
}

