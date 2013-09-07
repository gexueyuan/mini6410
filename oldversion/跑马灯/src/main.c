/**********************************************************
*实验要求：   用Tiny6410上的4个LED资源实现跑马灯程序。
*功能描述：   Tiny6410用下面4个引脚连接了LED发光二极管，分别是
*	          GPK4--LED1
*	          GPK5--LED2
*	          GPK6--LED3
*	          GPK7--LED4
*	          本程序将控制这四个管脚的输出电平，实现跑马灯的效果 
*日    期：   2011-3-10
*作    者：   国嵌
**********************************************************/
#include "def.h"
#include "gpio.h"

#define LED1_ON   ~(1<<4)
#define LED2_ON   ~(1<<5)
#define LED3_ON   ~(1<<6)
#define LED4_ON   ~(1<<7)

#define LED1_OFF   (1<<4)
#define LED2_OFF   (1<<5)
#define LED3_OFF   (1<<6)
#define LED4_OFF   (1<<7)
#define LEDALL_OFF (0xf<<4)

//GPIO
#define GPIO_BASE				(0x7F008000)
//oGPIO_REGS类型在 gpio.h 中定义
#define GPIO 	   (( volatile oGPIO_REGS *)GPIO_BASE)

//函数声明
void delay(int times);
void LedPortInit(void);
void LedRun(void);

/*
 * 程序入口
 * */
int main(void)
{	
	LedPortInit();
	LedRun();
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
	uConValue = GPIO->rGPIOKCON0;
	uConValue &= ~(0xffff<<16);
	uConValue |= 0x1111<<16;
	GPIO->rGPIOKCON0 = uConValue;			
}

/*
 *   跑马灯的实现函数
 * @ 通过控制连接LED的管脚的输出电平点亮和熄灭各个LED。
 * @ 逐个循环点亮各个LED。在每点亮一个后保持一定时间再熄灭它，接着
 * 点亮下一个LED，这样就形成了一个跑马灯的效果。
 * @ 这是一个需要改善的跑马灯程序，想想怎么优化这段代码。
 * */
void LedRun(void)
{
    GPIO->rGPIOKDAT |= LEDALL_OFF;
    while(1)
	{
		GPIO->rGPIOKDAT &= LED1_ON;
		delay(1000);
		GPIO->rGPIOKDAT |= LEDALL_OFF;

		GPIO->rGPIOKDAT &= LED2_ON;
		delay(1000);
		GPIO->rGPIOKDAT |= LEDALL_OFF;

		GPIO->rGPIOKDAT &= LED3_ON;
		delay(1000);
		GPIO->rGPIOKDAT |= LEDALL_OFF;

		GPIO->rGPIOKDAT &= LED4_ON;
		delay(1000);
		GPIO->rGPIOKDAT |= LEDALL_OFF;
    }
}

