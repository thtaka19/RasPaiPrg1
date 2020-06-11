/**********************************************************************
 *
 * Filename:    led.h
 * 
 * Description: Header file for LED device driver.
 *
 * Notes:       
 **********************************************************************/

#ifndef _LED_H
#define _LED_H

void ledInit(void);
void ledToggle(void);
void ledTogglePin(int );
void ledOn(unsigned int );
void ledOff(unsigned int );
void ledTogglePi2(void);
#endif /* _LED_H */
