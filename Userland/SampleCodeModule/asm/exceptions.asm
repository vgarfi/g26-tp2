GLOBAL divZero
GLOBAL invalidOpcode

section .text

divZero:
    mov rdi, 0
    div rdi
    ret

invalidOpcode:
    db 0x0F, 0x00
    ret