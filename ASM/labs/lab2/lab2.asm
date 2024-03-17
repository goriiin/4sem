section .data ; сегмент инициализированных переменных
 
section .bss  ; сегмент неинициализированных переменных
   A resq 1
   B resq 1
   C resq 1
   D resq 1

   OutBuf resq 10 ; буфер вывода
   OutLen resq 1
   
   InBuf resd 10 ; буфер для вводимой строки
   LenIn equ $-InBuf
   

; Функция ввода
section .text
   global input_func
   input_func:
      ; Чтение
      mov rax, 0
      mov rdi, 0
      mov rsi, InBuf
      mov rdx, LenIn
      syscall
      ; Перевод из строки в число
      mov  rsi, InBuf
      call StrToInt64
      cmp rbx, 0     ; проверка кода ошибки
      jne input_func ; при преобразовании обнаружена ошибка

      ret
;Функция вывода
section .text
   global output_func
   output_func:
      mov rsi, OutBuf ; загрузка адреса буфера вывода
      call IntToStr64
      mov  [OutLen], rax

      mov  rax, 1       ; 
      mov  rdi, 1       ; 
      mov  rsi, OutBuf  ; 
      mov  rdx, [OutLen]     ; 
      syscall; 

      ret

section .text ; сегмент кода
   global _start
        
;    a = b * ( c - d ) - c / ( d - 1 )
_start:
   ; Вводим переменные 
   call input_func
   mov  [B], rax

   call input_func
   mov  [C], rax

   call input_func
   mov  [D], rax

   mov rbx, [D]
   dec rbx ; d - 1
   mov rax, [C] 
   idiv rbx ; c / ( d - 1 )
   mov [A], rax

   mov rbx, [C] ; c
   sub rbx, [D] ; c - d
   mov rax, [B] 
   imul rbx ; b * ( c - d )

   sub rax, [A] ; b * ( c - d ) - c / ( d - 1 ) -- ответ
   
   call output_func

   mov  rax, 60      ; 
   xor  rdi, rdi     ; 
   syscall; 

%include "../lib.asm"