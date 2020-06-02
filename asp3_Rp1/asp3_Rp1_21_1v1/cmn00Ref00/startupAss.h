/**********************************************************************
 *
 * Filename:    startupAss.h
 * 
 * Description:  Header file for startup01.S,startup23.S, and startupAdd.s functions.
 * Notes:       
 *
 **********************************************************************/

#ifndef _STARTUPASS_H
#define _STARTUPASS_H

//  startup01.S or startup23.S
unsigned int getmode(void);
void enable_IRQ(void);
void disable_IRQ(void);

//  startupadd.S
void interruptDisable(void);
void interruptEnable(void);
unsigned int  readVectorBaseRegister(void);
void writeVectorBaseRegister(int);
void setHighVector(void);
void setLowVector(void);
unsigned int  readSCTLR(void);
void disableInstructionCache(void);
void disableDataCache(void);
void disableMMU(void);

#endif /* _STARTUPASS_H */
