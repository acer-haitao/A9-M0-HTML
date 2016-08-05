#include "lpc11xx.h"
#include "gpio.h"
#include "uart.h"
#include "timer32.h"
#include "timeflag.h"
#include "tools.h"
#include "sensor.h"
#include "device.h"
#include "control.h"
#include "key.h"

#include "stdlib.h"
#include "oled2864.h" 

#define STO_NO	1

uint8_t A[6][128] = {

//Log图片
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xC0,
0xC0,0x00,0x00,0x00,0x80,0xC0,0xE0,0x70,0x30,0x38,0x18,0x1C,0x0C,0x0C,0x0C,0xFC,
0xF8,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF8,0x7C,0x1E,0x07,0x03,0x01,0x00,0x01,
0x87,0xFF,0xFE,0x1F,0x07,0x01,0x00,0x00,0x00,0x80,0xC0,0xE0,0x78,0x3C,0x1F,0x0F,
0x07,0x07,0x03,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x06,0x0E,0x0C,0x1C,0x38,0x70,0xF0,0xE0,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xC7,0xC0,0xE0,0x70,0x38,0x38,0x1C,0x0E,
0x07,0x07,0x01,0x00,0x00,0x00,0x04,0x0E,0x06,0x07,0x03,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x07,0x1F,0xFE,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x38,0x70,0xE0,0xC0,0x80,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0xE0,0xF0,0x38,0x1C,0x0F,0x07,0x03,0x01,0x00,0x00,0x30,0x78,0xFC,0xFC,
0xFC,0xFC,0x78,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0xFC,0x00,0x80,0xF0,0xF8,0x3C,0x0C,0x0E,0x06,0x06,0x07,
0x07,0x06,0x06,0x0E,0x0C,0x1C,0xF8,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x03,0x9F,
0xFE,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,
0xFF,0xFF,0xC1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x26,0x76,0x66,0x66,0xE6,0xCE,0xCE,0x8E,0x8E,0x0E,0x0E,0x0E,0x06,0x06,0x06,
0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0xE0,0xF0,0xFC,0xFF,0xC7,0xC0,0xC0,0xC0,0xCF,0xDF,0xDC,0xF8,0xF0,0xE0,0xE0,0xE0,
0x60,0x60,0x60,0x70,0x78,0x7C,0x7F,0x77,0x73,0x30,0x30,0x38,0x18,0x1C,0x0E,0x07,
0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x03,0x03,0x07,0x06,0x0E,0x0C,0x0C,0x1C,0x1C,0x18,0x18,0x18,0x18,0x38,
0x38,0x38,0x30,0x30,0x30,0x30,0x30,0x31,0x31,0x33,0x33,0x33,0x36,0x3E,0x3E,0x34,
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
0x38,0x38,0x18,0x18,0x18,0x18,0x1C,0x1C,0x1C,0x0C,0x0C,0x0E,0x06,0x07,0x03,0x03,
0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,






//仓鼠小组
/*
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x80,0x80,0x80,0x40,0x40,0x20,0x20,0xD0,0xD0,0x48,0x4C,0x46,0x42,
0x43,0x43,0x44,0x44,0x48,0xE8,0xD0,0x50,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBE,0xBE,0x2A,0x2A,0xAA,0xA9,0x29,0x28,0xE0,
0xE0,0x60,0xA2,0xAA,0xAA,0x2A,0x2A,0xEA,0xEA,0x3F,0x3E,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x70,0x20,0x00,0x00,0x00,0x00,
0xFF,0xFF,0x00,0x00,0x00,0x10,0x20,0x20,0x20,0x40,0xC0,0x80,0x80,0x00,0x00,0x00,

0x00,0x00,0x00,0x20,0x60,0x30,0x28,0xA4,0xA6,0x63,0x20,0x30,0x18,0x08,0x08,0x00,
0xFE,0xFE,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x20,0x20,0x20,0x20,
0x20,0x24,0x24,0x24,0x24,0x27,0x23,0x20,0x20,0x20,0x3C,0x30,0x00,0x00,0x00,0x00,


0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x24,0x1C,0x05,0x01,0x00,0x3F,
0x3F,0x20,0x22,0x14,0x0D,0x05,0x00,0x03,0x0F,0x18,0x10,0x20,0x20,0x38,0x00,0x00,



0x00,0x00,0x00,0x04,0x04,0x02,0x02,0x01,0x00,0x00,0x00,0x00,0x20,0x20,0x20,0x60,
0x3F,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x00,0x00,



0x00,0x00,0x00,0x10,0x12,0x12,0x13,0x12,0x12,0x12,0x0A,0x0A,0x2A,0x20,0x20,0x20,
0x3F,0x3F,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x3F,0x3F,0x20,0x20,0x20,0x20,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
*/


//创科联动

/*0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,
0x60,0x30,0x18,0x1C,0x0E,0x1E,0x30,0x70,0x60,0x40,0xC0,0xF0,0x10,0x00,0x80,0xF0,
0x3C,0x0C,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0xE8,0x78,0x0C,0x0C,0x04,0x06,0x00,
0x00,0x78,0x70,0x00,0x00,0xE0,0x7C,0x0E,0x02,0x00,0x00,0x00,0x00,0x00,0x8C,0xFC,
0xBC,0x8C,0x8C,0xCC,0xFC,0x1C,0x0C,0x6C,0x40,0x40,0xDE,0xC8,0x40,0x70,0x58,0x4E,
0x46,0x22,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xC0,
0xC0,0xC0,0xC0,0xF0,0xFE,0xCE,0xC2,0xC0,0xC0,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE3,0x7D,0x0F,
0x03,0x43,0x43,0x63,0x3F,0x0F,0x01,0xC0,0xF0,0x3E,0x07,0x00,0xE0,0x7C,0x0F,0x01,
0x00,0x00,0x00,0x80,0xC3,0x63,0xF3,0xFF,0x1F,0xB3,0x73,0x43,0x03,0x01,0x8C,0x9E,
0x98,0x80,0xC0,0xF8,0xDF,0xC3,0x40,0x60,0x00,0x00,0x00,0x00,0xE0,0x7C,0x1F,0x11,
0xD0,0xF8,0x1E,0x87,0x10,0x10,0x10,0x90,0xF0,0xFC,0x1F,0x11,0x10,0x10,0x10,0x10,
0x00,0x00,0x00,0x00,0x84,0xC2,0x72,0x3A,0x0E,0x06,0xE2,0xE2,0x02,0x02,0x80,0xC0,
0x70,0x3C,0x0F,0x01,0x80,0xF0,0x3C,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3F,0x33,0x30,0x30,
0x30,0x30,0x1C,0x0C,0x00,0x00,0x00,0x01,0x31,0x30,0x38,0x1F,0x03,0x00,0x00,0x00,
0x00,0x02,0x03,0x01,0x30,0x3E,0x07,0x00,0x00,0x03,0x03,0x03,0x01,0x01,0x01,0x01,
0x71,0x3E,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x07,0x03,0x02,0x33,0x3F,
0x07,0x31,0x31,0x18,0x0C,0x06,0x03,0x01,0x00,0x07,0x1F,0x3C,0x18,0x00,0x00,0x00,
0x00,0x00,0x06,0x07,0x03,0x02,0x03,0x03,0x31,0x31,0x1B,0x0F,0x0C,0x06,0x03,0x01,
0x30,0x18,0x18,0x1E,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,*/
//farsight

/*0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xC0,0xC0,0x60,0x60,0x60,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
0x0C,0xCC,0xFC,0x3F,0x0F,0x0C,0x0C,0x04,0x00,0x00,0x00,0x10,0x98,0x88,0x8C,0x8C,
0xCC,0xDC,0xFC,0x38,0x00,0x00,0x00,0xC0,0xF8,0x7C,0x34,0x18,0x08,0x0C,0x0C,0x04,
0x00,0x00,0x00,0x00,0xF0,0xF8,0xCC,0x8C,0x8C,0x8C,0x8C,0x1C,0x18,0x00,0x00,0x00,
0x00,0x00,0xC0,0xF8,0x3C,0x04,0x00,0x00,0x00,0x00,0x40,0xF0,0xF8,0x8C,0x8C,0x8C,
0xDC,0x7C,0x38,0x0C,0x0C,0x04,0xC0,0xF8,0x7F,0x17,0x18,0x0C,0x0C,0xFC,0xFC,0x38,
0x00,0x00,0x00,0x08,0x0C,0xCC,0xFC,0x3F,0x0F,0x0C,0x0C,0x04,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,
0x1E,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x1F,0x19,0x19,0x19,0x09,0x15,
0x1E,0x1F,0x01,0x00,0x00,0x10,0x1E,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0C,0x1C,0x18,0x18,0x18,0x18,0x0D,0x0F,0x07,0x00,0x00,0x00,0x00,0x00,
0x10,0x1E,0x0F,0x01,0x00,0x00,0x00,0x60,0xF0,0x9E,0x8F,0x8D,0x8D,0x8D,0x8D,0x4D,
0x7C,0x38,0x00,0x00,0x10,0x1E,0x0F,0x01,0x00,0x00,0x00,0x10,0x1E,0x0F,0x01,0x00,
0x00,0x00,0x00,0x00,0x0E,0x1F,0x19,0x18,0x18,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,*/
};

