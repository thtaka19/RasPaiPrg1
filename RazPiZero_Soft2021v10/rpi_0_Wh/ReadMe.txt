For Raspberry Pi  U-boots
rpi_0_Wh: for Pi Zero_W
rpi_0-1 : for Pi Zero and Pi 1

pri_2   : for Pi 2
rpi_3_32b: for Pi 3 (B) 32bits

Pi 3 (B) 64bits and Pi 3 (B+) are not supported yet.

<u-boot binary files>
these are builded on 3rd Aug. 2018.
 u-boot1V2.bin: for Pi Zero,Pi Zero_w,Pi 1
 u-boot2V2.bin: for Pi 2
 u-boot3_32bV2.bin:for Pi 3 32bits
these are builded on 29th June. 2019.
 u-boot0WV10.bin: Pi Zero_w
 u-boot1V10.bin: for Pi Zero,Pi 1
 u-boot2V10.bin: for Pi 2
 u-boot3_32bV10.bin:for Pi 3 32bits
 
 
 
<Serial UART> 
1)Pi Zero_W : UART(SERIAL) is mini (UART1) 
2)Pi Zero   : UART(SERIAL) is normal (UART0) 
3)Pi 1 (A,B,B+):UART(SERIAL) is normal (UART0)
4)Pi 2 (B):UART(SERIAL) is normal (UART0)
5)Pi 3 (B) 32bits :UART(SERIAL) is mini (UART1)
6)Pi 3 (B) 64bits :UART(SERIAL) is mini (UART1) 
7)Pi 3 (B+) 32bits :UART(SERIAL) is mini (UART1)
 
(UART1) needs on config.txt
###
# Raspberry Pi 3, Pi Zero_W use only uart1
enable_uart=1
###
