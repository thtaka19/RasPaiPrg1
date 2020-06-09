/**********************************************************************
 *
 * Filename:    buzzer.c
 * 
 * Description: Buzzer device driver.
 *
 * Notes:       This file is specific to the Raspberry Pi board.
 **********************************************************************/

#include "buzzer.h"

void m_serialPutStr(char const *);

/**********************************************************************
 *
 * Function:    buzzerInit
 *
 * Description: Initialize the GPIO pin that controls the buzzer.
 * Notes:       This function is specific to the Raspberry Pi board.
 * Returns:     None.
 *
 **********************************************************************/
void buzzerInit(void)
{

m_serialPutStr("buzzerInit(void) Called Do None \r\n");
}

/**********************************************************************
 *
 * Function:    buzzerToggle
 * Description: Toggle the state of the buzzer.
 * Notes:       This function is specific to the Raspberry Pi board.
 * Returns:     None.
 *
 **********************************************************************/
void buzzerToggle(void)
{
 
	m_serialPutStr("buzzerToggle(void) Called Do None \r\n");
}

