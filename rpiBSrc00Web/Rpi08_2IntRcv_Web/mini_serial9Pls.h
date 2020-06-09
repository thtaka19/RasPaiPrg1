#ifndef MINI_SERIAL_H
#define MINI_SERIAL_H

void m_serialInit(void);
void m_serialRcvInterrupt(void);
void m_Serial_begin(int);

int m_serialGetChar( void );
void m_serialPutChar (int );
void m_serialPutStr(char const *);

void m_putCharI(int );
int  m_getCharI(void);
char *m_serialGetStr(char *,int);

void m_serialInitIrcv(void);
void m_serialInitIsndrcv(void);
void m_serialPutCharI(int data);
int m_serialGetCharI(void);
#endif
