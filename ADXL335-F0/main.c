#include <stm32f0xx_adc.h>
#include <GFXC.h>

//Initial type definitions
GPIO_InitTypeDef G;
ADC_InitTypeDef A;

//Analog accelerometer defines
#define A_XPin GPIO_Pin_0
#define A_YPin GPIO_Pin_1
#define A_ZPin GPIO_Pin_2

#define A_GPIO GPIOA

//Analog channel defines
#define A_XChan ADC_Channel_0
#define A_YChan ADC_Channel_1
#define A_ZChan ADC_Channel_2

#define A_ADC ADC1

//Accelerometer blocking ADC read function. This reads the
//channel sent to the function as ADC_Chan at a rate of
//SampleTime. The function then waits until the conversion
//is complete and returns the converted value!
uint16_t ADC_Read(uint32_t ADC_Chan, uint32_t SampleTime){
	ADC_ChannelConfig(A_ADC, ADC_Chan, SampleTime);
	ADC_StartOfConversion(A_ADC);
	while(ADC_GetFlagStatus(A_ADC, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(A_ADC);
}

//Standard ol' Systick millisecond counter!
volatile uint32_t MSec = 0;
void SysTick_Handler(void){
	MSec++;
}

int main(void)
{
	//Enable the required peripheral clocks
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	//Initialize the systick timer at 1 interrupt
	//per millisecond
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	//Initialize the LCD
	ILI9163Init();

	//Configure the accelerometer output pins
	//as analog inputs
	G.GPIO_Pin = A_XPin | A_YPin | A_ZPin;
	G.GPIO_Mode = GPIO_Mode_AN;
	G.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(A_GPIO, &G);

	//Configure the ADC for 12bit conversions and
	//to only convert when triggered (continuous
	//conversion mode disabled).
	A.ADC_ContinuousConvMode = DISABLE;
	A.ADC_DataAlign = ADC_DataAlign_Right;
	A.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	A.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(A_ADC, &A);
	ADC_Cmd(A_ADC, ENABLE);

	//Initialize accelerometer variables!
	uint16_t Xre, Yre, Zre, XPos;

	//Min and max variables
	uint16_t XMx = 0, XMn = 0xFFFF;
	uint16_t YMx = 0, YMn = 0xFFFF;
	uint16_t ZMx = 0, ZMn = 0xFFFF;

	//Normalized variables
	float X, Y, Z;

	while(1)
	{
		//Read each of the accelerometer outputs and store in
		//the corresponding variable!
		Xre = ADC_Read(A_XChan, ADC_SampleTime_71_5Cycles);
		Yre = ADC_Read(A_YChan, ADC_SampleTime_71_5Cycles);
		Zre = ADC_Read(A_ZChan, ADC_SampleTime_71_5Cycles);

		if(Xre>XMx) XMx = Xre;
		if(Xre<XMn) XMn = Xre;

		if(Yre>YMx) YMx = Yre;
		if(Yre<YMn) YMn = Yre;

		if(Zre>ZMx) ZMx = Zre;
		if(Zre<ZMn) ZMn = Zre;


		//Print X, Y and Z raw values to the LCD
		XPos = PStr("XRaw: ", 0, 0, 0, Black, White);
		PNum(Xre, XPos, 0, 0, 0, Black, White);

		XPos = PStr("YRaw: ", 0, 8, 0, Black, White);
		PNum(Yre, XPos, 8, 0, 0, Black, White);

		XPos = PStr("ZRaw: ", 0, 16, 0, Black, White);
		PNum(Zre, XPos, 16, 0, 0, Black, White);

		//Print minimum and maximum values read
		XPos = PStr("XMax: ", 0, 32, 0, Black, White);
		XPos = PNum(XMx, XPos, 32, 0, 0, Black, White);
		XPos = PStr(" XMin: ", XPos, 32, 0, Black, White);
		XPos = PNum(XMn, XPos, 32, 0, 0, Black, White);

		XPos = PStr("YMax: ", 0, 40, 0, Black, White);
		XPos = PNum(YMx, XPos, 40, 0, 0, Black, White);
		XPos = PStr(" YMin: ", XPos, 40, 0, Black, White);
		XPos = PNum(YMn, XPos, 40, 0, 0, Black, White);

		XPos = PStr("ZMax: ", 0, 48, 0, Black, White);
		XPos = PNum(ZMx, XPos, 48, 0, 0, Black, White);
		XPos = PStr(" ZMin: ", XPos, 48, 0, Black, White);
		XPos = PNum(ZMn, XPos, 48, 0, 0, Black, White);

		//Normalize the readings! This formula only works
		//after the device has been calibrated - which is
		//done by placing all 3 of the dimensions relative
		//to earth to get the max and min values. You need
		//to do 6 different reads, X+, X-, Y+, Y-, Z+ and Z-
		//to fully complete the calibration! Because the LCD
		//writes take a long time, ensure the accelerometer
		//is kept in that position for a fairly long duration.
		X = (float)(Xre-XMn)/(XMx-XMn);
		Y = (float)(Yre-YMn)/(YMx-YMn);
		Z = (float)(Zre-ZMn)/(ZMx-ZMn);

		//Print normalized values to screen
		XPos = PStr("XNrm: ", 0, 72, 0, Black, White);
		PNumF(X, XPos, 72, 2, 0, Black, White);

		XPos = PStr("YNrm: ", 0, 80, 0, Black, White);
		PNumF(Y, XPos, 80, 2, 0, Black, White);

		XPos = PStr("ZNrm: ", 0, 88, 0, Black, White);
		PNumF(Z, XPos, 88, 2, 0, Black, White);

	}
}
