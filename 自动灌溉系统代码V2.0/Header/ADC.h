#include<intrins.h>

#define ADC_PORT0			0X01
#define	ADC_PORT1			0X02
#define ADC_PORT2			0X04
#define ADC_PORT3			0X08
#define ADC_PORT4			0X10
#define ADC_PORT5			0X20
#define ADC_PORT6			0X40
#define ADC_PORT7			0X80
#define ADC_PORTALL			0XFF

#define ADC_CH0				0X00
#define ADC_CH1				0X01
#define ADC_CH2				0X02
#define ADC_CH3				0X03
#define ADC_CH4				0X04
#define ADC_CH5				0X05
#define ADC_CH6				0X06
#define ADC_CH7				0X07

#define ADC_SPEEDLL_540 	0X00           
#define ADC_SPEEDLL_360		0X20
#define ADC_SPEEDLL_180		0X40
#define ADC_SPEEDLL_90		0X60

#define ADC_POWER   		0X80            
#define ADC_FLAG    		0X10           
#define ADC_START   		0X08            



void ADC_Init(unsigned char port)
{
	P1ASF=port;
	ADC_RES=0;
	ADC_CONTR=ADC_POWER | ADC_SPEEDLL_540;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
float GetADCResult(unsigned char channel)
{
	unsigned int ADC_RESULT = 0;
	float result;
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL_540 | ADC_START | channel;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR & ADC_FLAG));
	ADC_CONTR &= ~ADC_FLAG;
	ADC_RESULT = ADC_RES;
	ADC_RESULT = (ADC_RESULT << 2) | (0x02 & ADC_RESL);
	result = ADC_RESULT * 5.0 / 1024.0 ;  
	return result;
}