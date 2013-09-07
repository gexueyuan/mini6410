;-------------------------------------------------------------------------------
;
;  Header: mem.inc
;
;-------------------------------------------------------------------------------

; Include the system definitions


    GBLL    USE_DMC0
    GBLL    USE_DMC0_CHIP0
    GBLL    USE_DMC0_CHIP1
    GBLL    USE_DMC1
    GBLL    USE_DMC1_CHIP0
    GBLL    USE_DMC1_CHIP1

;-------------------------------------------------------------------------------
; DDR Timing Parameter
;-------------------------------------------------------------------------------
DDR_tREFRESH  	EQU    7800  ; ns  7800

DDR_tRAS        EQU    45    ; ns (min: 45ns)
DDR_tRC     	EQU    68    ; ns (min: 67.5ns)
DDR_tRCD        EQU    23    ; ns (min: 22.5ns)
DDR_tRFC        EQU    80    ; ns (min: 80ns)
DDR_tRP       	EQU    23    ; ns (min: 22.5ns)
DDR_tRRD        EQU    15    ; ns (min: 15ns)
DDR_tWR       	EQU    15    ; ns (min: 15ns)
DDR_tXSR        EQU    120   ; ns (min: 120ns)

DDR_CASL        EQU    3     ; CAS Latency 3

;-------------------------------------------------------------------------------
; Definitions for memory configuration
;-------------------------------------------------------------------------------
USE_DMC0        SETL    {FALSE}
USE_DMC0_CHIP0 	SETL    {FALSE}
USE_DMC0_CHIP1 	SETL    {FALSE}
USE_DMC1        SETL    {TRUE}
USE_DMC1_CHIP0 	SETL    {TRUE}
USE_DMC1_CHIP1 	SETL    {FALSE}

;=================
; DMC
;=================
DMC0_BASE            EQU    0x7e000000
DMC1_BASE            EQU    0x7e001000

INDEX_MEMSTAT            EQU    0x0
INDEX_MEMCCMD            EQU    0x4
INDEX_DIRECTCMD            EQU    0x8
INDEX_MEMCFG            EQU    0xc
INDEX_REFRESH            EQU    0x10
INDEX_CASLAT            EQU    0x14
INDEX_T_DQSS            EQU    0x18
INDEX_T_MRD            EQU    0x1c
INDEX_T_RAS            EQU    0x20
INDEX_T_RC            EQU    0x24
INDEX_T_RCD            EQU    0x28
INDEX_T_RFC            EQU    0x2c
INDEX_T_RP            EQU    0x30
INDEX_T_RRD            EQU    0x34
INDEX_T_WR            EQU    0x38
INDEX_T_WTR            EQU    0x3c
INDEX_T_XP            EQU    0x40
INDEX_T_XSR            EQU    0x44
INDEX_T_ESR            EQU    0x48
INDEX_MEMCFG2            EQU    0x4c
INDEX_ID_0_CFG            EQU    0x100
INDEX_ID_1_CFG            EQU    0x104
INDEX_ID_2_CFG            EQU    0x108
INDEX_ID_3_CFG            EQU    0x10c
INDEX_ID_4_CFG            EQU    0x110
INDEX_ID_5_CFG            EQU    0x114
INDEX_ID_6_CFG            EQU    0x118
INDEX_ID_7_CFG            EQU    0x11c
INDEX_ID_8_CFG            EQU    0x120
INDEX_ID_9_CFG            EQU    0x124
INDEX_ID_10_CFG            EQU    0x128
INDEX_ID_11_CFG            EQU    0x12c
INDEX_ID_12_CFG            EQU    0x130
INDEX_ID_13_CFG            EQU    0x134
INDEX_ID_14_CFG            EQU    0x138
INDEX_ID_15_CFG            EQU    0x13c
INDEX_CHIP0_CFG            EQU    0x200
INDEX_CHIP1_CFG            EQU    0x204
INDEX_USER_STAT            EQU    0x300
INDEX_USER_CFG            EQU    0x304

;-------------------------------------------------------------------------------
; Memory Chip direct command
;-------------------------------------------------------------------------------
DMC_NOP0        EQU    0x0c0000
DMC_NOP1        EQU     0x1c0000
DMC_PA0            EQU    0x000000    ; Precharge all
DMC_PA1            EQU     0x100000
DMC_AR0            EQU     0x040000    ; Autorefresh
DMC_AR1            EQU     0x140000
DMC_SDR_MR0        EQU    0x080032    ; MRS, CAS 3, Burst Length 4
DMC_SDR_MR1        EQU    0x180032
DMC_DDR_MR0        EQU     0x080162
DMC_DDR_MR1        EQU     0x180162
DMC_mDDR_MR0        EQU    0x080032    ; CAS 3, Burst Length 4
DMC_mDDR_MR1        EQU     0x180032
DMC_mSDR_EMR0        EQU     0x0a0000    ; EMRS, DS:Full, PASR:Full Array
DMC_mSDR_EMR1        EQU     0x1a0000
DMC_DDR_EMR0        EQU     0x090000
DMC_DDR_EMR1        EQU     0x190000
DMC_mDDR_EMR0        EQU     0x0a0000    ; DS:Full, PASR:Full Array
DMC_mDDR_EMR1        EQU     0x1a0000


