GLOBAL writeScreen
GLOBAL readScreen
GLOBAL clearScreen

GLOBAL upArrowValue
GLOBAL leftArrowValue
GLOBAL downArrowValue
GLOBAL rightArrowValue

GLOBAL printRectangle
GLOBAL printSquare

GLOBAL printRegs
GLOBAL sleep

GLOBAL getSecs
GLOBAL getMins
GLOBAL getHour
GLOBAL getDay
GLOBAL getMonth
GLOBAL getYear

GLOBAL beepSound
GLOBAL zoomIn
GLOBAL zoomOut

GLOBAL printCursor
GLOBAL hideCursor
GLOBAL showCursor
GLOBAL setCursorPosition

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

printRegs:
    mov rax, 2
    int 80h
    ret

zoomIn:
    mov rax, 3
    int 80h
    ret

zoomOut:
    mov rax, 4
    int 80h
    ret

upArrowValue:
    mov rax, 5
    int 80h
    ret

leftArrowValue:
    mov rax, 6
    int 80h
    ret

downArrowValue:
    mov rax, 7
    int 80h
    ret

rightArrowValue:
    mov rax, 8
    int 80h
    ret

clearScreen:
    mov rax, 9
    int 80h
    ret

printSquare:
    mov r10, rcx
    mov rax, 10
    int 80h
    ret

printRectangle:
    mov r10, rcx
    mov rax, 11
    int 80h
    ret

setCursorPosition:
    mov rax, 12
    int 80h
    ret

beepSound:
    mov rax, 13
    int 80h
    ret

sleep:
    mov rax, 14
    int 80h
    ret

hideCursor:
    mov rax,15
    int 80h
    ret

showCursor:
    mov rax,16
    int 80h
    ret

printCursor:
    mov rax,17
    int 80h
    ret

getSecs:
    mov rax, 18
    int 80h
    ret

getMins:
    mov rax, 19
    int 80h
    ret

getHour:
    mov rax, 20
    int 80h
    ret

getDay:
    mov rax, 21
    int 80h
    ret

getMonth:
    mov rax, 22
    int 80h
    ret

getYear:
    mov rax, 23
    int 80h
    ret