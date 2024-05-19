GLOBAL getKey

section .text
getKey:
    cli

    xor rax, rax
    in al, 64h      ;leo el teclado

    test al, 0x1    ; comparo con el bit 1 para ver si hay una letra para leer
    je getKey

    ;hay una letra para leer
    in al, 60h      ; donde deja la tecla se leyo (lo deja en dormato scancode)
    
    sti
    ret