;-------------------------------------------------------------------------------
; Memory Configuration Register
; CKE_Ctrl[31], Active_Chip[22:21], Qos_master[20:18], Burst[17:15], Stop_mem_clock[14]
; Auto_power_down[13], Pwr_down_prd[12:7], AP bit[6], Row bit[5:3], Column bit[2:0]
; CKE_Ctrl : 1'b0(One CKE Ctrl), 1'b1(Individual CKE Ctrl)
; Active Chip : 2'b00 (1chip), 2'b01(2chips)
; Memory Burst: 3'b000 (Burst1), 3'b001(Burst2), 3'b010(Burst4), 3'b011(Burst8), 3'b100(Burst16)

; 31th register in P1MEMCFG shoud be set as '0' to support one cke control
DMC1_MEM_CFG        EQU    ((1<<30)+(0<<21)+(0<<18)+(2<<15)+(0<<14)+(0<<13)+(0<<7)+(0<<6)+(2<<3)+(2<<0))    ; colum A0~A9
;DMC1_MEM_CFG        EQU    0x80010012

;-------------------------------------------------------------------------------
; Memory Configuration 2 Register
; Read Delay[12:11], Memory Type[10:8], Memory Width[7:6], Bank bits[5:4], DQM init[2], Clock[1:0]
; Read Delay : 2'b00 (SDRAM), 2'b01 (DDR,mDDR), 2'b10 = Read Delay 2 cycle
; Memory Type: 3'b000(SDRAM), 3'b001(DDR), 3'b011(mDDR), 3'b010(Embedded DRAM)
; Memory Width : 2'b00 (16bit), 2'b01(32bit)
; DQM init : DQM state at reset
; Clock Config: AXI and Memory Clock are sync.
DMC1_MEM_CFG2        EQU    ((1<<11)+(3<<8)+(1<<6)+(0<<4)+(0<<2)+(1<<0))
;DMC1_MEM_CFG2        EQU    0xB41

;-------------------------------------------------------------------------------
; CHIP Configuration Register
; BRC_RBC[16], Addr_match[15:8], Addr_Mask[7:0]
; BRC_RBC: 1'b0 (Row-Bank-Column), 1'b1 (Bank-Row-Column)
; Addr_match: AXI_addr[31:24], Ex) 0x5000_0000,  Set 0x50
; Addr_Mask : AXI_addr[31:24], Ex) 0x57ff_ffff,  Set 0xF8
DMC1_CHIP0_CFG        EQU    ((1<<16)+(0x50<<8)+(0xF8<<0))    ; BRC (Linear Address Mapping)
;DMC1_CHIP0_CFG        EQU    ((0<<16)+(0x50<<8)+(0xF8<<0))    ; RBC (4K Unit Permute)
;DMC1_CHIP0_CFG        EQU    0x150F8

; User Configuration Register
; DQS3[7:6], DQS2[5:4], DQS1[3:2], DQS0[1:0]
DMC1_USER_CFG        EQU    0x0

;-------------------------------------------------------------------------------
; Memory Configurations for DMC
; (HCLK: DMC Clock)
;-------------------------------------------------------------------------------

