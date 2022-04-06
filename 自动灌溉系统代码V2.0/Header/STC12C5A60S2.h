#ifndef __5204_H__
#define __5204_H__

sfr P0    = 0x80;
sfr P1    = 0x90;
sfr P2    = 0xA0;
sfr P3    = 0xB0;
sfr PSW   = 0xD0;
sfr ACC   = 0xE0;
sfr B     = 0xF0;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
sfr PCON  = 0x87;
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;
sfr IE    = 0xA8;
sfr IP    = 0xB8;
sfr SCON  = 0x98;
sfr SBUF  = 0x99;
sfr PLASF = 0x9D;

sfr CH         = 0XF9;
sfr CCAP0H     = 0XFA;
sfr CCAP1H     = 0XFB;
sfr PCA_PWM0   = 0XF2;
sfr PCA_PWM1   = 0XF3;
sfr CL         = 0XE9;
sfr CCAP0L     = 0XEA;
sfr CCAP1L     = 0XEB;
sfr CCON       = 0XD8;
sfr CMOD       = 0XD9;
sfr CCAPM0     = 0XDA;
sfr CCAPM1     = 0XDB;
sfr P5         = 0XC8;
sfr P5M1       = 0XC9;
sfr P5M0       = 0XCA;
sfr SPSTAT     = 0XCD;
sfr SPCTL      = 0XCE;
sfr SPDAT      = 0XCF;
sfr P4         = 0XC0;
sfr WDT_CONTR  = 0XC1;
sfr IAP_DATA   = 0XC2;
sfr IAP_ADDRH  = 0XC3;
sfr IAP_ADDRL  = 0XC4;
sfr IAP_CMD    = 0XC5;
sfr IAP_TRIG   = 0XC6;
sfr IAP_CONTR  = 0XC7;
sfr P4SW       = 0XBB;
sfr ADC_CONTR  = 0XBC;
sfr ADC_RES    = 0XBD;
sfr ADC_RESL   = 0XBE;
sfr P3M1       = 0XB1;
sfr P3M0       = 0XB2;
sfr P4M1       = 0XB3;
sfr P4M0       = 0XB4;
sfr IP2        = 0XB5;
sfr IP2H       = 0XB6;
sfr IPH        = 0XB7;
sfr IE2        = 0XAF;
sfr BUS_SPEED  = 0XA1;
sfr AUXR1      = 0XA2;
sfr S2CON      = 0X9A;
sfr S2BUF      = 0X9B;
sfr BRT        = 0X9C;
sfr P1ASF      = 0X9D;
sfr P1M1       = 0X91;
sfr P1M0       = 0X92;
sfr P0M1       = 0X93;
sfr P0M0       = 0X94;
sfr P2M1       = 0X95;
sfr P2M0       = 0X96;
sfr CLK_DIV    = 0X97;
sfr AUXR       = 0X8E; 
sfr WAKE_CLK0  = 0X8F;



sfr T2CON  = 0xC8;
sfr T2MOD  = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;

sfr IPA   = 0xF8;
sfr IEA   = 0xE8;
sfr SADEN = 0xA9;
sfr SPSR  = 0xAA;


sfr WDTD  = 0x85;
sfr SPDR  = 0x86;
sfr SFCF  = 0xB1;
sfr SFCM  = 0xB2;
sfr SFAL  = 0xB3;
sfr SFAH  = 0xB4;
sfr SFDT  = 0xB5;
sfr SFST  = 0xB6;
sfr SPCR  = 0xD5;
sfr IPAH  = 0xF7;

sbit CY    = PSW^7;
sbit AC    = PSW^6;
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;
sbit P     = PSW^0; 

sbit TF1   = TCON^7;
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;


sbit EA    = IE^7;
sbit ELVD  = IE^6; 
sbit EADC  = IE^5; 
sbit ES    = IE^4;
sbit ET1   = IE^3;
sbit EX1   = IE^2;
sbit ET0   = IE^1;
sbit EX0   = IE^0;


sbit PPCA   = IP^7;
sbit PLVD   = IP^6;
sbit PADC   = IP^5;
sbit PS     = IP^4;
sbit PT1    = IP^3;
sbit PX1    = IP^2;
sbit PT0    = IP^1;
sbit PX0    = IP^0;


sbit RD    = P3^7;
sbit WR    = P3^6;
sbit T1    = P3^5;
sbit T0    = P3^4;
sbit INT1  = P3^3;
sbit INT0  = P3^2;
sbit TXD   = P3^1;
sbit RXD   = P3^0;


sbit SM0   = SCON^7;
sbit SM1   = SCON^6;
sbit SM2   = SCON^5;
sbit REN   = SCON^4;
sbit TB8   = SCON^3;
sbit RB8   = SCON^2;
sbit TI    = SCON^1;
sbit RI    = SCON^0;


sbit T2EX  = P1^1; 
sbit T2    = P1^0; 
             

sbit TF2    = T2CON^7;
sbit EXF2   = T2CON^6;
sbit RCLK   = T2CON^5;
sbit TCLK   = T2CON^4;
sbit EXEN2  = T2CON^3;
sbit TR2    = T2CON^2;
sbit C_T2   = T2CON^1;
sbit CP_RL2 = T2CON^0;


sbit CF                  = CCON^7; 
sbit CR                  = CCON^6; 
sbit CCF1                = CCON^1; 
sbit CCF0                = CCON^0; 


#endif
