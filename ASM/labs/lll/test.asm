%define aa -1

section .data ; сегмент инициализированных переменных
   x dd 0x10AD2019
section .bss ; сегмент неинициализированных переменных

   OutBuf resq 10 ; буфер вывода
   OutLen resq 1
   
   InBuf resd 10 ; буфер для вводимой строки
   LenIn equ $-InBuf
   

; Функция ввода
section .text
   global input_func
   input_func:
      ; Чтение
      mov  eax, 0
      mov  edi, 0
      mov  esi, InBuf
      mov  edx, LenIn
      syscall
      ; Перевод из строки в число
      mov  esi, InBuf
      call StrToInt64
      cmp  ebx, 0     ; проверка кода ошибки
      jne  input_func ; при преобразовании обнаружена ошибка

      ret
;Функция вывода
section .text
   global output_func
   output_func:
      mov  rsi,      OutBuf ; загрузка адреса буфера вывода
      call IntToStr64
      mov  [OutLen], rax

      mov rax, 1        ; 
      mov rdi, 1        ; 
      mov rsi, OutBuf   ; 
      mov rdx, [OutLen] ; 
      syscall; 

      ret

section .text ; сегмент кода
   global _start
        
;    a = b * ( c - d ) - c / ( d - 1 )
_start:

   mov eax, dword[x]
ror eax, 12
add eax, 0x4000

   call output_func
exit:
   mov rax, 60  ; 
   xor rdi, rdi ; 
   syscall; 


%include "../lib.asm"

