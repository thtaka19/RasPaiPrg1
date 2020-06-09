#include "raspGPIO.h"  // for Linux, !!

//

int main () {
int i=0;	
     printf("GPIO1_Lx Start v1\n");
//	struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
    gpio_init();                        //  オマジナイ 
	gpio_configure(20, GPIO_OUTPUT);        //  GPIO_20 を出力に設定 
	gpio_configure(47, GPIO_OUTPUT);     //  GPIO_47 を出力に設定 オンボードLED
   while (i <20) { 
   i++;
 ledTogglePi0();
         gpio_set(20);                   //  1 を出力（3.3V）  
//		 usleep(500000);                 //  0.5秒待ち 
	delay00(5000);
  ledTogglePi0();		 
		 gpio_clear(20);                 //  0 を出力（0V） 
//		 usleep(500000);                 //  0.5秒待ち  
	delay00(5000);		 
}
 main7100();
 } 
