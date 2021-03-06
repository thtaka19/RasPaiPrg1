#ifndef RPILIB_DEVICE_AQM0802_H
#define RPILIB_DEVICE_AQM0802_H

// i2c
#include "../cmn00/rpi_i2c.h"

// LCD slave addr
#define	AQM0802_ADDR	0x7C

// control byte
#define AQM0802_CTRL_Co		(0x01 << 7)
#define AQM0802_CTRL_RS		(0x01 << 6)

// data byte
#define AQM0802_CMD_CLEAR_DISPLAY			(0x01)
#define AQM0802_CMD_FUNCTION_BASE			(0x20)
#define AQM0802_CMD_FUNCTION_DL_EN			(0x01 << 4)	
#define AQM0802_CMD_FUNCTION_N_EN			(0x01 << 3)	
#define AQM0802_CMD_FUNCTION_DH_EN			(0x01 << 2)	
#define AQM0802_CMD_FUNCTION_IS_EN			(0x01)	

#define AQM0802_CMD_DISPLAY_CTRL_BASE		(0x08)
#define AQM0802_CMD_DISPLAY_CTRL_D			(0x01 << 2)
#define AQM0802_CMD_DISPLAY_CTRL_C			(0x01 << 1)
#define AQM0802_CMD_DISPLAY_CTRL_B 			(0x01)

#define AQM0802_CMD_ENTRY_MODE_BASE			(0x04)
#define AQM0802_CMD_ENTRY_MODE_ID_I			(0x01 << 1)
#define AQM0802_CMD_ENTRY_MODE_ID_D			(0x00)
#define AQM0802_CMD_ENTRY_MODE_ID_S			(0x01)

#define AQM0802_OSC_FREQ_BASE				(0x10)
#define AQM0802_OSC_FREQ_BS_EN				(0x01 << 3)
#define AQM0802_OSC_FREQ_F2_EN				(0x01 << 2)
#define AQM0802_OSC_FREQ_F1_EN				(0x01 << 1)
#define AQM0802_OSC_FREQ_F0_EN				(0x01)

#define AQM0802_POW_ICON_CONTRAST_BASE		(0x50)
#define AQM0802_POW_ICON_CONTRAST_ION_EN	(0x01 << 3)
#define AQM0802_POW_ICON_CONTRAST_BON_EN	(0x01 << 2)
#define AQM0802_POW_ICON_CONTRAST_C5_EN		(0x01 << 1)
#define AQM0802_POW_ICON_CONTRAST_C4_EN		(0x01)

#define AQM0802_CONTRAST_BASE				(0x70)
#define AQM0802_CONTRAST_C3_EN				(0x01 << 3)
#define AQM0802_CONTRAST_C2_EN				(0x01 << 2)
#define AQM0802_CONTRAST_C1_EN				(0x01 << 1)
#define AQM0802_CONTRAST_C0_EN				(0x01)

#define AQM0802_FOLLOWER_CTRL_BASE			(0x60)
#define AQM0802_FOLLOWER_CTRL_FON_EN		(0x01 << 3)
#define AQM0802_FOLLOWER_CTRL_RAB2_EN		(0x01 << 2)
#define AQM0802_FOLLOWER_CTRL_RAB1_EN		(0x01 << 1)
#define AQM0802_FOLLOWER_CTRL_RAB0_EN		(0x01)

#define AQM0802_SET_DDRAM_ADDR_BASE			(0x80)

// functions
void aqm0802_init(void);
void aqm0802_print_line(uint8_t *str, uint8_t line);
void aqm0802_cleardisplay(void);
void LCDputs(uint8_t*);
void LCDputchar(char );
void LCDgotoxy(unsigned char ,unsigned char);
void LCDgotoxyint(int ,int);
#endif
