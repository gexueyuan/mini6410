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
*	File Name : timer.c
*  
*	File Description : This file implements the API functons for Timer (PWM, WDT).
*
*	Author : Woojin.Kim
*	Dept. : AP Development Team
*	Created Date : 2006/12/27
*	Version : 0.1 
* 
*	History
*	- Created(Woojin.Kim 2006/12/27)
*  
**************************************************************************************/

#include "def.h"
#include "sfr6410.h"

#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "def.h"
#include "sfr6410.h"


enum TIMER_REG
{
	rTCFG0   = PWMTIMER_BASE+0x00,
	rTCFG1   = PWMTIMER_BASE+0x04,
	rTCON    = PWMTIMER_BASE+0x08,
	rTCNTB0  = PWMTIMER_BASE+0x0C,
	rTCMPB0  = PWMTIMER_BASE+0x10,
	rTCNTO0  = PWMTIMER_BASE+0x14,
	rTCNTB1  = PWMTIMER_BASE+0x18,
	rTCMPB1  = PWMTIMER_BASE+0x1C,
	rTCNTO1  = PWMTIMER_BASE+0x20,
	rTCNTB2  = PWMTIMER_BASE+0x24,
	rTCMPB2  = PWMTIMER_BASE+0x28,
	rTCNTO2  = PWMTIMER_BASE+0x2C,
	rTCNTB3  = PWMTIMER_BASE+0x30,
	rTCMPB3  = PWMTIMER_BASE+0x34,
	rTCNTO3  = PWMTIMER_BASE+0x38,
	rTCNTB4  = PWMTIMER_BASE+0x3C,
	rTCNTO4  = PWMTIMER_BASE+0x40,
	rTINT_CSTAT = PWMTIMER_BASE+0x44

/*
	rWTCON= WDT_BASE+0x00,
	rWTDAT = WDT_BASE+0x04,
	rWTCNT = WDT_BASE+0x08,
	rWTCLRINT = WDT_BASE+0x0C
*/	
	
};


typedef enum eDelay_measure
{
	micro	=0,
	milli	=1,
}
eDelay_M;

#ifdef __cplusplus
}
#endif


#endif //__TIMER_H__
