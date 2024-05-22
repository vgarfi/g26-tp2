GLOBAL writeScreen
GLOBAL readScreen
GLOBAL sleep

section .text

readScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToRead
    mov rax, 0
    int 80h
    ret

writeScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToPrint
    mov rax, 1
    int 80h
    ret

sleep:
    mov rax, 162
    int 80h
    ret