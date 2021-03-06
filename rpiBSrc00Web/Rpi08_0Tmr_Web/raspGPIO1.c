//
//  raspGPIO: Raspberry Pi GPIO module
//      xkozima@myu.ac.jp  Plus(2018)
//#include "raspGPIO.h"  // Diffence for Linux, for BareMetal!!
#include "io10.h"
#define CYCLES_PER_MS               (3000) // 2017 05
//  レジスタブロックの物理アドレス
#define PERI_BASE     0x20000000
#define GPIO_BASE     (PERI_BASE + 0x200000)
#define BLOCK_SIZE    4096

#define GPIO_INPUT    0x0       //  入力
#define GPIO_OUTPUT   0x1       //  出力
#define GPIO_ALT0     0x4
#define GPIO_ALT1     0x5
#define GPIO_ALT2     0x6
#define GPIO_ALT3     0x7
#define GPIO_ALT4     0x3
#define GPIO_ALT5     0x2
//  GPIO 関連レジスタ (volatile＝必ず実メモリにアクセスさせる)
static volatile unsigned int *Gpio;
static volatile struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
//  GPIO 初期化（最初に１度だけ呼び出すこと）  For Linux Self.

void delay00(int milliseconds)
{
    long volatile cycles = milliseconds;
	int volatile  cycle0 = CYCLES_PER_MS;
     
    while (cycles != 0) {
        cycles--;
		cycle0 = CYCLES_PER_MS;
	  while(cycle0 != 0)
		  cycle0--;
	}
}
//  ピン機能の設定（ピンを使用する前に必ず設定）
//      pin :  2,3,4,7,8,9,10,11,14,15,17,18,22,23,24,25,27
//             28,29,30,31  , 47
//      mode: GPIO_INPUT, _OUTPUT, _ALT0, _ALT1, _ALT2, _ALT3, _ALT4, _ALT5
void gpio_configure(int pin, int mode)
{
    //  ピン番号チェック

     if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_configure)\n");

     }

    //  レジスタ番号（index）と３ビットマスクを生成
    int index = pin / 10;
    unsigned int mask = ~(0x7 << ((pin % 10) * 3));
    //  GPFSEL0/1 の該当する FSEL (3bit) のみを書き換え

rpiGpio->GPFSEL[index]= (rpiGpio->GPFSEL[index] & mask) | ((mode & 0x7) << ((pin % 10) * 3));
	}

//  ピンをセット (3.3V)，クリア (0V)
void gpio_set(int pin)
{
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
	
    if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_set)\n");

    }
    //  ピンに１を出力（3.3V 出力）

rpiGpio->GPSET[pin/32] = 0x1 << (pin%32); //  GPSET0 or GPSET1	
}
void gpio_clear(int pin)
{
   
    if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_clear)\n");

    }
    //  ピンに０を出力（0V 出力）
//    Gpio[10] = 0x1 << pin;  //  GPCLR0
	rpiGpio->GPCLR[pin/32] = 0x1 << (pin%32); //  GPCLR0 or GPCLR1	
}

//  ピン状態の読み取り（3.3V->1, 0V->0）
int gpio_read (int pin)
{
	int tst;
  
    if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_read)\n");

    }
    //  ピンの電圧を返す（入力/出力を問わず 3.3V なら 1，0V なら 0）
//  return (Gpio[13] & (0x1 << pin)) != 0;  //  GPLEV0
	tst =  (rpiGpio->GPLEV[pin/32] & (0x1 << pin%32)) ;
	return tst != 0;
}
void ledTogglePi0(void) {	//GPIO47 pin:Only for pi1 B+,Pi2 ,and Zero  on Board LED
   // GPIO47 =32+15 --> (0x01 << 15)
	if( gpio_read(47) ) // If GPIO47 On 
		gpio_clear(47); // 	GPIO47 clear
	 else 
		gpio_set(47);// 		GPIO47 Set
}
//  プルアップ/ダウン抵抗の設定
//      pullmode: GPIO_PULLNONE/PULLDOWN/PULLUP
void gpio_configure_pull (int pin, int pullmode)
{
  
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_configure_pull)\n");

    }
    //  プルモード (2bit)を書き込む NONE/DOWN/UP
	
//    Gpio[37] = pullmode & 0x3;  //  GPPUD
rpiGpio->GPPUD = pullmode & 0x3;
delay00(1);//    usleep(1);
    //  ピンにクロックを供給（前後にウェイト）
//    Gpio[38] = 0x1 << pin;      //  GPPUDCLK0
rpiGpio->GPPUDCLK[0] = 0x1 << pin%32; 
delay00(1);//     usleep(1);
    //  プルモード・クロック状態をクリアして終了
//    Gpio[37] = 0;
//    Gpio[38] = 0;
rpiGpio->GPPUD = 0;
rpiGpio->GPPUDCLK[0] = 0;
}

//
