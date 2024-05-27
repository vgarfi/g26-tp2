GLOBAL outb
GLOBAL inb

section .text
inb:
    push rbp
    mov rbp, rsp

    mov rdx, rdi
    mov rax, 0
    in al, dx

    mov rsp, rbp
    pop rbp
    ret

outb:
    push rbp
    mov rbp, rsp

    mov rax, rsi
    mov rdx, rdi
    out dx, al
    
    mov rsp, rbp
    pop rbp
    ret