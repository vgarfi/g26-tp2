GLOBAL writeScreen
GLOBAL readScreen
GLOBAL sleep
GLOBAL clearScreen

GLOBAL upArrowValue
GLOBAL leftArrowValue
GLOBAL downArrowValue
GLOBAL rightArrowValue
GLOBAL printRectangle
GLOBAL printSquare
GLOBAL setCursorPosition
GLOBAL getTime
GLOBAL getDate
GLOBAL beepSound
GLOBAL zoomIn
GLOBAL zoomOut

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
upArrowValue:
    mov rax, 20
    int 80h
    ret

leftArrowValue:
    mov rax, 21
    int 80h
    ret

downArrowValue:
    mov rax, 22
    int 80h
    ret

rightArrowValue:
    mov rax, 23
    int 80h
    ret
printRectangle:
    mov rax, 31
    int 80h
    ret

printSquare:
    mov rax, 32
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

getTime:
    mov rax, 5
    int 80h
    ret

getDate:
    mov rax, 6
    int 80h
    ret

zoomIn:
    mov rax, 7
    int 80h
    ret

zoomOut:
    mov rax, 8
    int 80h
    ret