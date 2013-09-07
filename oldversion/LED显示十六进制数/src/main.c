/**********************************************************
*实验要求：   用Tiny6410上的4个LED资源实现显示十六进制数程序。
*功能描述：   Tiny6410用下面4个引脚连接了LED发光二极管，分别是
*	          GPK4--LED1
*	          GPK5--LED2
*	          GPK6--LED3
*	          GPK7--LED4
*	          本程序将控制这四个管脚的输出电平，显示0x0--0xF
*           的十六进制数。
*日    期：   2011-3-10
*作    者：   国嵌
**********************************************************/
#include "gpio.h"

//GPIO
#define GPIO_BASE				(0x7F008000)
//oGPIO_REGS类型在 gpio.h 中定义
#define GPIO 	   (( volatile oGPIO_REGS *)GPIO_BASE)

//函数声明
void delay(int times);
void LedPortInit(void);
void LedDisplay(u8);
void LedHexCounter(void);

/*
 * 程序入口
 * */
int main(void)
{	
	LedPortInit();
	LedHexCounter();
}

/*
 * 延时函数
 * */
void delay(int times)
{
    int i;
    for(;times>0;times--)
      for(i=0;i<3000;i++);
}

/*
 *   初始化连接LED灯的管脚资源
 * @ 通过将GPIO_BASE强制转化为(volatile oGPIO_REGS*)型的指针可以很方便
 * 的访问各个GPIO寄存器的值，这种方法比通过使用寄存器地址的宏定义访问
 * 寄存器单元更加规范和科学。
 * */  
void LedPortInit(void)
{
	u32 uConValue;
	//请注意下面操作寄存器的方式:
	// 	1.读出 2.清除要修改的位 3.修改对应位 4写回
	uConValue = GPIO->rGPIOKCON0;
	uConValue &= ~(0xffff<<16);
	uConValue |= 0x1111<<16;
	GPIO->rGPIOKCON0 = uConValue;			
}

/*
 *   显示一个十六进制数
 * @ 每个LED对应一个二进制位，4个LED组成一个16进制数
 * @ 如果用这个函数来实现上一节的跑马灯程序，该怎么做？
 * */
void LedDisplay(u8 data)
{
	u32 tmpDat;
	tmpDat = GPIO->rGPIOKDAT; 
	tmpDat = (tmpDat & ~(0xf<<4))|(~((data&0xf)<<4));
	GPIO->rGPIOKDAT = tmpDat;	 
}

/*
 * 十六进制数显示程序，四个Led从0x0到0xF循环计数
 * */
void LedHexCounter(void)
{
	int hex=0x0;
    while(1)
	{
		LedDisplay(hex);
		hex = (hex==0xf? 0x0: hex+1);
		delay(1000);
    }
}
