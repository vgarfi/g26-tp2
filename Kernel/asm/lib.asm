GLOBAL saveRegsInBuffer

section .text

saveRegsInBuffer:
    push rax     ; Backup rax
    mov rax, [rsp + 4]  ; Mov rax, rip
    mov [rdi + 128], rax
    pop rax      ; retrieve rax

    mov [rdi], rax
    mov [rdi + 8], rbx
    mov [rdi + 16], rcx
    mov [rdi + 24], rdx
    mov [rdi + 32], rsi
    mov [rdi + 40], rdi
    mov [rdi + 48], rbp
    mov [rdi + 56], rsp
    mov [rdi + 64], r8
    mov [rdi + 72], r9
    mov [rdi + 80], r10
    mov [rdi + 88], r11
    mov [rdi + 96], r12
    mov [rdi + 104], r13
    mov [rdi + 112], r14
    mov [rdi + 120], r15
    ret