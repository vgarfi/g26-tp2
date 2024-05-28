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
GLOBAL printCursor
GLOBAL hideCursor
GLOBAL showCursor
GLOBAL printRegs

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
    mov rax, 16
    int 80h
    ret

clearScreen:
    mov rax, 11
    int 80h
    ret
upArrowValue:
    mov rax, 7
    int 80h
    ret

leftArrowValue:
    mov rax, 8
    int 80h
    ret

downArrowValue:
    mov rax, 9
    int 80h
    ret

rightArrowValue:
    mov rax, 10
    int 80h
    ret
printRectangle:
    mov r10, rcx
    mov rax, 13
    int 80h
    ret

printSquare:
    mov r10, rcx
    mov rax, 12
    int 80h
    ret

setCursorPosition:
    mov rax, 14
    int 80h
    ret

beepSound:
    mov rax, 15
    int 80h
    ret

getTime:
    mov rax, 3
    int 80h
    ret

getDate:
    mov rax, 4
    int 80h
    ret

zoomIn:
    mov rax, 5
    int 80h
    ret

zoomOut:
    mov rax, 6
    int 80h
    ret

hideCursor:
    mov rax,17
    int 80h
    ret

showCursor:
    mov rax,18
    int 80h
    ret

printCursor:
    mov rax,19
    int 80h
    ret
    
printRegs:
    mov rax, 2
    int 80h
    ret