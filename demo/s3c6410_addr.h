#ifndef __S3C6410ADDR_H__
#define __S3C6410ADDR_H__

#ifdef __cplusplus
extern "C" {
#endif

// System Controller
#define SYSCON_BASE        (0x7E00F000)
#define rMEM_SYS_CFG    (*(volatile unsigned *)(SYSCON_BASE+0x120))

// GPIO
#define GPIO_BASE    (0x7F008000)
#define rGPACON        (*(volatile unsigned *)(GPIO_BASE+0x00))
#define rGPADAT        (*(volatile unsigned *)(GPIO_BASE+0x04))
#define rGPAPUD        (*(volatile unsigned *)(GPIO_BASE+0x08))
#define rGPBCON        (*(volatile unsigned *)(GPIO_BASE+0x20))
#define rGPBDAT        (*(volatile unsigned *)(GPIO_BASE+0x24))
#define rGPBPUD        (*(volatile unsigned *)(GPIO_BASE+0x28))
#define rGPNCON        (*(volatile unsigned *)(GPIO_BASE+0x830))
#define rGPNDAT        (*(volatile unsigned *)(GPIO_BASE+0x834))
#define rGPNPUD        (*(volatile unsigned *)(GPIO_BASE+0x838))

// NAND Flash Controller
#define NANDF_BASE    (0x70200000)
#define rNFCONF        (*(volatile unsigned *)(NANDF_BASE+0x00))        //NAND Flash configuration
#define rNFCONT        (*(volatile unsigned *)(NANDF_BASE+0x04))          //NAND Flash control
#define rNFCMD        (*(volatile unsigned *)(NANDF_BASE+0x08))         //NAND Flash command
#define rNFADDR        (*(volatile unsigned *)(NANDF_BASE+0x0C))         //NAND Flash address
#define rNFDATA        (*(volatile unsigned *)(NANDF_BASE+0x10))          //NAND Flash data
#define rNFDATA8    (*(volatile unsigned char *)(NANDF_BASE+0x10))    //NAND Flash data (byte)
#define rNFDATA32    (*(volatile unsigned *)(NANDF_BASE+0x10))       //NAND Flash data (word)
#define NFDATA        (NANDF_BASE+0x10)
#define rNFMECCD0    (*(volatile unsigned *)(NANDF_BASE+0x14))          //NAND Flash ECC for Main
#define rNFMECCD1    (*(volatile unsigned *)(NANDF_BASE+0x18))          //NAND Flash ECC for Main
#define rNFSECCD    (*(volatile unsigned *)(NANDF_BASE+0x1C))          //NAND Flash ECC for Spare Area
#define rNFSBLK         (*(volatile unsigned *)(NANDF_BASE+0x20))        //NAND Flash programmable start block address
#define rNFEBLK         (*(volatile unsigned *)(NANDF_BASE+0x24))            //NAND Flash programmable end block address
#define rNFSTAT         (*(volatile unsigned *)(NANDF_BASE+0x28))          //NAND Flash operation status
#define rNFECCERR0    (*(volatile unsigned *)(NANDF_BASE+0x2C))          //NAND Flash ECC Error Status for I/O [7:0]
#define rNFECCERR1    (*(volatile unsigned *)(NANDF_BASE+0x30))          //NAND Flash ECC Error Status for I/O [15:8]
#define rNFMECC0    (*(volatile unsigned *)(NANDF_BASE+0x34))          //SLC or MLC NAND Flash ECC status
#define rNFMECC1    (*(volatile unsigned *)(NANDF_BASE+0x38))            //SLC or MLC NAND Flash ECC status
#define rNFSECC         (*(volatile unsigned *)(NANDF_BASE+0x3C))          //NAND Flash ECC for I/O[15:0]
#define rNFMLCBITPT    (*(volatile unsigned *)(NANDF_BASE+0x40))         //NAND Flash 4-bit ECC Error Pattern for data[7:0]

// UART
#define UART0_BASE    (0x7F005000)
#define rULCON0        (*(volatile unsigned *)(UART0_BASE+0x00))
#define rUCON0        (*(volatile unsigned *)(UART0_BASE+0x04))
#define rUFCON0        (*(volatile unsigned *)(UART0_BASE+0x08))
#define rUMCON0        (*(volatile unsigned *)(UART0_BASE+0x0C))
#define rUTRSTAT0     (*(volatile unsigned *)(UART0_BASE+0x10))
#define rUERSTAT0     (*(volatile unsigned *)(UART0_BASE+0x14))
#define rUFSTAT0    (*(volatile unsigned *)(UART0_BASE+0x18))
#define rUMSTAT0    (*(volatile unsigned *)(UART0_BASE+0x1C))
#define rUTXH0        (*(volatile unsigned *)(UART0_BASE+0x20))
#define rURXH0        (*(volatile unsigned *)(UART0_BASE+0x24))
#define rUBRDIV0        (*(volatile unsigned *)(UART0_BASE+0x28))
#define rUDIVSLOT0     (*(volatile unsigned *)(UART0_BASE+0x2C))
#define rUINTP0        (*(volatile unsigned *)(UART0_BASE+0x30))
#define rUINTSP0        (*(volatile unsigned *)(UART0_BASE+0x34))
#define rUINTM0        (*(volatile unsigned *)(UART0_BASE+0x38))

#define UART1_BASE    (0x7F005400)
#define rULCON1        (*(volatile unsigned *)(UART1_BASE+0x00))
#define rUCON1        (*(volatile unsigned *)(UART1_BASE+0x04))
#define rUFCON1        (*(volatile unsigned *)(UART1_BASE+0x08))
#define rUMCON1        (*(volatile unsigned *)(UART1_BASE+0x0C))
#define rUTRSTAT1     (*(volatile unsigned *)(UART1_BASE+0x10))
#define rUERSTAT1     (*(volatile unsigned *)(UART1_BASE+0x14))
#define rUFSTAT1    (*(volatile unsigned *)(UART1_BASE+0x18))
#define rUMSTAT1    (*(volatile unsigned *)(UART1_BASE+0x1C))
#define rUTXH1        (*(volatile unsigned *)(UART1_BASE+0x20))
#define rURXH1        (*(volatile unsigned *)(UART1_BASE+0x24))
#define rUBRDIV1        (*(volatile unsigned *)(UART1_BASE+0x28))
#define rUDIVSLOT1     (*(volatile unsigned *)(UART1_BASE+0x2C))
#define rUINTP1        (*(volatile unsigned *)(UART1_BASE+0x2C))
#define rUINTSP1        (*(volatile unsigned *)(UART1_BASE+0x34))
#define rUINTM1        (*(volatile unsigned *)(UART1_BASE+0x38))

#define UART2_BASE    (0x7F005800)
#define rULCON2        (*(volatile unsigned *)(UART2_BASE+0x00))
#define rUCON2        (*(volatile unsigned *)(UART2_BASE+0x04))
#define rUFCON2        (*(volatile unsigned *)(UART2_BASE+0x08))
#define rUMCON2        (*(volatile unsigned *)(UART2_BASE+0x0C))
#define rUTRSTAT2     (*(volatile unsigned *)(UART2_BASE+0x10))
#define rUERSTAT2     (*(volatile unsigned *)(UART2_BASE+0x14))
#define rUFSTAT2    (*(volatile unsigned *)(UART2_BASE+0x18))
#define rUMSTAT2    (*(volatile unsigned *)(UART2_BASE+0x1C))
#define rUTXH2        (*(volatile unsigned *)(UART2_BASE+0x20))
#define rURXH2        (*(volatile unsigned *)(UART2_BASE+0x24))
#define rUBRDIV2        (*(volatile unsigned *)(UART2_BASE+0x28))
#define rUDIVSLOT2     (*(volatile unsigned *)(UART2_BASE+0x2C))
#define rUINTP2        (*(volatile unsigned *)(UART2_BASE+0x30))
#define rUINTSP2        (*(volatile unsigned *)(UART2_BASE+0x34))
#define rUINTM2        (*(volatile unsigned *)(UART2_BASE+0x38))



void Uart_Init(void);
void Uart_SendByte(int data);
void Uart_SendString(char *pt);
void Uart_SendDWORD(unsigned int d, int cr);
char *hex2char(unsigned int val);

#define WrUTXH0(ch)     (*(volatile unsigned char *)(UART0_BASE+0x20))=(unsigned char)(ch)
#define RdURXH0()       (*(volatile unsigned char *)(UART0_BASE+0x24))
#define WrUTXH1(ch)     (*(volatile unsigned char *)(UART1_BASE+0x20))=(unsigned char)(ch)
#define RdURXH1()       (*(volatile unsigned char *)(UART1_BASE+0x24))
#define WrUTXH2(ch)     (*(volatile unsigned char *)(UART2_BASE+0x20))=(unsigned char)(ch)
#define RdURXH2()       (*(volatile unsigned char *)(UART2_BASE+0x24))

#ifdef __cplusplus
}
#endif
#endif  //__S3C6410ADDR_H__

