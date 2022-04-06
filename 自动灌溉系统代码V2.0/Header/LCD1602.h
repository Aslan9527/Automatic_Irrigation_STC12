#include<intrins.h>
sbit RS_1602 = P1^2;	
sbit RW_1602 = P1^3;
sbit EN_1602 = P1^4;	
#define LCD_PORT	P2 	

#define CLEAR_SCREEN			0X01		
#define CURSOR_RESET			0X02		

#define SET_MOD					0X04		

#define SET_MOD_AC_ADD			0X02		
#define SET_MOD_AC_DEC			0X00		
#define SET_MOD_MOVE_ON			0X01		
#define SET_MOD_MOVE_OFF		0X00		

#define DISPLAY_SET				0X08		

#define DISPLAY_SET_ON			0X04		
#define DISPLAY_SET_OFF			0X00		
#define DISPLAY_SET_CURSOR_ON	0X02		
#define DISPLAY_SET_CURSOR_OFF	0X00		
#define DISPLAY_SET_BLINK_ON	0X01	
#define DISPLEY_SET_BLINK_OFF	0X00		

#define COURSOR_SHIFT_LEFT		0X10		
#define COURSOR_SHIFT_RIGHT		0X14	
#define FRAME_SHIFT_LEFT		0X18		
#define FRAME_SHIFT_RIGHT		0X1C		

#define DISPLAY_MOD				0X30		
#define DISPLAY_MOD_TWO_LINE	0X08		
#define DISPLAY_MOD_ONE_LINE	0X00		
#define DISPLAY_MOD_5_10		0X04		
#define DISPLAY_MOD_5_7			0X00		

unsigned char code self_definition_char[] = {

0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,	
0x00,0x00,0x0E,0x00,0x1F,0x00,0x00,0x00,    
0x00,0x0E,0x00,0x0E,0x00,0x1F,0x00,0x00,	
0x00,0x1F,0x15,0x15,0x1B,0x11,0x1F,0x00, 
0x1F,0x04,0x04,0x1E,0x0A,0x12,0x1F,0x00,    
0x08,0x0f,0x12,0x0f,0x0a,0x1f,0x02,0x00,    
0x0f,0x09,0x0f,0x09,0x0f,0x09,0x11,0x00,    
0x1f,0x11,0x11,0x1f,0x11,0x11,0x1f,0x00,   

};	

const unsigned char CGRAM_ADD = 0X40;


void LCD_Delay(unsigned char z)
{
	unsigned char x,y;
	for(x = z;x > 0;x --)
		for(y = 50;y>0;y--);
}

unsigned char Check_1602_Busy(void)
{
	unsigned int time=0;
	RS_1602 = 0;
	RW_1602 = 1;
	EN_1602 = 1;
	while( (LCD_PORT&0X80) != 0X00)
	{
		time ++;
		if(time > 1000) return 1;	
	}	
	return 0;
}

void Write_1602_Com(unsigned char zhiling)
{
	Check_1602_Busy();
	RS_1602 = 0;
	RW_1602 = 0;
	LCD_PORT = zhiling;
	LCD_Delay(1);
	EN_1602 = 1;
	LCD_Delay(1);
	EN_1602 = 0;
}

void Write_1602_Data(unsigned char shuju)
{
	Check_1602_Busy();
	RS_1602 = 1;
	RW_1602 = 0;
	LCD_PORT = shuju;
	LCD_Delay(1);
	EN_1602 = 1;
	LCD_Delay(1);
	EN_1602 = 0;
}

void Write_1602_String(unsigned char *str,unsigned char addr)
{
	Write_1602_Com(addr);
	while(*str)
	{
		Write_1602_Data(*str);
		str++;
	}	
}


void Write_CGRAM(void)
{
	unsigned char i,j;
	for (i = 0; i < 8; i ++)
	{		
		for(j = 0;j < 8;j ++)
		{
			Write_1602_Com(CGRAM_ADD+i*8+j);		
			Write_1602_Data(self_definition_char[i*8+j]);			
		}
	}
}

void LCD_1602_Init()
{
	EN_1602=0;
	Write_1602_Com(DISPLAY_MOD | DISPLAY_MOD_TWO_LINE | DISPLAY_MOD_5_7);

	Write_1602_Com(DISPLAY_SET | DISPLAY_SET_ON | DISPLAY_SET_CURSOR_OFF | DISPLEY_SET_BLINK_OFF);
		
	Write_1602_Com(SET_MOD | SET_MOD_AC_ADD | SET_MOD_MOVE_OFF);

	Write_1602_Com(CLEAR_SCREEN);
	Write_1602_Com(CURSOR_RESET);
	Write_CGRAM();
	Write_1602_Com(0x80);
}