//仓鼠联盟
uint8_t B[6][128] = 
{

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x80,0x80,0x80,0x40,0x40,0x20,0x20,0xD0,0xD0,0x48,0x4C,0x46,0x42,
0x43,0x43,0x44,0x44,0x48,0xE8,0xD0,0x50,0x20,0x20,0x20,0x40,0x40,0x40,0x40,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBE,0xBE,0x2A,0x2A,0xAA,0xA9,0x29,0x28,0xE0,
0xE0,0x60,0xA2,0xAA,0xAA,0x2A,0x2A,0xEA,0xEA,0x3F,0x3E,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x04,0x04,0xFC,0xFC,0x24,0x24,0x24,0x24,0xFC,0xFC,0x82,0x82,0x92,
0x90,0x91,0x92,0x96,0x94,0xF0,0xF0,0x88,0x94,0x96,0x93,0x91,0x88,0xD0,0x80,0x80,

0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x54,0x54,0x54,0x54,0x54,0x52,0x7E,0x02,0x00,
0x80,0xC0,0x7E,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0xFE,0xFE,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x20,0x20,0x20,0x20,
0x20,0x24,0x24,0x24,0x24,0x27,0x23,0x20,0x20,0x20,0x3C,0x30,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x24,0x1C,0x05,0x01,0x00,0x3F,
0x3F,0x20,0x22,0x14,0x0D,0x05,0x00,0x03,0x0F,0x18,0x10,0x20,0x20,0x38,0x00,0x00,

0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x09,0x09,0x09,0x05,0x3F,0x3F,0x44,0x44,0x40,
0x20,0x20,0x10,0x08,0x0C,0x07,0x01,0x01,0x06,0x08,0x18,0x10,0x30,0x20,0x20,0x20,

0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x3E,0x3E,0x22,0x22,0x22,0x22,0x3E,0x3F,0x23,
0x22,0x22,0x22,0x3E,0x22,0x22,0x22,0x23,0x23,0x3F,0x23,0x21,0x20,0x20,0x20,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

};
uint8_t Nu[200];

