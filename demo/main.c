#include "utils.h"

static void LedDelay(void)
{
    	volatile unsigned int k;
    	for(k = 0; k < 20000000; k++);
}

int _main(void)
{

    Uart_Init();
    Port_Init();
    Uart_SendString("\r\nHello, Mini6410\r\n");
    
    for(;;) {
    	Led_Display(0x9); // 1001
		LedDelay();
    	Led_Display(0x6); // 0110
		LedDelay();
    }

    return 0;

}

