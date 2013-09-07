/**********************************************************
*ʵ��Ҫ��   ��ʱ���жϷ�ʽ����LED����ȷʱ������˸��
*����������   ��ʵ���������Tiny6410��mini6410�������Timer0
*           �жϺ�Timer1�жϷֱ����LED1��LED2ʵ��ÿ����ȷ
*           0.5s��5s����˸��
*��    �ڣ�   2011-3-10
*��    �ߣ�   ��Ƕ
**********************************************************/
#include "sfr6410.h"
#include "gpio.h"
#include "def.h"

#include "library.h"
#include "system.h"
#include "intc.h"
#include "timer.h"

extern SYSC_GetClkInform(void);
//oGPIO_REGS������ gpio.h �ж���
#define GPIO 	   (( volatile oGPIO_REGS *)GPIO_BASE)

//��������
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
 * �������
 * */
int main(void)
{	
	SYSTEM_EnableVIC();
	SYSTEM_EnableIRQ();
	//�����������Ҫ�ǻ��g_PCLK��ֵ
	SYSC_GetClkInform();  
	INTC_Init();
	
	LedPortInit();	
	
	TimerInit();
	LedDisplay(0x3);	
	
	while(1);   
}

/*
 * ��ʱ����
 * */
void delay(int times)
{
    int i;
    for(;times>0;times--)
      for(i=0;i<300;i++);
}

/*
 *   ��ʼ������LED�ƵĹܽ���Դ
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
 *   ��һ��16����������LED������
 * @ ÿ��LED��Ӧһ��������λ��4��LED���һ��16������
 * */
void LedDisplay(u8 data)
{
	u32 tmpDat;
	tmpDat = GPIO->rGPIOKDAT; 
	tmpDat = (tmpDat & ~(0xf<<4))|(~((data&0xf)<<4));
	GPIO->rGPIOKDAT = tmpDat;
}

/*
 *   ��ʱ���жϴ��������������ͬʱ������Timer0��Timer1
 * ���жϷ�������ע�������������ǵķ���
 * */
static u32 uCounter=1;
void __irq Isr_Timer(void)
{       
	u32 uTmp;
	uTmp = Inp32(rTINT_CSTAT);  
	if (uTmp&(1<<5))  //Timer0�ж�
	{
		TimerClrPend(0);
		LedDisplay(1<<0);
		delay(2000);
		LedDisplay(0);		
	}
	else if (uTmp&(1<<6)) //Timer1�ж�
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
	
	//���rVIC0ADDR���üĴ�����λ��¼�ĸ�VIC0�ж�Դ���������ж�
	Outp32(rVIC0ADDR, 0);
}

/*
 * ���Timer�ж�����λ�����������Ӧλд1
 * */
void TimerClrPend(u32 uTimer_No )
{
 	u32 uTmp;
	uTmp = Inp32(rTINT_CSTAT);
	uTmp = (uTmp & 0x1f) | (1<<(5+uTimer_No));
	Outp32(rTINT_CSTAT,uTmp);      //  Timer1 Interrupt Clear register	
}

/*
 * ʹ��Timer�ж�λ 
 * */
void TimerDisMask(u32 uTimer_No )
{
 	u32 uTmp;
	uTmp = Inp32(rTINT_CSTAT);
	uTmp = (uTmp & 0x1f) | (1<<uTimer_No);
	Outp32(rTINT_CSTAT,uTmp);      		
}

/*
 *   ���ö�ʱ��ʱ��
 * @uTimer_No -- �����ö�ʱ���� 
 * @ms -- ����һ������������Ӧ�ĺ�������������2000����
 * @g_PCLK -- ���ȫ�ֱ�����SYSC_GetClkInform()�л��
 * */
void TimerClkInit(u32 uTimer_No, u32 ms)
{
 	u32 uTmp;
 	//����PrescalerΪ128
 	uTmp = Inp32(rTCFG0);
 	if (uTimer_No<2)
		uTmp = (uTmp & ~0xff) | 0x7f;
 	else
 		uTmp = (uTmp & ~(0xff<<8)) | (0x7f<<8);
	Outp32(rTCFG0,uTmp); 		
	//����MUXΪ16���ܹ�2048��Ƶ
 	uTmp = Inp32(rTCFG1);
	uTmp = (uTmp & ~(0xf<<(uTimer_No*4))) | (0x4<<(uTimer_No*4));
	Outp32(rTCFG1,uTmp); 	
	//����rTCNTBn��(g_PCLK>>11)/1000 ��õ�ֵ��2048��Ƶʱ1ms�ļ���ֵ
	Outp32(rTCNTB0+0xc*uTimer_No, ((g_PCLK>>11)/1000)*ms);	
}

/*
 * ����@uTimer_No ����Ķ�ʱ��
 * */
void TimerStart(u32 uTimer_No)
{		
 	u32 uTmp;
	//����Timer���ƼĴ���Ϊ �Զ�װ�ء��ֶ�����(��һ��װ��ʱ��Ҫ)
	//Ȼ������ʱ��(ͬʱ���ֶ�����λ)
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
 * ��ʼ��Timer�������Timer0��Timer1�����˳�ʼ��������������
 * */
void TimerInit(void)
{
	u32 uConValue;
	
	//ֹͣ����Timer
	Outp32(rTCON, 0);
	//���ö�ʱ��ʱ��
	TimerClkInit(0, 500);
	TimerClkInit(1, 1000);	
		
	//����ж�����λ
	TimerClrPend(0);
	TimerClrPend(1);		
	//��rVIC0VECTADDR��д���Ӧ�жϷ������ĵ�ַ
	Outp32(rVIC0VECTADDR+NUM_TIMER0*4, (unsigned)Isr_Timer);
	Outp32(rVIC0VECTADDR+NUM_TIMER1*4, (unsigned)Isr_Timer);
	//ʹ�ܶ�Ӧ�ж�Դ:
	uConValue = Inp32(rVIC0INTENABLE);
	uConValue |= (1<<NUM_TIMER0)|(1<<NUM_TIMER1);
	Outp32(rVIC0INTENABLE, uConValue);
	//�Ӵ�����
	TimerDisMask(0);		
	TimerDisMask(1);
	
	//������ʱ��
	TimerStart(0);
	TimerStart(1);
}
