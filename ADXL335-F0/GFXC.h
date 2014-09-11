#ifndef GFXC_H
#define GFXC_H

#include <ILI9163.h>

#define FastChar
#define LetterSpace 1

uint16_t ColIP(Colours8, uint8_t);
uint16_t ColP(uint8_t, uint8_t, uint8_t);

int16_t PChar(uint16_t, uint8_t, uint8_t, uint8_t, Colours8, Colours8);
int16_t PStr(char*, uint8_t, uint8_t, uint8_t, Colours8, Colours8);
int16_t PNum(int32_t, uint8_t, uint8_t, uint8_t, uint8_t, Colours8, Colours8);
int16_t PNumF(float, uint8_t, uint8_t, uint8_t, uint8_t, Colours8, Colours8);

uint8_t Circle(uint8_t, uint8_t, uint8_t, Colours8);
uint8_t Ellipse(uint8_t, uint8_t, uint8_t, uint8_t, Colours8);
uint8_t Semicircle(uint8_t, uint8_t, uint8_t, uint8_t, Colours8);

uint8_t Rect(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t, Colours8);
uint8_t FillRec(uint8_t, uint8_t, uint8_t, uint8_t, Colours8, Colours8);
uint8_t LineP(uint8_t, uint8_t, uint8_t, int16_t, Colours8);
uint8_t LineC(uint8_t, uint8_t, uint8_t, uint8_t, Colours8);

uint8_t Triangle(uint8_t, uint8_t, uint32_t, uint16_t, Colours8);

uint8_t Row(uint8_t, uint8_t, uint8_t, Colours8);
uint8_t Column(uint8_t, uint8_t, uint8_t, Colours8);

uint8_t InBounds(int32_t, int32_t);
void RotateCo(int32_t *, int32_t *, int32_t);
uint32_t IAbs(int32_t);
int16_t qSin(int32_t);
uint32_t StrLen(char *);
uint8_t CheckNumLength(int32_t);
int32_t FPow(int32_t, uint32_t);

#endif
