#include <STC12C5A60S2.h>
#include <LCD1602.h>
#include <ADC.h>
#include <usart.h>
#include <string.h>
#include <intrins.h>
#define uchar	unsigned  char
#define uint	unsigned  int

#define FSCLK	11059200
//#define FSCLK	12000000

sbit moto=P1^1;//声明继电器连接引脚P11
float res0,res1;//res0当前电压，res1设定电压
uchar a,b,c;

uchar data_buffer[20],data_length = 0,flag = 0;//data_buffer串口接收缓存数组、data_length数组长度、flag接收标志
/**************命令集*************/
uchar table0[8]="SetValue";//命令1
uchar table1[16]={'S','e','t','V','a','l','u','e',':','x','.','x','x','O','K','.'};//返回1
uchar table2[5]="Start";//命令2
uchar table3[10]="Operating.";//返回2
uchar table4[4]="Stop";//命令3
uchar table5[7]="Stoped.";//返回3
/*********************************************************************************************************
** 函数功能 ：延时函数
** 函数说明 ：利用软件延时，占用CPU，经调试最小单位大约为1ms
** 入口参数 ：time:需要延时的时间，单位ms
** 出口参数 ：无
*********************************************************************************************************/
void Delay_ms(uint time)
{
	uint i,j;
	for(i = 0;i < time;i ++)
		for(j = 0;j < 930;j ++);
}
/*********************************************************************************************************
** 函数功能 ：当前电压显示函数
** 函数说明 ：显示当前电压
** 入口参数 ：无
** 出口参数 ：无
*********************************************************************************************************/
void Display_Now_U()
{
		Write_1602_String("NOW:U=",0x80);//第一行第1个字符位置开始显示
		Write_1602_Data(0x30 + (uint)res0%10);
		Write_1602_Data('.');
		Write_1602_Data(0x30 + (uint)(res0*10)%10);
		Write_1602_Data(0x30 + (uint)(res0*100)%10);
		Write_1602_Data('V');
}
/*********************************************************************************************************
** 函数功能 ：设定电压显示函数
** 函数说明 ：显示设定电压
** 入口参数 ：无
** 出口参数 ：无
*********************************************************************************************************/
void Display_Set_U()
{
	  Write_1602_String("SET:U=",0x80+0x40);//第二行第1个字符位置开始显示
	  Write_1602_Data(0x30 + (uint)res1%10);
  	Write_1602_Data('.');
	  Write_1602_Data(0x30 + (uint)(res1*10)%10);
	  Write_1602_Data(0x30 + (uint)(res1*100)%10);
  	Write_1602_Data('V');
}
/*********************************************************************************************************
** 函数功能 ：串口命令分析函数
** 函数说明 ：分析串口命令
** 入口参数 ：串口缓存数组、命令集数组、长度
** 出口参数 ：无
*********************************************************************************************************/
int Analysis(char *S,char *D,char LEN)
{
int n;
for(n=0;n<LEN;n++)
if(S[n]!=D[n]) return 1;//如果数组不相同返回1
return 0;//相同返回0
}

void main()
{

	LCD_1602_Init(); //液晶显示、初始化
	ADC_Init(ADC_PORT0); //配置通道P1^0为AD采集口
	USART_Init();//串口初始化
	moto=1;//继电器初始状态置1
	res1=1.28;//初始设定电压1.28V

	while(1)
	{
		res0=GetADCResult(ADC_CH0);	//获取AD转换电压
		Display_Now_U();//显示当前电压
		Display_Set_U();//显示设定电压
    if(flag==1)//如果接收到了串口数据
		{
			flag=0;//清零接收标志
			
		  a=Analysis(data_buffer,table0,8) ;//判断是不是"SetValue"命令
		  b=Analysis(data_buffer,table2,5) ;//判断是不是"Start"命令
			c=Analysis(data_buffer,table4,4) ;//判断是不是"Stop"命令
			  if(a==0)//是table0命令
			{
				 table1[10]=data_buffer[9];//获取设定电压值个位
				 table1[12]=data_buffer[10];//获取设定电压值小数点后第1位
				 table1[13]=data_buffer[11];//获取设定电压值小数点后第2位
			   Send_String(table1,16);//返回应答“SetValue：x.xxOK.”
         res1=data_buffer[9]+0.1*data_buffer[10]+0.01*data_buffer[11];//设定电压值赋给res1  				
			   a=1;
			}
				if(b==0)//如果是"Start"命令
			{
			   Send_String(table3,10);//返回应答"Operating."
         moto=0;//启动继电器			   
         b=1;				
			
			}
				if(c==0)////如果是"Stop"命令
			{
			   Send_String(table5,7);//返回应答"Stoped."
         moto=1;//关闭继电器			   
         c=1;							
			}			
     
		}
			
		Delay_ms(10);//延时10ms	
	}	
}

/************************** (C) *****END OF FILE*****************************/