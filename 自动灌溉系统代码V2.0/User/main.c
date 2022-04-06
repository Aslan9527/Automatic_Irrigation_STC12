#include <STC12C5A60S2.h>
#include <LCD1602.h>
#include <ADC.h>
#include <usart.h>
#include <string.h>
#include <intrins.h>
#define uchar	unsigned  char
#define uint	unsigned  int
#define FSCLK	11059200

sbit moto=P1^1;
float res0,res1;
uchar a,b,c;
uchar i;
uchar data_buffer[20],data_length = 0,flag = 0;
uchar table0[8]="SetValue";
uchar table1[]={'S','e','t','V','a','l','u','e',':','x','.','x','x','O','K','.'};
uchar table2[5]="Start";
uchar table3[10]="Operating.";
uchar table4[4]="Stop";
uchar table5[7]="Stoped.";
uchar table6[]={'S','e','t','V','a','l','u','e',':',' ','x','x','x','.'};


void Delay_ms(uint time)
{
	uint i,j;
	for(i = 0;i < time;i ++)
		for(j = 0;j < 930;j ++);
}

void Display_Now_U()
{
		Write_1602_String("NOW:U=",0x80);
		Write_1602_Data(0x30 + (uint)res0%10);
		Write_1602_Data('.');
		Write_1602_Data(0x30 + (uint)(res0*10)%10);
		Write_1602_Data(0x30 + (uint)(res0*100)%10);
		Write_1602_Data('V');
}

void Display_Set_U()
{
	  Write_1602_String("SET:U=",0x80+0x40);
	  Write_1602_Data(0x30 + (uint)res1%10);
  	Write_1602_Data('.');
	  Write_1602_Data(0x30 + (uint)(res1*10)%10);
	  Write_1602_Data(0x30 + (uint)(res1*100)%10);
  	Write_1602_Data('V');
}


int Analysis(char *S,char *D,char LEN)    
{
int n;
for(n=0;n<LEN;n++)
if(S[n]!=D[n]) return 1;
return 0;
}

void main()
{

	LCD_1602_Init(); 
	ADC_Init(ADC_PORT0); 
	USART_Init();
	moto=1;
	res1=1.28;

	while(1)
	{
		res0=GetADCResult(ADC_CH0);	
		Display_Now_U();
		Display_Set_U();
		if(flag==1)
		{
			flag=0;
			
			a=Analysis(data_buffer,table0,8) ;
			b=Analysis(data_buffer,table2,5) ;
			c=Analysis(data_buffer,table4,4) ;
			  if(a==0)
			{
				if(data_buffer[10]!=NULL)
				{
					table1[9]=data_buffer[9];
					table1[10]=data_buffer[10];
					table1[11]=data_buffer[11];
					table1[12]=data_buffer[12];
					Send_String(table1,16); 	
					res1=(data_buffer[9]-48)*100+(data_buffer[11]-48)*10+(data_buffer[12]-48);	
					res1 = res1/100;
				}
				else
				{
					table1[9]='x';
					 table1[10]='.';
					 table1[11]='x';
					 table1[12]='x';
					Send_String(table6,14);
					res1 = 0;
				}					
				a=1;
				
			}
				if(b==0)
			{
				Send_String(table3,10);
				moto=0;			   
				b=1;				
			
			}
				if(c==0)
			{
			   Send_String(table5,7);
				moto=1;
				c=1;							
			}

				for(i=0;i<20;i++)
			{
				data_buffer[i]=NULL;
			}
     
		}
			
		Delay_ms(10);
	}	
}