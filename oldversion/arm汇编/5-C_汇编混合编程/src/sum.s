		AREA	stack,CODE,READONLY	; ���������start
		CODE32						; ����32λARMָ��
		
		EXPORT	asmSum
asmSum
		ADD R0,R0,R1		;R0�������ݷ���ֵ
		MOV	PC,LR    
		
		END