//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
//------------------------------------------------------------------------------
//
//  File:  soc_cfg.h
//
//  This file contains system constant specific for S3C6410 board.
//
#ifndef __SOC_CFG_H
#define __SOC_CFG_H

//------------------------------------------------------------------------------
// Define: SYNCMODE 
//
// SYNCMODE used to set cpu operation mode to syncronous mode or asyncronous mode
//------------------------------------------------------------------------------
#define SYNCMODE        (1)

//------------------------------------------------------------------------------
// Define : PRESET_CLOCK
//
// Use Predefined CLOCK SETTING.
//------------------------------------------------------------------------------
#define PRESET_CLOCK    (1)

//------------------------------------------------------------------------------
// CPU Revision (S3C6410 has EVT0, EVT1)
//------------------------------------------------------------------------------
#define EVT0            (36410100)
#define EVT1            (36410101)
#define CPU_REVISION    (EVT1)

//------------------------------------------------------------------------------
// Predefined System Clock setting selection
// Here are samples for clock setting that already tested.
// For S3C410, ARM 533Mhz, SystemBus 133Mhz is recommended.
// This values is only used on Driver written in C
//------------------------------------------------------------------------------

#if PRESET_CLOCK
#define CLK_25MHz        25000000
#define CLK_50MHz        50000000
#define CLK_33_25MHz     33250000
#define CLK_66_5MHz      66500000
#define CLK_96MHz        96000000
#define CLK_100MHz       100000000
#define CLK_133MHz       133000000
#define CLK_1333MHz      133333333
#define CLK_133_2MHz     133200000
#define CLK_150MHz       150000000
#define CLK_200MHz       200000000
#define CLK_233MHz       233000000
#define CLK_266MHz       266000000
#define CLK_266_4MHz     266400000
#define CLK_300MHz       300000000
#define CLK_400MHz       400000000
#define CLK_450MHz       450000000
#define CLK_532MHz       532000000
#define CLK_600MHz       600000000
#define CLK_634MHz       634000000
#define CLK_1332MHz      1332000000
#define CLK_666MHz       666000000
#define CLK_667MHz       667000000
#define CLK_798MHz       798000000
#define CLK_800MHz       800000000
#define CLK_900MHz       900000000

// Change This Definition to choose BSP Clock !!! (and "s3c6410.inc")
//#define TARGET_ARM_CLK    CLK_66_5MHz      //< Sync 66.5:66.5:66.5 HCLKx2=266
//#define TARGET_ARM_CLK    CLK_133MHz      //< Sync 133:133:66.5 HCLKx2=266
//#define TARGET_ARM_CLK    CLK_266MHz      //< Sync 266:133:66.5 HCLKx2=266
//#define TARGET_ARM_CLK    CLK_400MHz      //< Async 400:100:50 HCLKx2=200
//#define TARGET_ARM_CLK    CLK_450MHz      //< Sync 450:150:37.5 HCLKx2=300
#define TARGET_ARM_CLK    CLK_532MHz      //< Sync 532:133:66.5 HCLKx2=266, Async is same
//#define TARGET_ARM_CLK    CLK_600MHz        //< Sync 600:150:75 HCLKx2=300
//#define TARGET_ARM_CLK    CLK_666MHz      //< Sync 666:133.2:66.6 HCLKx2=266.4, Async 666:133:66.5 HCLKx2=266
//#define TARGET_ARM_CLK    CLK_798MHz      //< Sync 798:133:66.5  HCLKx2=266
//#define TARGET_ARM_CLK    CLK_800MHz      //< Sync 800:133.33:33.33 HCLKx2=266.66, ASync 800:133:66.5  HCLKx2=266
//#define TARGET_ARM_CLK    CLK_900MHz      //< Sync 900:150:75, HCLKx2=300

/// MPLL Setting
#if (TARGET_ARM_CLK == CLK_400MHz)
#define MPLL_CLK            (CLK_200MHz)
#else   // 532, 634, 666, 800, 900, 133, 266, 66.5
#define MPLL_CLK            (CLK_266MHz)
#endif
#define MPLL_DIV            2
#define S3C6410_DoutMPLL    (MPLL_CLK/MPLL_DIV)     // 100 Mhz or 133Mhz


#if (TARGET_ARM_CLK == CLK_666MHz && SYNCMODE) || (TARGET_ARM_CLK == CLK_450MHz) || (TARGET_ARM_CLK == CLK_266MHz)
#define APLL_CLK            (TARGET_ARM_CLK*2)
#elif (TARGET_ARM_CLK == CLK_133MHz)
#define APLL_CLK            (TARGET_ARM_CLK*4)
#elif (TARGET_ARM_CLK == CLK_66_5MHz)
#define APLL_CLK            (TARGET_ARM_CLK*8)
#else
#define APLL_CLK            (TARGET_ARM_CLK)
#endif

