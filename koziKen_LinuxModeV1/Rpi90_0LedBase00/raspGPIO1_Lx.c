//
//  raspGPIO: Raspberry Pi GPIO module
//      xkozima@myu.ac.jp  Plus(2018)
//#include "raspGPIO.h"  // for Linux, !!
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
//#include "io10.h"
struct rpiGpio{
	volatile unsigned int    GPFSEL[6];

    volatile const unsigned int    Reserved0;
volatile unsigned int    GPSET[2];	

    volatile const unsigned int    Reserved1;
	volatile unsigned int    GPCLR[2];

    volatile const unsigned int    Reserved2;
	    volatile unsigned int    GPLEV[2];

    volatile const unsigned int    Reserved3;
    volatile unsigned int    GPEDS0;
    volatile unsigned int    GPEDS1;
    volatile const unsigned int    Reserved4;
    volatile unsigned int    GPREN0;
    volatile unsigned int    GPREN1;
    volatile const unsigned int    Reserved5;
    volatile unsigned int    GPFEN0;
    volatile unsigned int    GPFEN1;
    volatile const unsigned int    Reserved6;
    volatile unsigned int    GPHEN0;
    volatile unsigned int    GPHEN1;
    volatile const unsigned int    Reserved7;
    volatile unsigned int    GPLEN0;
    volatile unsigned int    GPLEN1;
    volatile const unsigned int    Reserved8;
    volatile unsigned int    GPAREN0;
    volatile unsigned int    GPAREN1;
    volatile const unsigned int    Reserved9;
    volatile unsigned int    GPAFEN0;
    volatile unsigned int    GPAFEN1;
    volatile const unsigned int    Reserved10;
    volatile unsigned int    GPPUD;
	volatile unsigned int    GPPUDCLK[2];	

    volatile const unsigned int    Reserved11;
};
#define PHY_PERI_ADDR(x) (0x20000000 + (x))
//#define	RPI_IO_BASE	(0x20000000)	//Raspberry PI1 B / B+
#define	RPI_IO_BASE  PHY_PERI_ADDR(0x00000000)
#define RPI_UART_BASE	(struct rpiUart *)(RPI_IO_BASE |0x00201000)
#define RPI_GPIO_BASE	(struct rpiGpio *)(RPI_IO_BASE |0x00200000)  

#define CYCLES_PER_MS               (3000) // 2017 05
//  レジスタブロックの物理アドレス
#define PERI_BASE     0x20000000
#define GPIO_BASE     (PERI_BASE + 0x200000)
#define SPI000_BASE     (PERI_BASE + 0x00204000)
#define BSC100_BASE     (PERI_BASE + 0x00804000)
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
static volatile unsigned int *Spi;
static volatile unsigned int *I2c;
static volatile struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
//static	struct rpiSpi0* rpiSpi0= SPI0_BASE;//Spi
//static	struct rpiBsc1* rpiBsc1 = BSC1_BASE;//I2c
//  GPIO 初期化（最初に１度だけ呼び出すこと）  For Linux Self.
//   Only for Linux self 
void gpio_init(void)
{
    //  既に初期化済なら何もしない
    if (Gpio) return;
    //  ここから GPIO 初期化
    int fd;
    void *gpio_map;
    //  /dev/mem（物理メモリデバイス）を開く（sudo が必要）
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("error: cannot open /dev/mem (gpio_init)\n");
        exit(-1);
    }
    //  mmap で GPIO（物理メモリ）を gpio_map（仮想メモリ）に対応づける
    gpio_map = mmap(NULL, BLOCK_SIZE,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, GPIO_BASE );
    if ((int) gpio_map == (int)-1) {
        printf("error: cannot map /dev/mem on the memory (gpio_init)\n");
        exit(-1);
    }
    //  mmap 後は不要な fd をクローズ
    close(fd);
    //  gpio[index]: 整数 uint32 の配列としてレジスタへのアクセスを確立
 //   Gpio = (unsigned int *) gpio_map;
 rpiGpio = (struct rpiGpio *)gpio_map;
}
unsigned int * spi_init(void)
{
    //  既に初期化済なら何もしない
    if (Spi) return (unsigned int *)Spi;
    //  ここから GPIO 初期化
    int fd;
    void *spi_map;
    //  /dev/mem（物理メモリデバイス）を開く（sudo が必要）
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("error: cannot open /dev/mem (spi_init)\n");
        exit(-1);
    }
    //  mmap で GPIO（物理メモリ）を spi_map（仮想メモリ）に対応づける
    spi_map = mmap(NULL, BLOCK_SIZE,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, SPI000_BASE );
    if ((int) spi_map == (int)-1) {
        printf("error: cannot map /dev/mem on the memory (spi_init)\n");
        exit(-1);
    }
    //  mmap 後は不要な fd をクローズ
    close(fd);
    //  gpio[index]: 整数 uint32 の配列としてレジスタへのアクセスを確立
 //   Gpio = (unsigned int *) gpio_map;
 //rpiGpio = (struct rpiGpio *)gpio_map;
    Spi = spi_map;
    return  (unsigned int *) spi_map;
}

