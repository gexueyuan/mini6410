/**********************************************************
*实验要求：   定时器中断方式控制LED按精确时间间隔闪烁。
*功能描述：   本实验代码利用Tiny6410、mini6410开发板的Timer0
*           中断和Timer1中断分别控制LED1和LED2实现每隔精确
*           0.5s和5s的闪烁。
*日    期：   2011-3-10
*作    者：   国嵌
**********************************************************/
#include "sfr6410.h"
#include "gpio.h"
#include "def.h"

#include "library.h"
#include "system.h"
#include "intc.h"
#include "timer.h"

extern SYSC_GetClkInform(void);
//oGPIO_REGS类型在 gpio.h 中定义
#define GPIO 	   (( volatile oGPIO_REGS *)GPIO_BASE)

//函数声明
void __irq Isr_Timer(void);

void delay(int times);
void LedPortInit(void);
void LedDisplay(u8 data);
void TimerClrPend(u32 uTimer_No );
void TimerDisMask(u32 uTimer_No );
void TimerClkInit(u32 uTimer_No, u32 ms);
void TimerStart(u32 uTimer_No);
void TimerInit(void);

/*
 * 程序入口
 * */
int main(void)
{	
	SYSTEM_EnableVIC();
	SYSTEM_EnableIRQ();
	//用这个函数主要是获得g_PCLK的值
	SYSC_GetClkInform();  
	INTC_Init();
	
	LedPortInit();	
	
	TimerInit();
	LedDisplay(0x3);	
	
	while(1);   
}

/*
 * 延时函数
 * */
void delay(int times)
{
    int i;
    for(;times>0;times--)
      for(i=0;i<300;i++);
}

/*
 *   初始化连接LED灯的管脚资源
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
 *   用一个16进制数控制LED的亮灭
 * @ 每个LED对应一个二进制位，4个LED组成一个16进制数
 * */
void LedDisplay(u8 data)
{
	u32 tmpDat;
	tmpDat = GPIO->rGPIOKDAT; 
	tmpDat = (tmpDat & ~(0xf<<4))|(~((data&0xf)<<4));
	GPIO->rGPIOKDAT = tmpDat;
}

/*
 *   定时器中断处理函数，这个函数同时处理了Timer0和Timer1
 * 的中断服务请求，注意其中区分它们的方法
 * */
static u32 uCounter=1;
void __irq Isr_Timer(void)
{       
	u32 uTmp;
	uTmp = Inp32(rTINT_CSTAT);  
	if (uTmp&(1<<5))  //Timer0中断
	{
		TimerClrPend(0);
		LedDisplay(1<<0);
		delay(2000);
		LedDisplay(0);		
	}
	else if (uTmp&(1<<6)) //Timer1中断
	{
		TimerClrPend(1);
		if (uCounter==5)
		{
			LedDisplay(1<<1);
			delay(2000);
			LedDisplay(0);
			uCounter=1;	
		}
		else
			uCounter++;
	}
	
	//清除rVIC0ADDR，该寄存器按位记录哪个VIC0中断源曾发生了中断
	Outp32(rVIC0ADDR, 0);
}

/*
 * 清除Timer中断悬起位，方法是向对应位写1
 * */
void TimerClrPend(u32 uTimer_No )
{
 	u32 uTmp;
	uTmp = Inp32(rTINT_CSTAT);
	uTmp = (uTmp & 0x1f) | (1<<(5+uTimer_No));
	Outp32(rTINT_CSTAT,uTmp);      //  Timer1 Interrupt Clear register	
}

/*
 * 使能Timer中断位 
 * */
void TimerDisMask(u32 uTimer_No )
{
 	u32 uTmp;
	uTmp = Inp32(rTINT_CSTAT);
	uTmp = (uTmp & 0x1f) | (1<<uTimer_No);
	Outp32(rTINT_CSTAT,uTmp);      		
}

/*
 *   配置定时器时钟
 * @uTimer_No -- 待设置定时器号 
 * @ms -- 设置一次完整计数对应的毫秒数，最大可设2000左右
 * @g_PCLK -- 这个全局变量在SYSC_GetClkInform()中获得
 * */
void TimerClkInit(u32 uTimer_No, u32 ms)
{
 	u32 uTmp;
 	//设置Prescaler为128
 	uTmp = Inp32(rTCFG0);
 	if (uTimer_No<2)
		uTmp = (uTmp & ~0xff) | 0x7f;
 	else
 		uTmp = (uTmp & ~(0xff<<8)) | (0x7f<<8);
	Outp32(rTCFG0,uTmp); 		
	//设置MUX为16，总共2048分频
 	uTmp = Inp32(rTCFG1);
	uTmp = (uTmp & ~(0xf<<(uTimer_No*4))) | (0x4<<(uTimer_No*4));
	Outp32(rTCFG1,uTmp); 	
	//设置rTCNTBn，(g_PCLK>>11)/1000 算得的值是2048分频时1ms的计数值
	Outp32(rTCNTB0+0xc*uTimer_No, ((g_PCLK>>11)/1000)*ms);	
}

/*
 * 启动@uTimer_No 代表的定时器
 * */
void TimerStart(u32 uTimer_No)
{		
 	u32 uTmp;
	//设置Timer控制寄存器为 自动装载、手动更新(第一次装载时需要)
	//然后开启定时器(同时清手动更新位)
 	uTmp = Inp32(rTCON);	
	if (uTimer_No==0)
	{
		uTmp = (uTmp & ~0x1f) | 0xa;
		Outp32(rTCON,uTmp);		
		
		uTmp = (uTmp & ~0x1f) | 0x9;		
		Outp32(rTCON,uTmp); 
	}
	else
	{
		uTimer_No++;
		uTmp = (uTmp & ~(0xf<<(uTimer_No*4))) | (0xa<<(uTimer_No*4));				
		Outp32(rTCON,uTmp); 

		uTmp = (uTmp & ~(0xf<<(uTimer_No*4))) | (0x9<<(uTimer_No*4));				
		Outp32(rTCON,uTmp);
	}	
}

/*
 * 初始化Timer，这里对Timer0和Timer1进行了初始化并开启了它们
 * */
void TimerInit(void)
{
	u32 uConValue;
	
	//停止所有Timer
	Outp32(rTCON, 0);
	//配置定时器时钟
	TimerClkInit(0, 500);
	TimerClkInit(1, 1000);	
		
	//清除中断悬起位
	TimerClrPend(0);
	TimerClrPend(1);		
	//向rVIC0VECTADDR中写入对应中断服务程序的地址
	Outp32(rVIC0VECTADDR+NUM_TIMER0*4, (unsigned)Isr_Timer);
	Outp32(rVIC0VECTADDR+NUM_TIMER1*4, (unsigned)Isr_Timer);
	//使能对应中断源:
	uConValue = Inp32(rVIC0INTENABLE);
	uConValue |= (1<<NUM_TIMER0)|(1<<NUM_TIMER1);
	Outp32(rVIC0INTENABLE, uConValue);
	//接触屏蔽
	TimerDisMask(0);		
	TimerDisMask(1);
	
	//开启定时器
	TimerStart(0);
	TimerStart(1);
}
