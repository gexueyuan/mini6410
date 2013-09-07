		AREA	stack,CODE,READONLY	; ���������start
		CODE32						; ����32λARMָ��
		
;�����ջ�Ĵ�С
USR_STACK_LEGTH     EQU         128
SVC_STACK_LEGTH     EQU         0
FIQ_STACK_LEGTH     EQU         16
IRQ_STACK_LEGTH     EQU         64
ABT_STACK_LEGTH     EQU         0
UND_STACK_LEGTH     EQU         0		
		
		EXPORT	InitStack
InitStack    
        MOV     R0, LR		; R0 <= LR����Ϊ����ģʽ��R0����ͬ��

;���ù���ģʽ��ջ
       	MSR     CPSR_c, #0xd3
       	LDR     SP, StackSvc
;�����ж�ģʽ��ջ
       	MSR     CPSR_c, #0xd2
       	LDR     SP, StackIrq
;���ÿ����ж�ģʽ��ջ
       	MSR     CPSR_c, #0xd1
       	LDR     SP, StackFiq
;������ֹģʽ��ջ
       	MSR     CPSR_c, #0xd7
   		LDR     SP, StackAbt
;����δ����ģʽ��ջ
       	MSR     CPSR_c, #0xdb
       	LDR     SP, StackUnd
;����ϵͳģʽ��ջ
       	MSR     CPSR_c, #0xdf
       	LDR     SP, StackUsr

       	MOV     PC, R0	;��ע�⣺axd��PC��ֵ�Ĳ������������쳣
       	
;��¼����ģʽ��ջ��ջ������Ϊ�ǵݼ���ջ
StackUsr    DCD     UsrStackSpace + (USR_STACK_LEGTH - 1)*4
StackSvc    DCD     SvcStackSpace + (SVC_STACK_LEGTH - 1)*4
StackIrq    DCD     IrqStackSpace + (IRQ_STACK_LEGTH - 1)*4
StackFiq    DCD     FiqStackSpace + (FIQ_STACK_LEGTH - 1)*4
StackAbt    DCD     AbtStackSpace + (ABT_STACK_LEGTH - 1)*4
StackUnd    DCD     UndtStackSpace + (UND_STACK_LEGTH - 1)*4


; �����ջ�ռ� 
        	AREA    MyStacks, DATA, NOINIT, ALIGN=2
UsrStackSpace     	SPACE  	USR_STACK_LEGTH * 4 	; �û���ϵͳ��ģʽ��ջ�ռ�
SvcStackSpace      	SPACE  	SVC_STACK_LEGTH * 4  	; ����ģʽ��ջ�ռ�
IrqStackSpace      	SPACE  	IRQ_STACK_LEGTH * 4  	; �ж�ģʽ��ջ�ռ�
FiqStackSpace      	SPACE  	FIQ_STACK_LEGTH * 4  	; �����ж�ģʽ��ջ�ռ�
AbtStackSpace      	SPACE  	ABT_STACK_LEGTH * 4  	; ��ֹ��ģʽ��ջ�ռ�
UndtStackSpace     	SPACE  	UND_STACK_LEGTH * 4  	; δ����ģʽ��ջ					

			END	
