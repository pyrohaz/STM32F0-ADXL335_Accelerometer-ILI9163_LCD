#include <GFXC.h>

/*
 * GFXC.c
 * Author: Harris Shallcross
 * Year: ~24/8/2014
 *
 *The rough unfinished version of my colour LCD graphics
 *library. As of now, maximum supported resolution is 255x255
 *though this is limited by the function parameters being
 *passed as unsigned 8 bit integers. Improvements are always
 *being made!
 *
 *More information can be found on my blog at:
 *www.hsel.co.uk
 *
 *Copyright (c) 2014 Harris Shallcross
 *
 *The code is released under the MIT License
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 */


const char Chars[] =
{
		0x00, 0x00, 0x00, 0x00, 0x00 // 20
		,0x00, 0x00, 0x5f, 0x00, 0x00 // 21 !
		,0x00, 0x07, 0x00, 0x07, 0x00 // 22 "
		,0x14, 0x7f, 0x14, 0x7f, 0x14 // 23 #
		,0x24, 0x2a, 0x7f, 0x2a, 0x12 // 24 $
		,0x23, 0x13, 0x08, 0x64, 0x62 // 25 %
		,0x36, 0x49, 0x55, 0x22, 0x50 // 26 &
		,0x00, 0x05, 0x03, 0x00, 0x00 // 27 '
		,0x00, 0x1c, 0x22, 0x41, 0x00 // 28 (
		,0x00, 0x41, 0x22, 0x1c, 0x00 // 29 )
		,0x14, 0x08, 0x3e, 0x08, 0x14 // 2a *
		,0x08, 0x08, 0x3e, 0x08, 0x08 // 2b +
		,0x00, 0x50, 0x30, 0x00, 0x00 // 2c ,
		,0x08, 0x08, 0x08, 0x08, 0x08 // 2d -
		,0x00, 0x60, 0x60, 0x00, 0x00 // 2e .
		,0x20, 0x10, 0x08, 0x04, 0x02 // 2f /
		,0x3e, 0x51, 0x49, 0x45, 0x3e // 30 0
		,0x00, 0x42, 0x7f, 0x40, 0x00 // 31 1
		,0x42, 0x61, 0x51, 0x49, 0x46 // 32 2
		,0x21, 0x41, 0x45, 0x4b, 0x31 // 33 3
		,0x18, 0x14, 0x12, 0x7f, 0x10 // 34 4
		,0x27, 0x45, 0x45, 0x45, 0x39 // 35 5
		,0x3c, 0x4a, 0x49, 0x49, 0x30 // 36 6
		,0x01, 0x71, 0x09, 0x05, 0x03 // 37 7
		,0x36, 0x49, 0x49, 0x49, 0x36 // 38 8
		,0x06, 0x49, 0x49, 0x29, 0x1e // 39 9
		,0x00, 0x36, 0x36, 0x00, 0x00 // 3a :
		,0x00, 0x56, 0x36, 0x00, 0x00 // 3b ;
		,0x08, 0x14, 0x22, 0x41, 0x00 // 3c <
		,0x14, 0x14, 0x14, 0x14, 0x14 // 3d =
		,0x00, 0x41, 0x22, 0x14, 0x08 // 3e >
		,0x02, 0x01, 0x51, 0x09, 0x06 // 3f ?
		,0x32, 0x49, 0x79, 0x41, 0x3e // 40 @
		,0x7e, 0x11, 0x11, 0x11, 0x7e // 41 A
		,0x7f, 0x49, 0x49, 0x49, 0x36 // 42 B
		,0x3e, 0x41, 0x41, 0x41, 0x22 // 43 C
		,0x7f, 0x41, 0x41, 0x22, 0x1c // 44 D
		,0x7f, 0x49, 0x49, 0x49, 0x41 // 45 E
		,0x7f, 0x09, 0x09, 0x09, 0x01 // 46 F
		,0x3e, 0x41, 0x49, 0x49, 0x7a // 47 G
		,0x7f, 0x08, 0x08, 0x08, 0x7f // 48 H
		,0x00, 0x41, 0x7f, 0x41, 0x00 // 49 I
		,0x20, 0x40, 0x41, 0x3f, 0x01 // 4a J
		,0x7f, 0x08, 0x14, 0x22, 0x41 // 4b K
		,0x7f, 0x40, 0x40, 0x40, 0x40 // 4c L
		,0x7f, 0x02, 0x0c, 0x02, 0x7f // 4d M
		,0x7f, 0x04, 0x08, 0x10, 0x7f // 4e N
		,0x3e, 0x41, 0x41, 0x41, 0x3e // 4f O
		,0x7f, 0x09, 0x09, 0x09, 0x06 // 50 P
		,0x3e, 0x41, 0x51, 0x21, 0x5e // 51 Q
		,0x7f, 0x09, 0x19, 0x29, 0x46 // 52 R
		,0x46, 0x49, 0x49, 0x49, 0x31 // 53 S
		,0x01, 0x01, 0x7f, 0x01, 0x01 // 54 T
		,0x3f, 0x40, 0x40, 0x40, 0x3f // 55 U
		,0x1f, 0x20, 0x40, 0x20, 0x1f // 56 V
		,0x3f, 0x40, 0x38, 0x40, 0x3f // 57 W
		,0x63, 0x14, 0x08, 0x14, 0x63 // 58 X
		,0x07, 0x08, 0x70, 0x08, 0x07 // 59 Y
		,0x61, 0x51, 0x49, 0x45, 0x43 // 5a Z
		,0x00, 0x7f, 0x41, 0x41, 0x00 // 5b [
		,0x02, 0x04, 0x08, 0x10, 0x20 // 5c
		,0x00, 0x41, 0x41, 0x7f, 0x00 // 5d ]
		,0x04, 0x02, 0x01, 0x02, 0x04 // 5e ^
		,0x40, 0x40, 0x40, 0x40, 0x40 // 5f _
		,0x00, 0x01, 0x02, 0x04, 0x00 // 60 `
		,0x20, 0x54, 0x54, 0x54, 0x78 // 61 a
		,0x7f, 0x48, 0x44, 0x44, 0x38 // 62 b
		,0x38, 0x44, 0x44, 0x44, 0x20 // 63 c
		,0x38, 0x44, 0x44, 0x48, 0x7f // 64 d
		,0x38, 0x54, 0x54, 0x54, 0x18 // 65 e
		,0x08, 0x7e, 0x09, 0x01, 0x02 // 66 f
		,0x0c, 0x52, 0x52, 0x52, 0x3e // 67 g
		,0x7f, 0x08, 0x04, 0x04, 0x78 // 68 h
		,0x00, 0x44, 0x7d, 0x40, 0x00 // 69 i
		,0x20, 0x40, 0x44, 0x3d, 0x00 // 6a j
		,0x7f, 0x10, 0x28, 0x44, 0x00 // 6b k
		,0x00, 0x41, 0x7f, 0x40, 0x00 // 6c l
		,0x7c, 0x04, 0x18, 0x04, 0x78 // 6d m
		,0x7c, 0x08, 0x04, 0x04, 0x78 // 6e n
		,0x38, 0x44, 0x44, 0x44, 0x38 // 6f o
		,0x7c, 0x14, 0x14, 0x14, 0x08 // 70 p
		,0x08, 0x14, 0x14, 0x18, 0x7c // 71 q
		,0x7c, 0x08, 0x04, 0x04, 0x08 // 72 r
		,0x48, 0x54, 0x54, 0x54, 0x20 // 73 s
		,0x04, 0x3f, 0x44, 0x40, 0x20 // 74 t
		,0x3c, 0x40, 0x40, 0x20, 0x7c // 75 u
		,0x1c, 0x20, 0x40, 0x20, 0x1c // 76 v
		,0x3c, 0x40, 0x30, 0x40, 0x3c // 77 w
		,0x44, 0x28, 0x10, 0x28, 0x44 // 78 x
		,0x0c, 0x50, 0x50, 0x50, 0x3c // 79 y
		,0x44, 0x64, 0x54, 0x4c, 0x44 // 7a z
		,0x00, 0x08, 0x36, 0x41, 0x00 // 7b {
		,0x00, 0x00, 0x7f, 0x00, 0x00 // 7c |
		,0x00, 0x41, 0x36, 0x08, 0x00 // 7d }
		,0x10, 0x08, 0x08, 0x10, 0x08 // 7e
		,0x78, 0x46, 0x41, 0x46, 0x78 // 7f
		,0xFF, 0x00, 0x00, 0x00, 0x00 // Current char line
};

