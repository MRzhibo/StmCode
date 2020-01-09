#include "reg52.h"
#include "stdio.h"

sbit LED_CHOODE3 = P2^0;
sbit LED_CHOODE2 = P2^1;
sbit LED_CHOODE1 = P2^2; 
sbit BEEP = P2^5;
sbit close = P2^6;
sbit LED1 = P1^6;
sbit LED2 = P1^7;
sbit LED3 = P2^4;
sbit LED4 = P2^3;

sbit K1 = P1^0;
sbit K2 = P1^1;
sbit K3 = P1^2;
sbit K4 = P1^3;
sbit K5 = P1^4;
sbit K6 = P1^5;
#define uint unsigned int 
#define uchar unsigned char
#define Numeric P0
#define KEY1   1
#define KEY2   2
#define KEY3   3
#define KEY4   4
#define KEY5   5
#define KEY6   6
uint  statu = 1;
uint count_num = 0;
uint qian,bai,shi,ge;
uint data1,data2,data3,data4;

uint count = 0;
uint open_cont = 0;
uint close_cont = 0;
uint open_num1 = 0;
uint open_num2 = 0;
uint close_num1 = 0;
uint close_num2 = 0;

uint key_flag = 0;
uint show_flag = 0;
uint open_flag = 1;
uint close_flag = 0;
uchar code Numeric_number[15] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //0~9
void Dynamic_show();
uchar i;

void delayms(uint xms)
{
	uint i,j;
    for(i=xms;i>0;i--)
        for(j=110;j>0;j--);
}


void Statu_set()
{
	switch(statu)
		{
			case 1:LED_CHOODE1 = 1;LED_CHOODE2 = 1;LED_CHOODE3 = 0;
						 break;
			case 2:LED_CHOODE1 = 0;LED_CHOODE2 = 1;LED_CHOODE3 = 0;
						 break;
			case 3:LED_CHOODE1 = 1;LED_CHOODE2 = 0;LED_CHOODE3 = 0;
						 break;
			case 4:LED_CHOODE1 = 0;LED_CHOODE2 = 0;LED_CHOODE3 = 0;
						 break;
			case 5:LED_CHOODE1 = 1;LED_CHOODE2 = 1;LED_CHOODE3 = 1;
						 break;
			case 6:LED_CHOODE1 = 0;LED_CHOODE2 = 1;LED_CHOODE3 = 1;
						 break;
			case 7:LED_CHOODE1 = 1;LED_CHOODE2 = 0;LED_CHOODE3 = 1;
						 break;
			case 8:LED_CHOODE1 = 0;LED_CHOODE2 = 0;LED_CHOODE3 = 1;
						 break;
		}
}

/*mode = 0 单次按键   1 ： 连续按键*/
uint KeyScan(uchar mode)
{
	static uchar keyen=1;
	if(mode==1)
	{
		keyen=1;
	}
	if(keyen==1&&(K1==0||K2==0||K3==0||K4==0||K5==0||K6==0))
	{
		delayms(5);  //消抖处理
		keyen=0;
		if(K1==0)return KEY1;
		else if(K2==0)return KEY2;
		else if(K3==0)return KEY3;
		else if(K4==0)return KEY4;
		else if(K5==0)return KEY5;
		else if(K6==0)return KEY6;
	}
	else if(K1==1&&K2==1&&K3==1&&K4==1&&K5==1&&K6==1)
	{
		keyen=1;
	}
	return 0;	
}

//开关次数统计
void Synchr_display()
{
	if(count_num>9999)
		count_num = 0;
	qian = count_num/1000;
	bai = (count_num%1000)/100;
	shi = (count_num%100)/10;
	ge = count_num%10;
	
	LED_CHOODE1 = 0;LED_CHOODE2 = 0;LED_CHOODE3 = 1;
	Numeric = Numeric_number[ge];
	delayms(1);
	
	LED_CHOODE1 = 1;LED_CHOODE2 = 0;LED_CHOODE3 = 1;
	Numeric = Numeric_number[shi];
	delayms(1);
	
	LED_CHOODE1 = 0;LED_CHOODE2 = 1;LED_CHOODE3 = 1;
	Numeric = Numeric_number[bai];
	delayms(1);
	
	LED_CHOODE1 = 1;LED_CHOODE2 = 1;LED_CHOODE3 = 1;
	Numeric = Numeric_number[qian];
	delayms(1);
}



/*继电开关显示*/
void Open_display()
{
	if(open_cont>99)
		open_cont = 0;
	data1 = open_cont/10;
	data2 = open_cont%10;
	
	LED_CHOODE1 = 1;LED_CHOODE2 = 1;LED_CHOODE3 = 0;
	Numeric = Numeric_number[data1];
	delayms(1);
	
	LED_CHOODE1 = 0;LED_CHOODE2 = 1;LED_CHOODE3 = 0;
	Numeric = Numeric_number[data2];
	delayms(1);
	
}

void Close_display()
{
	if(close_cont>99)
		close_cont = 0;
	data3 = close_cont/10;
	data4 = close_cont%10;
	
	LED_CHOODE1 = 1;LED_CHOODE2 = 0;LED_CHOODE3 = 0;
	Numeric = Numeric_number[data3];
	delayms(1);
	
	LED_CHOODE1 = 0;LED_CHOODE2 = 0;LED_CHOODE3 = 0;
	Numeric = Numeric_number[data4];
	delayms(1);
}