#if (TARGET_ARM_CLK == CLK_450MHz) || (TARGET_ARM_CLK == CLK_666MHz) || (TARGET_ARM_CLK == CLK_266MHz)
#define APLL_DIV            2
#elif (TARGET_ARM_CLK == CLK_133MHz)
#define APLL_DIV            4
#elif (TARGET_ARM_CLK == CLK_66_5MHz)
#define APLL_DIV            8
#else
#define APLL_DIV            1
#endif
#define HCLK_DIV            2
#if (TARGET_ARM_CLK == CLK_66_5MHz)
#define PCLK_DIV            2
#else
#define PCLK_DIV            4
#endif


/// APLL and A:H:P CLK configuration
#if (SYNCMODE)
    #if (TARGET_ARM_CLK == CLK_666MHz) && (CPU_REVISION == EVT1)
        #define HCLKx2_DIV          5    // sync
    #elif (TARGET_ARM_CLK == CLK_532MHz) || (TARGET_ARM_CLK == CLK_600MHz) || (TARGET_ARM_CLK == CLK_266MHz) || (TARGET_ARM_CLK == CLK_133MHz)
        #define HCLKx2_DIV          2    // sync    
    #elif (TARGET_ARM_CLK == CLK_798MHz) || (TARGET_ARM_CLK == CLK_900MHz) || (TARGET_ARM_CLK == CLK_450MHz) || (TARGET_ARM_CLK == CLK_800MHz)
        #define HCLKx2_DIV          3    // sync        
    #elif (TARGET_ARM_CLK == CLK_66_5MHz)
        #define HCLKx2_DIV          4    // sync
    #endif
#else   // 400Mhz, 532Mhz, 666Mhz
#define HCLKx2_DIV          1    // Async
#endif

#define S3C6410_ACLK        (APLL_CLK/APLL_DIV)           

#if (SYNCMODE)
    #define S3C6410_HCLKx2      (APLL_CLK/HCLKx2_DIV)     
#else
    #define S3C6410_HCLKx2      (MPLL_CLK/HCLKx2_DIV)
#endif
#define S3C6410_HCLK        (S3C6410_HCLKx2/HCLK_DIV)
#define S3C6410_PCLK        (S3C6410_HCLKx2/PCLK_DIV)
#else   // PRESET_CLOCK = FALSE
#define APLLVALUE    (((S3C6410_SYSCON_REG*)(S3C6410_BASE_REG_PA_SYSCON))->APLL_CON)
#define MPLLVALUE    (((S3C6410_SYSCON_REG*)(S3C6410_BASE_REG_PA_SYSCON))->MPLL_CON)
#define CLKDIV      (((S3C6410_SYSCON_REG*)(S3C6410_BASE_REG_PA_SYSCON))->CLKD_IV0)



#endif  // PRESET_CLOCK


//------------------------------------------------------------------------------
// SMDK6410 EPLL Output Frequency
//------------------------------------------------------------------------------
//#define S3C6410_ECLK        (CLK_96MHz)        // 96 MHz         for USB Host, SD/HSMMC..
#define S3C6410_ECLK        (84666667)        // 84,666,667 Hz     for IIS Sampling Rate 44.1 KHz (384fs)
//#define S3C6410_ECLK        (92160000)        // 92,160,000 Hz     for IIS Sampling Rate 48 KHz (384fs)

//------------------------------------------------------------------------------
// System Tick Timer Definition
//------------------------------------------------------------------------------
// For Precision of System timer
// Use timer counter as large as possible. (32-bit Counter)
// Use timer divider as small as possible.
#define SYS_TIMER_PRESCALER     (2)    // PCLK / 2 (Do not use Prescaler as 1)
#define SYS_TIMER_DIVIDER       (1)
#define TICK_PER_SEC            (1000)
#define OEM_COUNT_1MS           (S3C6410_PCLK/SYS_TIMER_PRESCALER/SYS_TIMER_DIVIDER/TICK_PER_SEC-1)
#define RESCHED_PERIOD          (1)

//------------------------------------------------------------------------------
// SMDK6410 Static SYSINTR Definition
//------------------------------------------------------------------------------
#define SYSINTR_OHCI         (SYSINTR_FIRMWARE+1)    // for USB Host
//gao0129
#define SYSINTR_ETH          (SYSINTR_FIRMWARE+19)   // for DM9000A
#endif // __SOC_CFG_H

