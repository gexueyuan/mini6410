		AREA	stack,CODE,READONLY	; 声明代码段start
		CODE32						; 声明32位ARM指令
		
		EXPORT	asmSum
asmSum
		ADD R0,R0,R1		;R0用来传递返回值
		MOV	PC,LR    
		
		END