uint16_t ColIP(Colours8 Col, uint8_t Perc){
	uint16_t RCol = 0;
	uint32_t PercApr = (Perc*2622)>>10;

	switch(Col){
	case Blue: RCol = (PercApr>>3) >= 31 ? 31 : (PercApr>>3); break;
	case Green: RCol = (PercApr>>2)<<5 >= 63<<5 ? 63<<5 : (PercApr>>2)<<5; break;
	case Red: RCol = (PercApr>>3)<<11 >= 31<<11 ? 31<<11 : (PercApr>>3)<<11; break;
	}

	return RCol;
}

uint16_t ColP(uint8_t RedC, uint8_t BlueC, uint8_t GreenC){
	return ColIP(Red, RedC)|ColIP(Green, GreenC)|ColIP(Blue, BlueC);
}

int16_t PChar(uint16_t Ch, uint8_t X, uint8_t Y, uint8_t Size, Colours8 Col, Colours8 BKCol){
	uint16_t XCnt, YCnt;
	uint16_t CharAddr, YPos;

	Ch-=0x20;
	Ch*=5;

	SetAddr(X, Y, X + 4 +(Size*5) + LetterSpace, Y + 7 + (Size<<3));

	for(YCnt = 0; YCnt<8*(Size+1); YCnt++){
		for(XCnt = 0; XCnt<(5*(1+Size)) + LetterSpace; XCnt++){

#ifdef FAST_CHAR
			switch(Size){
			case 0:
				CharAddr = XCnt;
				YPos = YCnt;
				break;
			case 1:
				CharAddr = XCnt>>1;
				YPos = YCnt>>1;
				break;
			case 2:
				CharAddr = (XCnt*86)>>8;
				YPos = (YCnt*86)>>8;
				break;
			case 3:
				CharAddr = XCnt>>2;
				YPos = YCnt>>2;
				break;
			case 4:
				CharAddr = (51*XCnt)>>8;
				YPos = (51*YCnt)>>8;
				break;
			}
#else
			//Slow, supports all sizes up to the screen max!
			CharAddr = XCnt/(Size+1);
			YPos = YCnt/(Size+1);
#endif

			if(XCnt<(5*(Size+1)) && (Chars[Ch+CharAddr] & 1<<YPos)) PCol(Col);
			else PCol(BKCol);
		}
	}

	return X+(1+Size)*5+LetterSpace;
}

