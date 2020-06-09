
echo "\n-Start cc Linux Rpi13_10Ledtest1 ---"
cc    -c raspMain00_Lx.c raspGPIO1_Lx.c main7100.c spi0.c i2c1.c 
cc    -c ../cmn00/buttonPi1.c ../cmn00/mini_serialPi1Linux.c ../cmn00/led10.c ../cmn00/ADT7310.c ../cmn00/AQM0802p.c

  echo "\n-Start link Linux Rpi13_10Ledtest1 ---"
  
  
cc     raspMain00_Lx.o raspGPIO1_Lx.o main7100.o spi0.o i2c1.o buttonPi1.o mini_serialPi1Linux.o led10.o ADT7310.o AQM0802p.o -o R13_10.out
echo "\nEnd cc Linux-"
pwd

