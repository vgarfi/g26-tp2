GLOBAL getKey

section .text
getKey:
    cli

    xor rax, rax
    in al, 60h

    sti
    ret