/*按键功能函数*/
void datapros()
{
	uint key=KeyScan(0);
	switch(key)
	{
		case 1: 
				if(key_flag == 1)
				{
					
					switch(statu)
					{
						case 1 :
							open_num1++;
							if(open_num1>=10)
							{
								open_num1=0; 
							}
							Numeric = Numeric_number[open_num1];
							break;
						case 2 :
							open_num2++;
							if(open_num2>=10)
							{
								open_num2=0; 
							}
							Numeric = Numeric_number[open_num2];
							break;
						case 3 :
							close_num1++;
							if(close_num1>=10)
								{
									close_num1=0; 
								}
							Numeric = Numeric_number[close_num1];
							break;
						case 4 :
							close_num2++;
							if(close_num2>=10)
								{
									close_num2=0; 
								}
							Numeric = Numeric_number[close_num2];
							break;
					}			
				}
			break;//add
		case 2:  
			if(key_flag == 1)
			{
				Statu_set();
				switch(statu)
					{
						case 1 :
							if(open_num1<=0)
							{
								open_num1=10; 
							}
							open_num1--;
							Numeric = Numeric_number[open_num1];
							break;
						case 2 :
							if(open_num2<=0)
							{
								open_num2=10; 
							}
							open_num2--;
							Numeric = Numeric_number[open_num2];
							break;
						case 3 :
							if(close_num1<=0)
							{
								close_num1=10; 
							}
							close_num1--;
							Numeric = Numeric_number[close_num1];
							break;
						case 4 :
							if(close_num2<=0)
							{
								close_num2=10; 
							}
							close_num2--;
							Numeric = Numeric_number[close_num2];
							break;
					}			
			}
			break;//cat
		case 3:  
			if(key_flag == 1)
				{	
					if(statu >= 4)
					{ 
						statu = 0;  
					}		
					statu++;
					Statu_set(); //位选
					switch(statu)
					{
						case 1:Numeric = Numeric_number[open_num1];break;
						case 2:Numeric = Numeric_number[open_num2];break;
						case 3:Numeric = Numeric_number[close_num1];break;
						case 4:Numeric = Numeric_number[close_num2];break;
					}
		    }			
			break;  // move right
		case 4:  
			if(key_flag == 1)
				{
					if(statu <= 1) 
					{
						statu = 5;
					}
					statu--;  
					Statu_set(); //位选
					switch(statu)
					{
						case 1:Numeric = Numeric_number[open_num1];break;
						case 2:Numeric = Numeric_number[open_num2];break;
						case 3:Numeric = Numeric_number[close_num1];break;
						case 4:Numeric = Numeric_number[close_num2];break;
					}
				}					
			break;  // move left
		case 5:  
			key_flag = 1;
		  count_num = 0;
	   	show_flag = 0;
			open_num1 = 0;
      open_num2 = 0;
      close_num1 = 0;
      close_num2 = 0;
			statu = 1;
			LED_CHOODE1 = 1;LED_CHOODE2 = 1;LED_CHOODE3 = 0;
			Numeric = Numeric_number[0];
			break;//按键设置开始
		case 6:
			key_flag = 0;
		  show_flag = 1;
			open_cont = open_num1*10 + open_num2;
			close_cont = close_num1*10 + close_num2;
			break;//设置完成 break;
	}
}


/*中断计数函数*/
void Timer() interrupt 1
{
	if(count >= 20)
	{				//20*50MS定时时间为1.0秒
		count=0;
//		BEEP = ~BEEP;
//		close = ~close;
		if(open_flag == 1)
		{
				open_cont--;
				if(open_cont <= 0)
				{
					open_flag = 0;
					close_flag = 1;
					close = ~close;
				}
		}
		if(close_flag == 1)
		{
			close_cont--;
			if(close_cont<=0)
			{
				open_flag = 1;
				close = ~close;
				close_flag = 0;
				count_num++;
				open_cont = open_num1*10 + open_num2;
				close_cont = close_num1*10 + close_num2;
			}
		}
	}
		TH0=(65536-50000)/256;	//重新赋值
		TL0=(65536-50000)%256;
		count++;			//50毫秒加1，加20次为一秒
}


/*
	main function
*/

void main(void)
{
	TMOD &= 0X0F;		/*中断初始化*/
	TMOD |= 0X01;
	TH0=(65536-50000)/256;	
	TL0=(65536-50000)%256;
	EA=1;				//中断总开关
	ET0=1;				//请求中断
	TR0=1;				//允许中断
	
	close = 1;
	BEEP = 0;
	LED_CHOODE1 = 1;LED_CHOODE2 = 1;LED_CHOODE3 = 0;
	Numeric = Numeric_number[0];
	
	while(1)
	{
		if(show_flag == 1)
		{
			if(open_flag == 1)
			{
				Open_display();
			}
			if(close_flag == 1)
			{
				Close_display();
			}
			Synchr_display();
		}
		datapros();
	}
}

	







