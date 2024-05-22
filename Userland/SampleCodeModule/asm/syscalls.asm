GLOBAL writeScreen
GLOBAL readScreen

section .text

readScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToRead
    mov rax, 0
    int 80h
    ret

writeScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToPrint
    mov rax, 1
    int 80h
    ret
