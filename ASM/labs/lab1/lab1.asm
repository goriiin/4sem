   section .data              ; сегмент инициализированных переменных
   A dd -30
   B dd 21

   ; 2 задание 
   vall db 255
   kue3 dw -128
   v5 db 10h
   beta db 23,23h,0ch
   sdk db "Hello",10
   min dw -32767
   ar dd 12345678h
   valar times 5 db 8


   ;3 задание
   gamma dw 25
   tetta dd -35
   name_en dq "Dmitry"
   name_ru dq "Дмитрий"

   ;4 задание 
   aa dd 37
   bb dd 9472
   

   ExitMsg db "Press Enter to Exit",10  ; выводимое сообщение
   lenExit equ $-ExitMsg

section .bss               ; сегмент неинициализированных переменных
   X resd 1

   alu resw 10
   f1 resb 5
InBuf   resb    10            ; буфер для вводимой строки
lenIn   equ     $-InBuf 
        section .text         ; сегмент кода
        global  _start
_start:
   ; write
   mov rax, [A]; загрузить число А в регистор
   add rax, 5; сложить rax и 5, результат в rax
   sub rax, [B]; вычесть число B, результат в rax
   mov [X], rax; сохранить результат в памяти

   mov     rax, 1        ; системная функция 1 (write)
   mov     rdi, 1        ; дескриптор файла stdout=1
   mov     rsi, ExitMsg  ; адрес выводимой строки
   mov     rdx, lenExit  ; длина строки
   syscall               ; вызов системной функции
   ; read
   mov     rax, 0        ; системная функция 0 (read)
   mov     rdi, 0        ; дескриптор файла stdin=0
   mov     rsi, InBuf    ; адрес вводимой строки
   mov     rdx, lenIn    ; длина строки
   syscall               ; вызов системной функции
   ; exit
   mov     rax, 60       ; системная функция 60 (exit)
   xor     rdi, rdi      ; return code 0    
   syscall               ; вызов системной функции