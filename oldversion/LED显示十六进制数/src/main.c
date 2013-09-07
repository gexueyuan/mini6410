/**********************************************************
*ʵ��Ҫ��   ��Tiny6410�ϵ�4��LED��Դʵ����ʾʮ������������
*����������   Tiny6410������4������������LED��������ܣ��ֱ���
*	          GPK4--LED1
*	          GPK5--LED2
*	          GPK6--LED3
*	          GPK7--LED4
*	          �����򽫿������ĸ��ܽŵ������ƽ����ʾ0x0--0xF
*           ��ʮ����������
*��    �ڣ�   2011-3-10
*��    �ߣ�   ��Ƕ
**********************************************************/
#include "gpio.h"

//GPIO
#define GPIO_BASE				(0x7F008000)
//oGPIO_REGS������ gpio.h �ж���
#define GPIO 	   (( volatile oGPIO_REGS *)GPIO_BASE)

//��������
void delay(int times);
void LedPortInit(void);
void LedDisplay(u8);
void LedHexCounter(void);

/*
 * �������
 * */
int main(void)
{	
	LedPortInit();
	LedHexCounter();
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
	//��ע����������Ĵ����ķ�ʽ:
	// 	1.���� 2.���Ҫ�޸ĵ�λ 3.�޸Ķ�Ӧλ 4д��
	uConValue = GPIO->rGPIOKCON0;
	uConValue &= ~(0xffff<<16);
	uConValue |= 0x1111<<16;
	GPIO->rGPIOKCON0 = uConValue;			
}

/*
 *   ��ʾһ��ʮ��������
 * @ ÿ��LED��Ӧһ��������λ��4��LED���һ��16������
 * @ ��������������ʵ����һ�ڵ�����Ƴ��򣬸���ô����
 * */
void LedDisplay(u8 data)
{
	u32 tmpDat;
	tmpDat = GPIO->rGPIOKDAT; 
	tmpDat = (tmpDat & ~(0xf<<4))|(~((data&0xf)<<4));
	GPIO->rGPIOKDAT = tmpDat;	 
}

/*
 * ʮ����������ʾ�����ĸ�Led��0x0��0xFѭ������
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
