extern unsigned char data_buffer[20],data_length,flag; 
void USART_Init()
{
	PCON &= 0x7F;		
	SCON = 0x50;		
	AUXR |= 0x40;		
	TMOD = 0X20;		
	TL1 = 0XFD;		   
	TH1 = 0XFD;		   
	TR1 = 1;			
	ES = 1;				
	EA = 1;				
}	  

void Send_Byte(unsigned char d)
{
	
	SBUF = d;
	while(!TI);	
	TI=0;		
}				 
void Send_String(unsigned char *str ,unsigned int length)	
{
	while(length!=0)
	{
		Send_Byte(*str++) ;
		length --;
	}
}

void USART_Interrupt(void)  interrupt 4	 
{
	EA = 0; 
   	if(RI) 		
   	RI=0;
    	data_buffer[data_length++] = SBUF;
		if(data_buffer[data_length-1] == '\n'){
		flag = 1;    {
  
		 data_length = 0;
		}
    }
	EA = 1;
}
