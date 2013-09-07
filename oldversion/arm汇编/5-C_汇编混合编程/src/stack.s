		AREA	stack,CODE,READONLY	; 声明代码段start
		CODE32						; 声明32位ARM指令
		
;定义堆栈的大小
USR_STACK_LEGTH     EQU         128
SVC_STACK_LEGTH     EQU         0
FIQ_STACK_LEGTH     EQU         16
IRQ_STACK_LEGTH     EQU         64
ABT_STACK_LEGTH     EQU         0
UND_STACK_LEGTH     EQU         0		
		
		EXPORT	InitStack
InitStack    
        MOV     R0, LR		; R0 <= LR，因为各种模式下R0是相同的

;设置管理模式堆栈
       	MSR     CPSR_c, #0xd3
       	LDR     SP, StackSvc
;设置中断模式堆栈
       	MSR     CPSR_c, #0xd2
       	LDR     SP, StackIrq
;设置快速中断模式堆栈
       	MSR     CPSR_c, #0xd1
       	LDR     SP, StackFiq
;设置中止模式堆栈
       	MSR     CPSR_c, #0xd7
   		LDR     SP, StackAbt
;设置未定义模式堆栈
       	MSR     CPSR_c, #0xdb
       	LDR     SP, StackUnd
;设置系统模式堆栈
       	MSR     CPSR_c, #0xdf
       	LDR     SP, StackUsr

       	MOV     PC, R0	;请注意：axd对PC赋值的操作可能引起异常
       	
;记录各个模式堆栈的栈顶，因为是递减堆栈
StackUsr    DCD     UsrStackSpace + (USR_STACK_LEGTH - 1)*4
StackSvc    DCD     SvcStackSpace + (SVC_STACK_LEGTH - 1)*4
StackIrq    DCD     IrqStackSpace + (IRQ_STACK_LEGTH - 1)*4
StackFiq    DCD     FiqStackSpace + (FIQ_STACK_LEGTH - 1)*4
StackAbt    DCD     AbtStackSpace + (ABT_STACK_LEGTH - 1)*4
StackUnd    DCD     UndtStackSpace + (UND_STACK_LEGTH - 1)*4


; 分配堆栈空间 
        	AREA    MyStacks, DATA, NOINIT, ALIGN=2
UsrStackSpace     	SPACE  	USR_STACK_LEGTH * 4 	; 用户（系统）模式堆栈空间
SvcStackSpace      	SPACE  	SVC_STACK_LEGTH * 4  	; 管理模式堆栈空间
IrqStackSpace      	SPACE  	IRQ_STACK_LEGTH * 4  	; 中断模式堆栈空间
FiqStackSpace      	SPACE  	FIQ_STACK_LEGTH * 4  	; 快速中断模式堆栈空间
AbtStackSpace      	SPACE  	ABT_STACK_LEGTH * 4  	; 中止义模式堆栈空间
UndtStackSpace     	SPACE  	UND_STACK_LEGTH * 4  	; 未定义模式堆栈					

			END	
