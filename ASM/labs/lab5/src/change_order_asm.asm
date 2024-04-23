section .data
    wordNumber db 1 ; Номер слова для обработки

section .bss
    inputString resb 256
    outputString resb 256
    stack resb 256 ; Стек для временного хранения символов слов

; Обязательно назвать также как назвали в С++
section .text
    global change_order
    extern print_result ; подключаем с++ функцию для вывода

change_order:
    ; Вывод приглашения к вводу
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt1
    mov rdx, 18
    syscall

    ; Чтение строки
    mov rdi, 0
    mov rsi, inputString
    mov rdx, 256
    syscall

    ; Обработка строки
    mov rsi, inputString
    mov rdi, stack
    mov rcx, 256
    mov r8, 1 ; Счетчик слов
    process:
        lodsb
        cmp al, ' '
        jz pushToStack
        cmp al, 0
        jz processStack
        stosb
        jmp process

    pushToStack:
        mov al, [rsi]
        cmp al, ' '
        jz skipPush
        push rax
        skipPush:
        inc rsi
        loop process

    processStack:
        mov rcx, 256
        mov rdi, outputString
        popLoop:
            pop rax
            stosb
        loop popLoop

    ; Проверка номера слова
    cmp r8, wordNumber
    jne error

    ; Вывод обработанного слова
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt2
    mov rdx, 19
    syscall
    mov rdi, outputString
    mov rcx, 256
    print:
        lodsb
        cmp al, 0
        je end
        mov rax, 1
        mov rdi, 1
        mov rdx, 1
        syscall
        jmp print

    error:
        ; Вывод ошибки
        mov rax, 1
        mov rdi, 1
        mov rsi, errorMsg
        mov rdx, 5
        syscall

    end:
        ; Завершение программы
        mov rax, 60
        xor rdi, rdi
        syscall
