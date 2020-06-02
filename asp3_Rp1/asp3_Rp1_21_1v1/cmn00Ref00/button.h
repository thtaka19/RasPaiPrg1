/**********************************************************************
 *
 * Filename:    button.h
 * 
 * Description: Header file for button device driver.
 *
 * Notes:       
 **********************************************************************/

#ifndef _BUTTON_H
#define _BUTTON_H
/***
#define TRUE            1
#define FALSE           0
***/

int buttonDebounce(void);
void buttonInit(void);
unsigned int buttonRead(void);
#endif /* _BUTTON_H */