int16_t PStr(char* Str, uint8_t X, uint8_t Y, uint8_t Size, Colours8 Col, Colours8 BKCol){
	uint8_t SCnt, StrL;

	StrL = StrLen(Str);

	for(SCnt = 0; SCnt<StrL; SCnt++){
		X = PChar(Str[SCnt], X, Y, Size, Col, BKCol);
	}

	return X;
}

int16_t PNum(int32_t Num, uint8_t X, uint8_t Y, uint8_t Pad, uint8_t Size, Colours8 Col, Colours8 BKCol){
	int8_t Cnt, Len, NegNum = 0, XPos = X;

	if(Num<0){
		Num = -Num;
		NegNum = 1;
	}

	if(NegNum){
		XPos = PChar('-', XPos, Y, Size, Col, BKCol);
	}

	Len = CheckNumLength(Num);

	if(Len<Pad){
		for(Cnt = 0; Cnt<(Pad-Len); Cnt++){
			XPos = PChar('0', XPos, Y, Size, Col, BKCol);
		}
	}

	for(Cnt = Len-1; Cnt>=0; Cnt--){
		XPos = PChar('0' + (Num/FPow(10, Cnt))%10, XPos, Y, Size, Col, BKCol);
	}

	return XPos;
}

int16_t PNumF(float Num, uint8_t X, uint8_t Y, uint8_t Prec, uint8_t Size, Colours8 Col, Colours8 BKCol){
	char NBuf[17], PadBuf[5] = "%.0f";
	uint8_t SCnt, Len, XPos = X;

	PadBuf[2] = Prec + '0';
	Len = sprintf(NBuf, &PadBuf[0], Num);

	for(SCnt = 0; SCnt<Len; SCnt++){
		XPos = PChar(NBuf[SCnt], XPos, Y, Size, Col, BKCol);
	}

	return XPos;
}

