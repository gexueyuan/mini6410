/**********************************************************
*ʵ��Ҫ��   ��Tiny6410�ϵ�4��LED��Դʵ������Ƴ���
*����������   Tiny6410������4������������LED��������ܣ��ֱ���
*	          GPK4--LED1
*	          GPK5--LED2
*	          GPK6--LED3
*	          GPK7--LED4
*	          �����򽫿������ĸ��ܽŵ������ƽ��ʵ������Ƶ�Ч�� 
*��    �ڣ�   2011-3-10
*��    �ߣ�   ��Ƕ
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
//oGPIO_REGS������ gpio.h �ж���
#define GPIO 	   (( volatile oGPIO_REGS *)GPIO_BASE)

//��������
void delay(int times);
void LedPortInit(void);
void LedRun(void);

/*
 * �������
 * */
int main(void)
{	
	LedPortInit();
	LedRun();
}

/*
 * ��ʱ����
 * */
void delay(int times)
{
    int i;
    for(;times>0;times--)
      for(i=0;i<3000;i++);
}

/*
 *   ��ʼ������LED�ƵĹܽ���Դ
 * @ ͨ����GPIO_BASEǿ��ת��Ϊ(volatile oGPIO_REGS*)�͵�ָ����Ժܷ���
 * �ķ��ʸ���GPIO�Ĵ�����ֵ�����ַ�����ͨ��ʹ�üĴ�����ַ�ĺ궨�����
 * �Ĵ�����Ԫ���ӹ淶�Ϳ�ѧ��
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
 *   ����Ƶ�ʵ�ֺ���
 * @ ͨ����������LED�Ĺܽŵ������ƽ������Ϩ�����LED��
 * @ ���ѭ����������LED����ÿ����һ���󱣳�һ��ʱ����Ϩ����������
 * ������һ��LED���������γ���һ������Ƶ�Ч����
 * @ ����һ����Ҫ���Ƶ�����Ƴ���������ô�Ż���δ��롣
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

