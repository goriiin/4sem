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