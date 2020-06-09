//#include "raspGPIO.h"  // for Linux, !!
#include <stdio.h>

//  gpio_init: GPIO 初期化（最初に１度だけ呼び出すこと）
void gpio_init();
//  gpio_configure: ピン機能を設定する（ピンを使用する前に必ず設定）
//      pin : (P1) 2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27
//            (P5) 28,29,30,31
//      mode: GPIO_INPUT, _OUTPUT, _ALT0, _ALT1, _ALT2, _ALT3, _ALT4, _ALT5
//  ピン機能（BCM2835）
#define GPIO_INPUT    0x0       //  入力
#define GPIO_OUTPUT   0x1       //  出力

void gpio_configure(int pin, int mode);
//  gpio_set/clear: ピンをセット (3.3V)，クリア (0V)
void gpio_set(int pin);
void gpio_clear(int pin);

//  gpio_read: ピンの読み取り（3.3V->1, 0V->0)
int gpio_read (int pin);
void delay00(int milliseconds);
void ledTogglePi0(void);////  GPIO_47 (Pai Zero のオンボードLED)をオン、オフ


//

int main () { 
     printf("Led On/Off Rpi90_0Base for Linux  Start v1\n");
//	struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
    gpio_init();                        //  オマジナイ レジスタ群のアドレス情報を得る。（Ｌｉｎｕｘ上の表現）
	gpio_configure(20, GPIO_OUTPUT);        //  GPIO_20 を出力に設定 
	gpio_configure(47, GPIO_OUTPUT);     //  GPIO_47 を出力に設定 オンボードLED
   while (1) { 
 ledTogglePi0();//オンボードLEDのオンオフ　反転
         gpio_set(20);                   // ＧＰＩＯ＿２０ピンに　 1 を出力（3.3V）  
//		 usleep(500000);                 //  0.5秒待ち 
	delay00(5000);
  ledTogglePi0();//オンボードLEDのオンオフ　反転		 
		 gpio_clear(20);                 //  ＧＰＩＯ＿２０ピンに0 を出力（0V） 
//		 usleep(500000);                 //  0.5秒待ち  
	delay00(5000);		 
}
 } 