uint8_t Circle(uint8_t XS, uint8_t YS, uint8_t R, Colours8 Col){
	return Ellipse(XS, YS, R, R, Col);
}

uint8_t Ellipse(uint8_t XS, uint8_t YS, uint8_t XR, uint8_t YR, Colours8 Col){
	const uint16_t Res = 360;
	uint16_t Cnt;
	uint8_t X, Y;

	for(Cnt = 0; Cnt<Res; Cnt++){
		X = XS+((XR*qSin(Cnt+90))>>10);
		Y = YS+((YR*qSin(Cnt))>>10);
		WritePix(X, Y, Col);
	}
	return 0;
}

uint8_t Semicircle(uint8_t XS, uint8_t YS, uint8_t R, uint8_t UD, Colours8 Col){
	const uint16_t Res = 360;
	uint16_t Cnt;
	uint8_t X, Y;

	for(Cnt = 0; Cnt<Res/2; Cnt++){
		if(UD){
			X = XS - ((R*qSin(Cnt+90))>>10);
			Y = YS - ((R*qSin(Cnt))>>10);
		}
		else{
			X = XS + ((R*qSin(Cnt+90))>>10);
			Y = YS + ((R*qSin(Cnt))>>10);
		}
		WritePix(X, Y, Col);
	}

	LineC(XS-(R-1), YS, XS+(R), YS, Col);
	return 0;
}

//TODO: Change from XS to XE and YS to YE and instead do origin, xlen and ylen
uint8_t Rect(uint8_t XS, uint8_t YS, uint8_t XE, uint8_t YE, uint16_t Angle, Colours8 Col){
	int16_t XLM = - (IAbs(XE-XS)>>1), XRM = -XLM;
	int16_t YTM = (IAbs(YE-YS)>>1), YBM = -YTM;
	int16_t OrX = XS+(IAbs(XE-XS)>>1), OrY = YS+(IAbs(YE-YS)>>1);
	int32_t NTLCoX, NTRCoX, NBLCoX, NBRCoX;
	int32_t NTLCoY, NTRCoY, NBLCoY, NBRCoY;

	//Rotated co-ordinates
	NTLCoX = ((XLM*qSin(Angle+90))>>10) - ((YTM*qSin(Angle))>>10);
	NTLCoY = ((XLM*qSin(Angle))>>10) + ((YTM*qSin(Angle+90))>>10);

	NTRCoX = ((XRM*qSin(Angle+90))>>10) - ((YTM*qSin(Angle))>>10);
	NTRCoY = ((XRM*qSin(Angle))>>10) + ((YTM*qSin(Angle+90))>>10);

	NBLCoX = ((XLM*qSin(Angle+90))>>10) - ((YBM*qSin(Angle))>>10);
	NBLCoY = ((XLM*qSin(Angle))>>10) + ((YBM*qSin(Angle+90))>>10);

	NBRCoX = ((XRM*qSin(Angle+90))>>10) - ((YBM*qSin(Angle))>>10);
	NBRCoY = ((XRM*qSin(Angle))>>10) + ((YBM*qSin(Angle+90))>>10);

	LineC(NTLCoX+OrX, NTLCoY+OrY, NTRCoX+OrX, NTRCoY+OrY, Col); //Top left to top right
	LineC(NTLCoX+OrX, NTLCoY+OrY, NBLCoX+OrX, NBLCoY+OrY, Col); //Top left to bottom left
	LineC(NTRCoX+OrX, NTRCoY+OrY, NBRCoX+OrX, NBRCoY+OrY, Col); //Top right to bottom right
	LineC(NBLCoX+OrX, NBLCoY+OrY, NBRCoX+OrX, NBRCoY+OrY, Col); //Bottom left to bottom right

	return 0;
}