unsigned int * i2c_init(void)
{
	    //  既に初期化済なら何もしない
    if (I2c) return (unsigned int *)I2c ;
    //  ここから GPIO 初期化
    int fd;
    void *i2c_map;
    //  /dev/mem（物理メモリデバイス）を開く（sudo が必要）
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf("error: cannot open /dev/mem (i2c_init)\n");
        exit(-1);
    }
    //  mmap で BSC1(i2c)（物理メモリ）を i2c_map（仮想メモリ）に対応づける
    i2c_map = mmap(NULL, BLOCK_SIZE,
                    PROT_READ | PROT_WRITE, MAP_SHARED,
                    fd, BSC100_BASE );
    if ((int) i2c_map == (int)-1) {
        printf("error: cannot map /dev/mem on the memory (i2c_init)\n");
        exit(-1);
    }
    //  mmap 後は不要な fd をクローズ
    close(fd);
    //  gpio[index]: 整数 uint32 の配列としてレジスタへのアクセスを確立
 //   Gpio = (unsigned int *) gpio_map;
 //rpiGpio = (struct rpiGpio *)gpio_map;
 I2c = i2c_map;
  return  (unsigned int *) i2c_map;
}
//
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
//	if(pin != 47){ //Pin47: Only for pi1 B+,Pi2 ,and Zero on Board LED
     if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_configure)\n");
        exit(-1);
     }
//	}
    //  レジスタ番号（index）と３ビットマスクを生成
    int index = pin / 10;
    unsigned int mask = ~(0x7 << ((pin % 10) * 3));
    //  GPFSEL0/1 の該当する FSEL (3bit) のみを書き換え
//    Gpio[index] = (Gpio[index] & mask) | ((mode & 0x7) << ((pin % 10) * 3));
rpiGpio->GPFSEL[index]= (rpiGpio->GPFSEL[index] & mask) | ((mode & 0x7) << ((pin % 10) * 3));
	}

//  ピンをセット (3.3V)，クリア (0V)
void gpio_set(int pin)
{
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
	
    if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_set)\n");
        exit(-1);
    }
    //  ピンに１を出力（3.3V 出力）
//    Gpio[7] = 0x1 << pin;   //  GPSET0
rpiGpio->GPSET[pin/32] = 0x1 << (pin%32); //  GPSET0 or GPSET1	
}
void gpio_clear(int pin)
{
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
    if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_clear)\n");
        exit(-1);
    }
    //  ピンに０を出力（0V 出力）
//    Gpio[10] = 0x1 << pin;  //  GPCLR0
	rpiGpio->GPCLR[pin/32] = 0x1 << (pin%32); //  GPCLR0 or GPCLR1	
}

//  ピン状態の読み取り（3.3V->1, 0V->0）
int gpio_read (int pin)
{
	int tst;
    //  ピン番号チェック（スピードを追求するなら省略してもよい）
    if (pin < 0 || pin > 53) {
        printf("error: pin number out of range (gpio_read)\n");
        exit(-1);
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
    //  ピン番号チェック
    if (pin < 0 || pin > 31) {
        printf("error: pin number out of range (gpio_configure_pull)\n");
        exit(-1);
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
/***
//
void ledTogglePi2(void) {	//Only for pi1 B+,Pi2 ,and Zero  on Board LED
 
	   // GPIO47 =32+15 --> (0x01 << 15)
	if( gpio_read(47) ) // If GPIO47 On 
		gpio_clear(47); // 	GPIO47 clear
	 else 
		gpio_set(47);// 		GPIO47 Set
}
int main () { 
     printf("GPIO1_Lx Start v1\n");
	struct rpiGpio *rpiGpio = RPI_GPIO_BASE;
    gpio_init();                        //  オマジナイ 
	gpio_configure(20, GPIO_OUTPUT);        //  GPIO_20 を出力に設定 
	gpio_configure(47, GPIO_OUTPUT);     //  GPIO_47 を出力に設定 オンボードLED
   while (1) { 
         ledTogglePi2( );
         gpio_set(20);                   //  1 を出力（3.3V）  
//		 usleep(500000);                 //  0.5秒待ち 
	delay00(500);
         ledTogglePi2( );		 
		 gpio_clear(20);                 //  0 を出力（0V） 
//		 usleep(500000);                 //  0.5秒待ち  
	delay00(500);		 
   }
 } 
 ***/
