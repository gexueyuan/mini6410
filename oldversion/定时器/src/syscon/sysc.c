/**************************************************************************************
* 
*	Project Name : S3C6410 Validation
*
*	Copyright 2006 by Samsung Electronics, Inc.
*	All rights reserved.
*
*	Project Description :
*		This software is only for validating functions of the S3C6410.
*		Anybody can use this software without our permission.
*  
*--------------------------------------------------------------------------------------
* 
*	File Name : sysc.c
*  
*	File Description : This file implements the API functons for system controller.
*
*	Author : Haksoo,Kim
*	Dept. : AP Development Team
*	Created Date : 2006/11/08
*	Version : 0.1 
* 
*	History
*	- Created(Haksoo,Kim 2006/11/08)
*	- Added sfr (Wonjoon.Jang 2007/01/08)
*  
**************************************************************************************/

#include "library.h"
#include "sfr6410.h"
#include "system.h"
#include "option.h"

#include "gpio.h"
#include "sysc.h"
#include "intc.h"

#define dprintf	UART_Printf
//#define dprintf


//
#define rAPLL_LOCK			(SYSCON_BASE+0x000)
#define rMPLL_LOCK			(SYSCON_BASE+0x004)
#define rEPLL_LOCK			(SYSCON_BASE+0x008)
#define rAPLL_CON			(SYSCON_BASE+0x00c)
#define rMPLL_CON			(SYSCON_BASE+0x010)
#define rEPLL_CON0			(SYSCON_BASE+0x014)
#define rEPLL_CON1			(SYSCON_BASE+0x018)
#define rCLK_SRC				(SYSCON_BASE+0x01c)
#define rCLK_SRC2			(SYSCON_BASE+0x10c)
#define rCLK_DIV0			(SYSCON_BASE+0x020)
#define rCLK_DIV1			(SYSCON_BASE+0x024)
#define rCLK_DIV2			(SYSCON_BASE+0x028)
#define rCLK_OUT				(SYSCON_BASE+0x02c)
#define rHCLK_GATE			(SYSCON_BASE+0x030)
#define rPCLK_GATE			(SYSCON_BASE+0x034)
#define rSCLK_GATE			(SYSCON_BASE+0x038)
#define rMEM0_CLK_GATE		(SYSCON_BASE+0x03c)

//
#define rAHB_CON0			(SYSCON_BASE+0x100)
#define rAHB_CON1			(SYSCON_BASE+0x104)
#define rAHB_CON2			(SYSCON_BASE+0x108)
#define rSDMA_SEL			(SYSCON_BASE+0x110)
#define rSW_RST				(SYSCON_BASE+0x114)
#define rSYS_ID				(SYSCON_BASE+0x118)
#define rMEM_SYS_CFG		(SYSCON_BASE+0x120)
#define rQOS_OVERRIDE0		(SYSCON_BASE+0x124)
#define rQOS_OVERRIDE1		(SYSCON_BASE+0x128)
#define rMEM_CFG_STAT		(SYSCON_BASE+0x12c)
//
#define rPWR_CFG			(SYSCON_BASE+0x804)
#define rEINT_MASK			(SYSCON_BASE+0x808)
#define rNORMAL_CFG			(SYSCON_BASE+0x810)
#define rSTOP_CFG			(SYSCON_BASE+0x814)
#define rSLEEP_CFG			(SYSCON_BASE+0x818)
#define rSTOP_MEM_CFG		(SYSCON_BASE+0x81C)
#define rOSC_FREQ			(SYSCON_BASE+0x820)
#define rOSC_STABLE			(SYSCON_BASE+0x824)
#define rPWR_STABLE			(SYSCON_BASE+0x828)
#define rFPC_STABLE			(SYSCON_BASE+0x82c)
#define rMTC_STABLE			(SYSCON_BASE+0x830)
#define rBUS_CACHEABLE_CON	(SYSCON_BASE+0x838)

// 
#define rOTHERS				(SYSCON_BASE+0x900)
#define rRST_STAT			(SYSCON_BASE+0x904)
#define rWAKEUP_STAT		(SYSCON_BASE+0x908)
#define rBLK_PWR_STAT		(SYSCON_BASE+0x90c)
#define rINFORM0			(SYSCON_BASE+0xA00)
#define rINFORM1			(SYSCON_BASE+0xA04)
#define rINFORM2			(SYSCON_BASE+0xA08)
#define rINFORM3			(SYSCON_BASE+0xA0c)
#define rINFORM4			(SYSCON_BASE+0xA10)
#define rINFORM5			(SYSCON_BASE+0xA14)
#define rINFORM6			(SYSCON_BASE+0xA18)
#define rINFORM7			(SYSCON_BASE+0xA1c)


u8	g_System_Revision, g_System_Pass, g_SYNCACK;
u32	g_APLL, g_MPLL, g_ARMCLK, g_HCLKx2, g_HCLK, g_PCLK;

//////////
// Function Name : SYSC_GetClkInform
// Function Description : This function gets common clock information
// Input : NONE 
// Output : NONE
// Version : 
void SYSC_GetClkInform( void)
{
	u8 muxApll, muxMpll, muxSync;
	u8 divApll, divHclkx2, divHclk, divPclk;
	u16 pllM, pllP, pllS;
	u32 temp;
	
	////
	// clock division ratio	
	temp = Inp32(rCLK_DIV0);
	divApll = temp & 0xf;
	divHclkx2 = (temp>>9) & 0x7;
	divHclk = (temp>>8) & 0x1;
	divPclk = (temp>>12) & 0xf;

	////
	// Operating Mode
	temp = Inp32(rOTHERS);
	temp = (temp>>8)&0xf;
	if(temp)
	{
		g_SYNCACK = 1;
	}
	else
	{
		g_SYNCACK = 0;
	}
	
	////
	// ARMCLK
	muxApll = Inp32(rCLK_SRC) & 0x1;
	if(muxApll)	//FOUT
	{			
		temp = Inp32(rAPLL_CON);
		pllM = (temp>>16)&0x3ff;
		pllP = (temp>>8)&0x3f;
		pllS = (temp&0x7);

		g_APLL = ((FIN>>pllS)/pllP)*pllM;
	}
	else	//FIN
	{
		g_APLL = FIN;
	}
	
	g_ARMCLK = g_APLL/(divApll+1);
	
	////
	// HCLK
	muxSync = (Inp32(rOTHERS)>>7) & 0x1;
	if(muxSync)	//synchronous mode
	{
		g_HCLKx2 = g_APLL/(divHclkx2+1);
		
		temp = Inp32(rMPLL_CON);
		pllM = (temp>>16)&0x3ff;
		pllP = (temp>>8)&0x3f;
		pllS = (temp&0x7);

		g_MPLL = ((FIN>>pllS)/pllP)*pllM;
	}
	else
	{
		muxMpll = (Inp32(rCLK_SRC)>>1) & 0x1;
		if(muxMpll)	//FOUT
		{						
			temp = Inp32(rMPLL_CON);
			pllM = (temp>>16)&0x3ff;
			pllP = (temp>>8)&0x3f;
			pllS = (temp&0x7);

			g_MPLL = ((FIN>>pllS)/pllP)*pllM;
		}
		else	//FIN
		{
			g_MPLL = FIN;
		}
		g_HCLKx2 = g_MPLL/(divHclkx2+1);		
	}
	
	g_HCLK = g_HCLKx2/(divHclk+1);
	
	////
	// PCLK
	g_PCLK = g_HCLKx2/(divPclk+1);

	return;
	
}





