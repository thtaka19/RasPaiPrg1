/**********************************************************************
 *
 * Filename:    commands.h
 * 
 * Description: Header file for Monitor and Control program
 *              command functions.
 *
 * Notes:       
 * 
 * 
 **********************************************************************/

#ifndef _COMMANDS_H
#define _COMMANDS_H


void commandsLed(void);
void commandsBuzzer(void);
void commandsHelp(void);
void commandsLcdHello(void);
void commandsLcdData( char *);
void commandsLcdCler(void);
void commandsSw(void);
void commandsAdLcd(void);
void commandsTemp(void);
void commandsLcdDa0(char *);
void commandsLcdDa1(char *);
void commandsLcdDa(int,char *);
void commandsTimer(void);
#endif /* _COMMANDS_H */
