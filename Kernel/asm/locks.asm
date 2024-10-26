section .text

global acquire
global release

acquire:
    mov al, 0
.acquire_retry:
    xchg [rdi], al
    test al, al
    jz .acquire_retry
    ret

release:
    mov byte [rdi], 1
    ret