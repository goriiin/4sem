%define MATRIX_SIZE 25
%define ROW_LEN     5

section .data ; сегмент инициализированных переменных
   ind dw 0
   matrix times MATRIX_SIZE dq 0 ; матрица 25 символов 
   InBuf  times 32  db 0         ; буфер для вводимой строки
   LenIn equ $-InBuf

   err_num     db  "Only numbers and spaces can be entered", 10
   err_num_len equ $-err_num

   err_line     db  "Each line should have exactly 5 numbers divided by spaces", 10
   err_line_len equ $-err_line

section .bss ; сегмент неинициализированных переменных
   OutBuf resq 10 ; буфер вывода
   OutLen resq 1

; Функция ввода
section .text
   global input_funcToI
   input_funcToI:
      ; Чтение
      mov  rax, 0
      mov  rdi, 0
      mov  rsi, InBuf
      mov  rdx, LenIn
      syscall
      ; Перевод из строки в число
      mov  rsi, InBuf
      call StrToInt64
      cmp  rbx, 0     ; проверка кода ошибки
      jne  input_func ; при преобразовании обнаружена ошибка

      ret

section .text
   global input_func
   input_func:
      mov rax, 0
      mov rdi, 0
      mov rsi, InBuf
      mov rdx, LenIn
      syscall

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

_start:
   mov rcx, ROW_LEN
   xor rdi, rdi
read_line: 
   push rcx
   push rdi

   call input_func

   pop rdi
   mov rcx, rax
   xor rdx, rdx
   xor r10, r10 ; r10 - индекс числа в строке

process_line:
   cmp byte[InBuf + rdx], 10
   je  process_number

   cmp byte[InBuf + rdx], ' '
   jne next

   mov byte[InBuf + rdx], 10

   cmp r10, rdx
   jne process_number
   jmp next

process_number:
   push rdx

   call StrToInt64
   cmp  rbx, 0
   jne  error_num

   cmp rdi, MATRIX_SIZE
   jge error_line       ; обработка ошибки

   mov [matrix + 8 * rdi], rax ; сохраняем число в матрице
   inc rdi

   pop rdx
   mov r10, rdx
   inc r10
   lea rsi, [InBuf + r10]

next:
   inc  rdx
   loop process_line

   pop rcx

   mov  rax, ROW_LEN
   sub  rax, rcx
   inc  rax
   push rdx
   mov  rdx, ROW_LEN
   mul  rdx
   pop  rdx

   cmp rdi, rax
   jne error_line

   dec rcx
   cmp rcx, 0
   jne read_line


exit:
   ; exit
   mov     rax, 60  ; системная функция 60 (exit)
   xor     rdi, rdi ; return code 0    
   syscall          ; вызов системной функции

error_line:
    mov rax, 1
    mov rdi, 1
    mov rsi, err_line
    mov rdx, err_line_len
    syscall
    jmp exit

error_num:
    mov rax, 1
    mov rdi, 1
    mov rsi, err_num
    mov rdx, err_num_len
    syscall
    jmp exit

%include "../lib.asm"