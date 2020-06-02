/**********************************************************************
 *
 * Filename:    button.h
 * 
 * Description: Header file for button device driver.
 *
 **********************************************************************/

#ifndef _BUTTON_H
#define _BUTTON_H

#define TRUE            1

#define FALSE           0


int buttonDebounce(void);
uint8_t buttonRead(void);
void buttonInit(void);
#endif /* _BUTTON_H */
