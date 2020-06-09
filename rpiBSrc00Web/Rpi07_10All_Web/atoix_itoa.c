/**********************************************************************
 *
 * Filename:    atoix_itoa 
 * 
 * Description: atoi,itoa,itoax convert. And put_Xvalue
 * Notes:       
 * 
 **********************************************************************/
#include "mini_serial.h"
#ifndef NULL
#define NULL            (void *)0
#endif

int atoi0(char *str)
 {
	int cnt;
	int num=0;
	for (cnt = 0; (str[cnt] >= '0') && (str[cnt] <= '9') ; cnt++){
	num = 10 * num + (str[cnt] - '0');
	}
	return num ;
 }

void itoa0(int num, char * numC) 
{
	int i,idx;
char invNumC[10];
	if(num <=0){
		numC[0] = '0';
		numC[1] = '\0';
		return;
	}
	idx=0;
	for(i=0;i<6 && (num > 0);i++) {		
		invNumC[idx++]='0'+num%10;
		num=num/10;		
	}
	for(i=0;i<idx;i++)numC[i]=invNumC[idx-i-1];
	numC[i]='\0';	
}
/* HexDesimal Style*/
void itoaxval0(unsigned long value, char * xvalC)
{
  int column = 16;
  int j;
  char buf[18];
  char *p,*i,*idx;
  p = buf + sizeof(buf) - 1;
  idx = p;
  *(p--) = '\0';

  if (!value && !column)
    column++;

  while (value > 0 &&  column > 0) {
    *(p--) = "0123456789abcdef"[value & 0xf];
    value >>= 4;
    column--;
  }
 j=0;
  for(i=(p+1);i<=idx;i++) xvalC[j++]= *i;
 return;
}

void putxval0(unsigned long value, int column)
{
  char buf[18];
  char *p;
  if (column > 16) column = 16;
  if (column < 1)  column = 1;
  p = buf + sizeof(buf) - 1;
  *(p--) = '\0';
  
  if (!value && !column)
    column++;

  while (value || column) {
    *(p--) = "0123456789abcdef"[value & 0xf];
    value >>= 4;
    if (column) column--;
  }
  //puts(p + 1);
   m_serialPutStr(p+1);
  return ;
}