;---------------------------
; mDDR Memory Configuration
;---------------------------
    [ {TRUE}
DMC_DDR_BA_EMRS        EQU    (2)
DMC_DDR_MEM_CASLAT    EQU    (3)
DMC_DDR_CAS_LATENCY    EQU    (DDR_CASL<<1)                        ; 6   Set Cas Latency to 3
DMC_DDR_t_DQSS        EQU    (1)                            ; Min 0.75 ~ 1.25
DMC_DDR_t_MRD        EQU    (2)                            ; Min 2 tck
DMC_DDR_t_RAS        EQU    (((HCLK/1000*DDR_tRAS)+500000)/1000000+1)    ; 7, Min 45ns
DMC_DDR_t_RC        EQU    (((HCLK/1000*DDR_tRC)+500000)/1000000+1)    ; 10, Min 67.5ns
DMC_DDR_t_RCD        EQU    (((HCLK/1000*DDR_tRCD)+500000)/1000000+1)    ; 4,5(TRM), Min 22.5ns
DMC_DDR_schedule_RCD    EQU    ((DMC_DDR_t_RCD -3) <<3);
DMC_DDR_t_RFC        EQU    (((HCLK/1000*DDR_tRFC)+500000)/1000000+1)    ; 11,18(TRM) Min 80ns
DMC_DDR_schedule_RFC    EQU    ((DMC_DDR_t_RFC -3) <<5);
DMC_DDR_t_RP        EQU    (((HCLK/1000*DDR_tRP)+500000)/1000000+1)    ; 4, 5(TRM) Min 22.5ns
DMC_DDR_schedule_RP    EQU    ((DMC_DDR_t_RP -3) <<3);
DMC_DDR_t_RRD        EQU    (((HCLK/1000*DDR_tRRD)+500000)/1000000+1)    ; 3, Min 15ns
DMC_DDR_t_WR        EQU    (((HCLK/1000*DDR_tWR)+500000)/1000000+1)    ; Min 15ns
DMC_DDR_t_WTR        EQU    (2)
DMC_DDR_t_XP        EQU    (2)                            ; 1tck + tIS(1.5ns)
DMC_DDR_t_XSR        EQU    (((HCLK/1000*DDR_tXSR)+500000)/1000000+1)    ; 17, Min 120ns
DMC_DDR_t_ESR        EQU    (DMC_DDR_t_XSR)
DMC_DDR_REFRESH_PRD    EQU    (((HCLK/1000*DDR_tREFRESH)+500000)/1000000)    ; TRM 2656
DMC_DDR_REFRESH_PRD_DVS    EQU    (DMC_DDR_REFRESH_PRD/2)                    ; HCLK can be divided by 2
	|
	[ {TRUE} ;HCLK=133MHZ
DMC_DDR_REFRESH_PRD			EQU    (0x40D)    ; TRM 2656
DMC_DDR_REFRESH_PRD_DVS		EQU    (0x40D)                    ; HCLK can be divided by 2

DMC_DDR_CAS_LATENCY		EQU		(0x6)   ; 6   Set Cas Latency to 3
DMC_DDR_t_DQSS			EQU		(0x1)   ; Min 0.75 ~ 1.25
DMC_DDR_t_MRD			EQU		(0x2)   ; Min 2 tck
DMC_DDR_t_RAS			EQU     (0x6)   ; 7, Min 45ns
DMC_DDR_t_RC			EQU		(0xA)   ; 11 Changed		; 10, Min 67.5ns
DMC_DDR_t_RCD			EQU		(0xC)	; 4,5(TRM), Min 22.5ns
DMC_DDR_t_RFC			EQU	    (0x10B)	;
DMC_DDR_t_RP			EQU		(0xC)    ; 4, 5(TRM) Min 22.5ns
DMC_DDR_t_RRD			EQU		(0x2)    ; 3, Min 15ns
DMC_DDR_t_WR			EQU		(0x2)    ; Min 15ns
DMC_DDR_t_WTR			EQU    (0x2)
DMC_DDR_t_XP			EQU    (0x2)                            ; 1tck + tIS(1.5ns)
DMC_DDR_t_XSR			EQU    (0x10)    ;18	; 17, Min 120ns
DMC_DDR_t_ESR			EQU    (DMC_DDR_t_XSR)
	]
	[ {FALSE} ;HCLK=150MHZ
DMC_DDR_REFRESH_PRD			EQU    (0x491)    ; TRM 2656
DMC_DDR_REFRESH_PRD_DVS		EQU    (0x491)                    ; HCLK can be divided by 2

DMC_DDR_CAS_LATENCY		EQU		(0x6)   ; 6   Set Cas Latency to 3
DMC_DDR_t_DQSS			EQU		(0x1)   ; Min 0.75 ~ 1.25
DMC_DDR_t_MRD			EQU		(0x2)   ; Min 2 tck
DMC_DDR_t_RAS			EQU     (0x7)   ; 7, Min 45ns
DMC_DDR_t_RC			EQU		(0xB)   ; 11 Changed		; 10, Min 67.5ns
DMC_DDR_t_RCD			EQU		(0xC)	; 4,5(TRM), Min 22.5ns
DMC_DDR_t_RFC			EQU	    (0x12C)	;
DMC_DDR_t_RP			EQU		(0xC)    ; 4, 5(TRM) Min 22.5ns
DMC_DDR_t_RRD			EQU		(0x3)    ; 3, Min 15ns
DMC_DDR_t_WR			EQU		(0x3)    ; Min 15ns
DMC_DDR_t_WTR			EQU    (0x2)
DMC_DDR_t_XP			EQU    (0x2)                            ; 1tck + tIS(1.5ns)
DMC_DDR_t_XSR			EQU    (0x12)    ;18	; 17, Min 120ns
DMC_DDR_t_ESR			EQU    (DMC_DDR_t_XSR)
    ]
    ]

    END

