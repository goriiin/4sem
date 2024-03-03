section .data        ; сегмент инициализированных переменных
   OutMsg dq "a = ",0
   lenOut equ $-OutMsg

   InputMsgB dq "enter b: ",0
   InputMsgC db "enter c: ",0
   InputMsgD db "enter d: ",0
   lenIn equ 10
   
   OutStr dw 0
   OutStrLen dq 0
   
 
section .bss         ; сегмент неинициализированных переменных
   A resd 2
   B resd 2
   C resd 2
   D resd 2

   InBuf resb 10     ; буфер для вводимой строки
   OutBuf resb 10    ; буфер вывода
   LenIn   equ     $-InBuf 

section .text        ; сегмент кода
        global  _start
        
;    a = b * ( c - d ) - c / ( d - 1 )
;    a = b * ( c - d ) + c / ( 1 - d )
; делаем d отрицательным
; нужно сделать деление  
_start:
   ; Предложение ввести b
   mov rax, 1
   mov rdi, 1
   mov rsi, InputMsgB
   mov rdx, lenIn
   syscall

   ; Чтение b
   mov rax, 0
   mov rdi, 0
   mov rsi, InBuf
   mov rdx, LenIn
   syscall

   ; Перевод B из строки в число
   mov rsi, InBuf
   call StrToInt64
   mov [B], rax

   
   ; Предложение ввести c
   mov rax, 1
   mov rdi, 1
   mov rsi, InputMsgC
   mov rdx, lenIn
   syscall

   ; Чтение c
   mov rax, 0
   mov rdi, 0
   mov rsi, InBuf
   mov rdx, LenIn
   syscall

   ; Перевод C из строки в число
   mov rsi, InBuf
   call StrToInt64
   mov [C], rax

   ; Предложение ввести D
   mov rax, 1
   mov rdi, 1
   mov rsi, InputMsgD
   mov rdx, lenIn
   syscall

   ; Чтение D
   mov rax, 0
   mov rdi, 0
   mov rsi, InBuf
   mov rdx, LenIn
   syscall
 
   ; Перевод D из строки в число
   mov rsi, InBuf
   call StrToInt64
   mov [D], rax

   ;a = b * ( c - d ) + c / ( 1 - d )

   mov rax, [C]
   sub rax, [D]; -D + C

   mov rbx, [B] 
   imul rbx ; B * (-D + C)
   mov [A], rax ; переносим результат в А

   mov rax, 1
   sub rax, [D]
   mov [D], rax

   mov rax, [C]
   mov rbx, [D]

   ; выполнить деление (знаковое)
   ; результат будет в rax (частное) и rdx (остаток)
   idiv rbx 
   add rax, [A]

   mov [OutBuf], rax
   mov rsi, OutBuf
   call  IntToStr64

   mov   [OutStrLen],  rax
   mov [OutStr], rsi 

   mov     rax, 1        ; системная функция 1 (write)
   mov     rdi, 1        ; дескриптор файла stdout=1
   mov     rsi, OutMsg ; адрес выводимой строки
   mov     rdx, lenOut  ; длина строки
   syscall               ; вызов системной функции

   mov     rax, 0
   mov     rax, 1        ; системная функция 1 (write)
   mov     rdi, 1        ; дескриптор файла stdout=1
   mov     rsi, [OutStr] ; адрес выводимой строки
   mov     rdx, OutStrLen  ; длина строки
   syscall               ; вызов системной функции

   mov     rax, 60       ; системная функция 60 (exit)
   xor     rdi, rdi      ; return code 0    
   syscall               ; вызов системной функции

%include "../lib.asm"