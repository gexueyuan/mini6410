;  �����ļ�����ʼ��C��������л�����Ȼ�����C������롣
;�������������ȶ���õ��������������α���
;ARM�Ŀ�ִ��ӳ���ļ���RO��RW��ZI���������
;ROΪ����Σ�RWΪ�ѳ�ʼ����ȫ�ֱ�����ZIΪδ��ʼ����ȫ�ֱ���
      	IMPORT	|Image$$RO$$Limit|  ; RO�ν�����ַ
      	IMPORT	|Image$$RW$$Base|   ; RW����ʼ��ַ
      	IMPORT	|Image$$ZI$$Base|   ; ZI����ʼ��ַ
        IMPORT	|Image$$ZI$$Limit|  ; ZI�ν�����ַ

		IMPORT	Main		; ����C�����е�Main()����
		IMPORT  InitStack	; ������ʼ����ջ����

		AREA	Start,CODE,READONLY	; ���������Start
		ENTRY				; ��ʶ�������
		CODE32				; ����32λARMָ��	

        ; ��ʼ��C��������л���
    	LDR	R0,=|Image$$RO$$Limit|
    	LDR	R1,=|Image$$RW$$Base|	
    	LDR	R3,=|Image$$ZI$$Base|	
			
    	CMP	R0,R1
    	BEQ	LOOP1
LOOP0	
		CMP	R1,R3	  
    	LDRCC   R2,[R0],#4     
    	STRCC   R2,[R1],#4 
    	BCC	LOOP0    	
LOOP1	
		LDR	R1,=|Image$$ZI$$Limit| 
    	MOV	R2,#0
LOOP2	
		CMP	R3,R1
    	STRCC   R2,[R3],#4
    	BCC	LOOP2
    	
    	BL	InitStack
    	
    	BL	Main		; ��ת��C�������Main()����
    	
    	END