uint8_t FillRec(uint8_t XS, uint8_t YS, uint8_t XE, uint8_t YE, Colours8 LCol, Colours8 FCol){
	uint8_t XCnt, YCnt, LCnt;

	uint8_t FRowLen = IAbs(XE-XS)-1, FColLen = IAbs(YE-YS)-1;
	uint32_t Cnt, Area = FRowLen*FColLen;

	LineC(XS, YS, XE, YS, LCol);
	LineC(XS, YE, XE, YE, LCol);
	LineC(XS, YS, XS, YE, LCol);
	LineC(XE, YS, XE, YE, LCol);

	SetAddr(XS+1, YS+1, XE-1, YE-1);
	for(Cnt = 0; Cnt<=Area; Cnt++){
		PCol(FCol);
	}

	return 0;
}

uint8_t LineP(uint8_t XS, uint8_t YS, uint8_t R, int16_t Angle, Colours8 Col){
	uint8_t XE, YE;

	XE = XS+((R*qSin(Angle+90))>>10);
	YE = YS+((R*qSin(Angle))>>10);

	return LineC(XS, YS, XE, YE, Col);
}

uint8_t LineC(uint8_t XS, uint8_t YS, uint8_t XE, uint8_t YE, Colours8 Col){
	int Cnt, Distance;
	int XErr = 0, YErr = 0, dX, dY;
	int XInc, YInc;

	dX = XE-XS;
	dY = YE-YS;

	if(dX>0) XInc = 1;
	else if(dX==0) XInc = 0;
	else XInc = -1;

	if(dY>0) YInc = 1;
	else if(dY==0) YInc = 0;
	else YInc = -1;

	dX = IAbs(dX);
	dY = IAbs(dY);

	if(dX>dY) Distance = dX;
	else Distance = dY;

	for(Cnt = 0; Cnt<=Distance+1; Cnt++){
		WritePix(XS, YS, Col);

		XErr+=dX;
		YErr+=dY;
		if(XErr>Distance){
			XErr-=Distance;
			XS+=XInc;
		}
		if(YErr>Distance){
			YErr-=Distance;
			YS+=YInc;
		}
	}
	return 0;
}

uint8_t Row(uint8_t Y, uint8_t Amount, uint8_t Rows, Colours8 Col){
	uint8_t YCnt, XCnt;

	if(InBounds(Y, Amount) && InBounds(Y+Rows, Amount)){
		SetAddr(0, Y, Amount-1, Y+Rows-1);
		for(XCnt = Y; XCnt<(Rows+Y); XCnt++){
			for(YCnt = 0; YCnt<Amount; YCnt++){
				PCol(Col);
			}
		}

		return 0;
	}
	else{
		return 1;
	}
}

