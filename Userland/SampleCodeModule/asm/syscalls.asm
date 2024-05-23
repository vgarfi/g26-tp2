GLOBAL writeScreen
GLOBAL readScreen
GLOBAL sleep
GLOBAL clearScreen
GLOBAL printRectangle
GLOBAL setCursorPosition

GLOBAL beepSound

section .text

readScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToRead
    mov rax, 0
    int 80h
    ret

writeScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToPrint, R10: colorHex
    mov r10, rcx
    mov rax, 1
    int 80h
    ret

sleep:
    mov rax, 162
    int 80h
    ret

clearScreen:
    mov rax, 30
    int 80h
    ret
printRectangle:
    mov rax, 31
    int 80h
    ret

setCursorPosition:
    mov rax, 40
    int 80h
    ret

beepSound:
    mov rax, 128
    int 80h
    ret