section .data              ; сегмент инициализированных переменных 
   A1 dw 9472
   B1 dw 37

   A2 dw 2500h
   B2 dw 25h
   
   A3 dw 10010100000000b
   B3 dw 100101b
   
   A4a db 0, 37
   B4a db 37, 0

   A4b db 0, 100101b
   B4b db 100101b, 0

   A4c db 0h, 25h
   B4c db 25h, 0
section .text         ; сегмент кода
   global  _start
_start:
   mov rax, [A1]
   mov rax, [B1]
   mov rax, [A2]
   mov rax, [B2]
   mov rax, [A3]
   mov rax, [B3]
   mov rax, [B4a]
   mov rax, [B4b]
   mov rax, [A4b]
   mov rax, [B4b]
   mov rax, [A4c]
   mov rax, [B4c]
   
   ; exit
   mov     rax, 60       ; системная функция 60 (exit)
   xor     rdi, rdi      ; return code 0    
   syscall               ; вызов системной функции

% 

