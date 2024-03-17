section .data              ; сегмент инициализированных переменных 
   f1 dw 65535
   f2 dd 65535

section .bss               ; сегмент неинициализированных переменных

section .text         ; сегмент кода
   global  _start

_start:
   inc word[f1]
   inc dword[f2]
   
   ; exit
   mov     rax, 60       ; системная функция 60 (exit)
   xor     rdi, rdi      ; return code 0    
   syscall               ; вызов системной функции










;    ;3 задание
;    gamma dw 25
;    tetta dd -35
;    name_en dq "Dmitry"
;    name_ru dq "Дмитрий"

;    ;4 задание 
;    aa dd 37
;    bb dd 9472
   
; X resd 1

;    alu resw 10
;    f1 resb 5

;  %import