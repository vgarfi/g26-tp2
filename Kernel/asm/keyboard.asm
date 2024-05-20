GLOBAL getKey

section .text
getKey:
    cli

    xor rax, rax
    in al, 60h      ; donde deja la tecla se leyo (lo deja en dormato scancode)
    
    sti
    ret