GLOBAL kb_get_key

section .text
kb_get_key:
    cli
    xor rax, rax
    in al, 60h      ; donde deja la tecla que se leyo (lo deja en formato scancode)
    sti
    ret