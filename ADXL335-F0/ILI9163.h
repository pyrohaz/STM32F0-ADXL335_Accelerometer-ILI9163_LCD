#ifndef ILI9163_H
#define ILI9163_H

#include <stm32f0xx_gpio.h>
#include <stm32f0xx_spi.h>
#include <stm32f0xx_rcc.h>
#include <string.h>
#include <stdio.h>

typedef enum WModesS{
	Dat,
	Reg,
} WModes;

typedef enum SleepModesS{
	Sleep,
	Awake,
} SleepModes;

/*
typedef enum Colours8B{
	Black = 0x0000,
	Blue = 0x0010,
	Red = 0x8000,
	Magenta = 0x8010,
	Green = 0x0400,
	Cyan = 0x0410,
	Yellow = 0x8400,
	White = 0x8410,
} Colours8;
 */

/*
#define Black 0x0000
#define Blue 0x0010
#define Red 0x8000
#define Magenta 0x8010
#define Green 0x0400
#define Cyan 0x0410
#define Yellow 0x8400
#define White 0x8410
 */

enum Colours{
	Black = 0x0000,
	Blue = 0x0010,
	Red = 0x8000,
	Magenta = 0x8010,
	Green = 0x0400,
	Cyan = 0x0410,
	Yellow = 0x8400,
	White = 0xFFFF
};

typedef uint16_t Colours8;

#define BKGCol White

#define CSPin GPIO_Pin_3
#define ResPin GPIO_Pin_4
#define AOPin GPIO_Pin_6
#define DatPin GPIO_Pin_7
#define ClkPin GPIO_Pin_5
#define VCCPin GPIO_Pin_3
#define BLPin GPIO_Pin_10

#define DatPS GPIO_PinSource7
#define ClkPS GPIO_PinSource5

#define XPix 128
#define YPix 128

void Delay(uint32_t);

void ILI9163Init(void);

uint16_t EToS(uint8_t);

void SB(uint8_t, WModes);
void SW(uint16_t, WModes);

void SetAddr(uint8_t, uint8_t, uint8_t, uint8_t);
void SetScrn(Colours8);
void ClrScrn(void);
void WritePix(uint16_t, uint16_t, Colours8);
void PCol(Colours8);

void SleepMode(uint8_t);
void InvMode(uint8_t);

#endif