uint8_t Column(uint8_t X, uint8_t Amount, uint8_t Columns, Colours8 Col){
	uint8_t YCnt, XCnt;

	if(InBounds(X, Amount) && InBounds(X+Columns, Amount)){
		SetAddr(X, 0, X+Columns-1, Amount-1);
		for(XCnt = X; XCnt<(Columns+X); XCnt++){
			for(YCnt = 0; YCnt<Amount; YCnt++){
				PCol(Col);
			}
		}

		return 0;
	}
	else{
		return 1;
	}
}

uint8_t Triangle(uint8_t X, uint8_t Y, uint32_t SideLen, uint16_t Angle, Colours8 Col){
	int32_t TCoX, TCoY, LCoX, LCoY, RCoX, RCoY;
	int32_t NTCoX, NTCoY, NLCoX, NLCoY, NRCoX, NRCoY;
	int16_t SLST = SideLen>>1, HST, Height;

	Angle+=180;

	Height = (SideLen*887)>>10;
	HST = Height>>1;

	TCoX = 0;
	TCoY = HST;

	LCoX = -SLST;
	LCoY = -HST;

	RCoX = SLST;
	RCoY = LCoY;

	RotateCo(&TCoX, &TCoY, Angle);
	RotateCo(&RCoX, &RCoY, Angle);
	RotateCo(&LCoX, &LCoY, Angle);

	if(InBounds(TCoX, TCoY) && InBounds(LCoX, LCoY) && InBounds(RCoX, RCoY)){
		LineC(TCoX+X, TCoY+Y, LCoX+X, LCoY+Y, Col);
		LineC(TCoX+X, TCoY+Y, RCoX+X, RCoY+Y, Col);
		LineC(RCoX+X, RCoY+Y, LCoX+X, LCoY+Y, Col);

		return 0;
	}
	else{
		return 1;
	}
}

//Check if given co-ordinates are within range.
uint8_t InBounds(int32_t X, int32_t Y){
	if(X<0 || X>XPix) return 0;
	if(Y<0 || Y>YPix) return 0;

	return 1;
}

//Rotate co-ordinates around the origin
void RotateCo(int32_t *X, int32_t *Y, int32_t Angle){
	int32_t XT;

	XT = ((*X*qSin(Angle+90))>>10) - ((*Y*qSin(Angle))>>10);
	*Y = ((*X*qSin(Angle))>>10) + ((*Y*qSin(Angle+90))>>10);

	*X = XT;
}

//Returns -1024 to 1024!
int16_t qSin(int32_t Ph){
	int32_t XSqr;

	Ph%=360;

	if(Ph<180){
		XSqr = (8100-(Ph-90)*(Ph-90));
	}
	else{
		Ph-=180;
		XSqr = ((Ph-90)*(Ph-90)-8100);
	}
	XSqr = (XSqr*517)>>12;

	return XSqr;
}

uint32_t IAbs(int32_t N){
	if(N>0) return N;
	else return -N;
}

uint32_t StrLen(char *S){
	uint32_t SCnt = 0;
	uint8_t CChar = 1;

	while(CChar!= '\0'){
		CChar = S[SCnt];
		SCnt++;
	}

	return SCnt-1;
}

uint8_t CheckNumLength(int32_t Num){
	uint8_t Len = 0, Cnt;

	for(Cnt = 0; Cnt<10; Cnt++){
		if(Num>=FPow(10, Cnt)){
			Len = Cnt;
		}
		else{
			Len = Cnt;
			break;
		}
	}

	return Len;
}

int32_t FPow(int32_t Num, uint32_t Pow){
	int32_t NumO = Num;
	uint32_t Cnt;
	if(Pow>1){
		for(Cnt = 0; Cnt<Pow-1; Cnt++){
			Num*=NumO;
		}
		return Num;
	}

	if(Pow==1) return Num;
	if(Pow==0) return 1;
	else return 0;
}
