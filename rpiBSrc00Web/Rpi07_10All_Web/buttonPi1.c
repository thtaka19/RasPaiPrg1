/**********************************************************************
 *
 * Filename:    buttonPi1.c
 * 
 * Description: Button device driver.
 *
 * Notes:       This file is specific to the Raspberry Pi1 board.
 *		Now only (SW1 GPIO18) is Enable.
 *		If you want other Sws(SW0,SW2,SW3),Correct unsigned int buttonRead(void).
 *              	(SW0 GPIO13,sW1 gpio18,sW2 GPIO19,sW3 gpio26,)
 * 
 **********************************************************************/

#include "gpio_LedAddress.h"
/***  rpi_periAddress00.h  Define
// ********  Rsp. Pi1  ***
#define GPFSEL1  0x20200004
#define GPFSEL2  0x20200008

#define GPSET0	 0x2020001C
#define GPCLR0	 0x20200028
#define GPLEV0	 0x20200034

#define GPPUD	 0x20200094
#define GPPUDCLK0	 0x20200098
***/

/********  Rsp. Pi2 Pi3  ***
#define GPFSEL1  0x3F200004
#define GPFSEL2  0x3F200008

#define GPSET0	 0x3F20001C
#define GPCLR0	 0x3F200028
#define GPLEV0	 0x3F200034

#define GPPUD	0x3F200094
#define GPPUDCLK0	 0x3F200098
***/
#define GPIO_INPUT    0x0       //  入力
#define GPIO_PULLDOWN 0x1
#define GPIO_PULLUP   0x2

#define TRUE            1
#define FALSE           0
#define HIGH		1
#define LOW		0

/**********************************************************************
 *
 * Function:    buttonDebounce
 *
 * Description: This function gets the current state of the button.
 *
 * Notes:       This function is specific to the Raspberry Pi board. The
 *              default state on the button input signals is high.
 *              When a button is pressed, the input signal goes low.
 *
 * Returns:     The current state of the SW0 button.
 *
 **********************************************************************/
//unsigned int SwChickBtn( unsigned int );
 
unsigned int buttonRead(void) {
        int GPIONo[] ={13,18,19,26,0 };//SW1: GPIO13, SW2: GPIO18, ...SW4 :GPIO26;0:dummy
	unsigned int SW_status0,SW_status ;
	static int i1 = 0; 
SW_status = 0;
// 	SW_status0 = (*(volatile unsigned int *)GPLEV0 & (0x01 << GPIONo[0]));
	SW_status0 = gpio_read(GPIONo[0]);
 	if(SW_status0 == LOW){ SW_status = SW_status | 0x01 ; }  // SW4 On

 	SW_status0 =  gpio_read(GPIONo[1]);
 	if(SW_status0 == LOW){  // SW1(PIO18) On ??
	 SW_status = SW_status | 0x02 ; 
	}  // SW1 On

 	SW_status0 = gpio_read(GPIONo[2]);
 	if(SW_status0 == LOW){ 
	  SW_status = SW_status | 0x04 ; }  // SW2 On

	return SW_status;	
}

/**********************************************************************
 *
 * Function:    buttonDebounce
 *
 * Description: This function debounces buttons.
 *
 * Notes:       
 *
 * Returns:     TRUE if the button edge is detected, otherwise
 *              FALSE is returned.
 *
 **********************************************************************/ 
int buttonDebounce(void)
{
    static int buttonState = 0;
    int pinState;    

    pinState = buttonRead();// 0x01 or 0
    /* Store the current debounce status. */
    buttonState = ((buttonState << 1) | pinState | 0xE000);
    if (buttonState == 0xF000)
{
        return TRUE;
}
    return FALSE;
}

/*************************************************************************/
void buttonInit(void)
{
       int GPIONo[] ={0,18,19,26,13 };//0:Dummy; SW1: GPIO18 ...SW4 :GPIO13

gpio_configure(18, GPIO_INPUT);
gpio_configure(19, GPIO_INPUT);
gpio_configure(13, GPIO_INPUT);

	gpio_configure_pull (18,GPIO_PULLUP );
	gpio_configure_pull (19,GPIO_PULLUP );	
	gpio_configure_pull (13,GPIO_PULLUP );	
}

