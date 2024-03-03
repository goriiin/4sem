section .data              ; сегмент инициализированных переменных
    InputMsgA dq "enter a: ",0
    InputMsgK db "enter k: ",0
    InputMsgR db "enter r: ",0
    lenIn equ 10

    OutStr dw 0
    OutStrLen dq 0

    OutMsg dq "f = ", 0
    lenOut equ $-OutMsg

    k8 dd 8

section .bss            ; сегмент неинициализированных переменных
    InBuf   resb 10     ; буфер для вводимой строки
    LenIn   equ  $-InBuf
    OutBuf resb 10    ; буфер вывода

    a resd 4
    k resd 4
    r resd 4


section .text         ; сегмент кода
    global  _start


; Вычислить 
; if k * a > 5 {
    ;f = (k-5)^2/r
;}else{
    ;f = 8-a
;}

_start:
    ; Предложение ввести A
    mov rax, 1
    mov rdi, 1
    mov rsi, InputMsgA
    mov rdx, lenIn
    syscall

    ; Чтение A
    mov rax, 0
    mov rdi, 0
    mov rsi, InBuf
    mov rdx, LenIn
    syscall

    ; Перевод A из строки в число
    mov rsi, InBuf
    call StrToInt64
    mov [a], rax

    ; Предложение ввести K
    mov rax, 1
    mov rdi, 1
    mov rsi, InputMsgK
    mov rdx, lenIn
    syscall

    ; Чтение K
    mov rax, 0
    mov rdi, 0
    mov rsi, InBuf
    mov rdx, LenIn
    syscall

    ; Перевод K из строки в число
    mov rsi, InBuf
    call StrToInt64
    mov [k], rax

    mov rbx, [a]
    mov rax, [k]
    imul rbx

    cmp rax, 5 ; сраниваем значения регистра RAX и регистра RBX
    js else ; если произошло заимствование
        ; Предложение ввести R
        mov rax, 1
        mov rdi, 1
        mov rsi, InputMsgR
        mov rdx, lenIn
        syscall

        ; Чтение R
        mov rax, 0
        mov rdi, 0
        mov rsi, InBuf
        mov rdx, LenIn
        syscall

        ; Перевод R из строки в число
        mov rsi, InBuf
        call StrToInt64
        mov [r], rax

        mov rax, [k]
        sub rax, 5
        mul rax

        mov rbx, [r]
        idiv rbx 
        jmp exit
    else:
        mov rax, [k8]
        sub rax, [a]

    exit: 
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