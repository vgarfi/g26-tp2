GLOBAL saveRegsInBuffer

section .text

saveRegsInBuffer:
    push rax     ; Backup rax
    mov rax, [rsp + 4]  ; Mov rax, rip
    mov [regs], rax
    pop rax      ; retrieve rax

    mov [regs + 8], rax
    mov [regs + 16], rbx
    mov [regs + 24], rcx
    mov [regs + 32], rdx
    mov [regs + 40], rsi
    mov [regs + 48], rdi
    mov [regs + 56], rbp
    mov [regs + 64], rsp
    mov [regs + 72], r8
    mov [regs + 80], r9
    mov [regs + 88], r10
    mov [regs + 96], r11
    mov [regs + 104], r12
    mov [regs + 112], r13
    mov [regs + 120], r14
    mov [regs + 128], r15
    mov rax, regs
    ret

section .data
regs dq 17