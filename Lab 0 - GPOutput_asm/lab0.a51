ORG 0



LOOP:                  
        MOV    P2,#0H         ; ��X��P2��
        CALL   DELAY100MS    ; �I�s����\��Ƶ{��
        MOV    P2,#0FFH         ; ��X��P2��
        CALL   DELAY100MS    ; �I�s����\��Ƶ{��
        JMP    LOOP

;����\��Ƶ{��
DELAY100MS:
       MOV   R6,#217  ; 1 cycle  
D1:
       MOV   R5, #250 ; 1 cycle * 200
       DJNZ  R5, $    ; 2 cycle * 250 *217 
       DJNZ  R6, D1   ; 2 cycle * 200 
       RET            ; 2 cycle  

END