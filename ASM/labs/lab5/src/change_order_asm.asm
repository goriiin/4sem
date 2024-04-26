section .text
global change_order
extern print_result

change_order:
    ; save registers
    push rbp
    mov rbp, rsp

    ; get arguments
    mov rsi, rdi    ; input string
    mov rdx, rsi    ; size of input string
    mov rcx, rdx    ; num of word to change

    ; count number of words in input string
    xor rax, rax
    mov r8, rsi
.count_words:
    xor rax, rax    ; word counter
    mov r8, rsi    ; input string
    mov al, byte [r8]
    test al, al
    jz .count_words_done
    cmp al, ' '
    je .skip_space
    inc rax        ; increment word counter
.loop:
    mov al, byte [r8]
    test al, al
    jz .count_words_done
    cmp al, ' '
    je .skip_space
    inc r8
    jmp .loop
.skip_space:
    inc r8
    jmp .loop
.count_words_done:

.find_word:
    mov r8, rsi    ; input string
    xor rax, rax    ; word counter
    mov r9, rcx    ; n-th word to find
.find_word_loop:
    cmp rax, r9
    je .found_word
    mov al, byte [r8]
    test al, al
    jz .error
    cmp al, ' '
    je .next_word
    inc r8
    jmp .find_word_loop
.next_word:
    inc rax        ; increment word counter
    inc r8
    jmp .find_word_loop
.found_word:
    ; r8 now points to the n-th word

    ; change order of letters in the word
    mov r9, r8
    xor rax, rax
.change_order:
    mov al, byte [r9]
    test al, al
    jz .done_change_order
    cmp al, ' '
    je .done_change_order
    xchg al, byte [r9 + rax]
    inc rax
    jmp .change_order
.done_change_order:

    ; print result
    mov rdi, r8
    call print_result

    ; restore registers
    mov rsp, rbp
    pop rbp
    ret

.error:
    mov rdi, error_message
    call print_result
    mov rsp, rbp
    pop rbp
    ret

section .data
error_message db 'ERROR', 0