//extern uint8_t cmd;
#if(STO_NO == 1)
uint8_t TitileBuf[20] = {"     STORAGE ONE"};
#endif
#if(STO_NO == 2)
uint8_t TitileBuf[20] = {"     STORAGE TWO"};
#endif


int sure(uint8_t y)
{
	char i;
	for(i = 0;i < 100;i++)
	{
		if(y == Nu[i])
			return 1;
	}
	return 0;
}

void Logo(void)
{
	int i, j;
	char n,m;
	uint8_t x,y,*q = (uint8_t *)B;
	srand(6);
	/*for(i = 0;i<768;i++)
		q[i] = 0xff;
		*/
	show(q);
	for(i= 0;i < 10;i++)
		{
			Delay_ms(300);
		}
	i = j = 0;
 

/***********恢复把A 和 B都变成LOGO*********/
	for(i = 0;i<768;i++)
		q[i] = ((uint8_t *)A)[i];
	show((uint8_t *)A);
		for(i= 0;i < 10;i++)
		{
			Delay_ms(300);
		}
				
/*************横渐灭 ***********/
	srand(2);
	j = 0;
	while(j!=47) {
	 	 y = rand() % 48;
		 if(y > 50 || y < 1)
		 	continue;
		 if(sure(y))
		 	continue;
		 n = y & 0x07;
		 m = y >> 3;

		 for(i = 0; i < 128; i++) {
		  	  A[m][i] &= ~(1<<n);			  			  
		 } 
		 Nu[j++] = y; 
		 show((uint8_t *)A);
		 Delay_ms(20);
	}
	Delay_ms(340);
/*************竖渐亮***********/	
	srand(5);
	j = 0;
		
	while(j<199) {
	 	 x = rand() % 128;
		 if(x > 128 || x < 0)
		 	continue;
		 if(sure(x))
		 	continue;

		 for(i = 0; i < 6; i++) {
		  	  A[i][x] = B[i][x];			  			  
		 } 
		 Nu[j++] = x;  
		 show((uint8_t *)A);
	}	
		for(i= 0;i <10;i++)   //延时logo图像显示
		{
			Delay_ms(300);
		}
		OLED_ClearScreen();
}

void InitSys(void)
{
	SystemInit(); //系统初始化
 	GPIOInit();	 //IO初始化
	InitDelay(48); 	 //初始化延时滴答定时器
	init_timer32(0, 480000);	   //初始化32位定时器  10ms
	NVIC_SetPriority(TIMER_32_0_IRQn, 0);	 //映射32位定时器中断
	enable_timer32(0);						//使能32位定时器
	UARTInit(115200);						//设置串口波特率
	NVIC_SetPriority(UART_IRQn, 2);			 //映射串口中断
}

int main(void)
{
 	InitSys();			 	//系统初始化，让M0芯片跑起来
 	InitTimeFlag();			//定时时间标志位
 	InitAllSensor();		//初始化所有的传感器
 	InitAllDevice();		 //初始化外围设备
	InitControl(TitileBuf);    //初始化按键控制，传参标题头TitileBuf
		
	Logo();  //显示logo图像
		while(1)
  {
 		ScanTimeFlag();
		ScanAllSensor();
		DealA8Cmd(STO_NO);		//zigbee 接收命令
		SendEnvMsg(STO_NO);
		Control(STO_NO);       //仓库号，rfid控制 
	}
}




