GLOBAL syswriteScreen
GLOBAL sysreadScreen
GLOBAL sysclearScreen
GLOBAL sysclearKbEntry

GLOBAL sysupArrowValue
GLOBAL sysleftArrowValue
GLOBAL sysdownArrowValue
GLOBAL sysrightArrowValue

GLOBAL sysprintRectangle
GLOBAL sysprintSquare

GLOBAL sysprintRegs
GLOBAL syssleep

GLOBAL sysgetSecs
GLOBAL sysgetMins
GLOBAL sysgetHour
GLOBAL sysgetDay
GLOBAL sysgetMonth
GLOBAL sysgetYear

GLOBAL syseasterEgg
GLOBAL sysbeepSound
GLOBAL syszoomIn
GLOBAL syszoomOut
GLOBAL sysgetZoomLevel
GLOBAL syssetZoomLevel
GLOBAL sysprintCursor
GLOBAL syshideCursor
GLOBAL sysshowCursor
GLOBAL syssetCursorPosition

GLOBAL sysctrlPressed

section .text

sysreadScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToRead
    mov rax, 0
    int 80h
    ret

syswriteScreen:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToPrint, R10: colorHex
    mov r10, rcx
    mov rax, 1
    int 80h
    ret

sysprintRegs:
    mov rax, 2
    int 80h
    ret

syszoomIn:
    mov rax, 3
    int 80h
    ret

syszoomOut:
    mov rax, 4
    int 80h
    ret

sysgetZoomLevel:
    mov rax, 5
    int 80h
    ret

syssetZoomLevel:
    mov rax, 6
    int 80h
    ret

sysupArrowValue:
    mov rax, 7
    int 80h
    ret

sysleftArrowValue:
    mov rax, 8
    int 80h
    ret

sysdownArrowValue:
    mov rax, 9
    int 80h
    ret

sysrightArrowValue:
    mov rax, 10
    int 80h
    ret

sysclearScreen:
    mov rax, 11
    int 80h
    ret

sysprintSquare:
    mov r10, rcx
    mov rax, 12
    int 80h
    ret

sysprintRectangle:
    mov r10, rcx
    mov rax, 13
    int 80h
    ret

syssetCursorPosition:
    mov rax, 14
    int 80h
    ret

sysbeepSound:
    mov rax, 15
    int 80h
    ret

syssleep:
    mov rax, 16
    int 80h
    ret

syshideCursor:
    mov rax, 17
    int 80h
    ret

sysshowCursor:
    mov rax, 18
    int 80h
    ret

sysprintCursor:
    mov rax, 19
    int 80h
    ret

sysgetSecs:
    mov rax, 20
    int 80h
    ret

sysgetMins:
    mov rax, 21
    int 80h
    ret

sysgetHour:
    mov rax, 22
    int 80h
    ret

sysgetDay:
    mov rax, 23
    int 80h
    ret

sysgetMonth:
    mov rax, 24
    int 80h
    ret

sysgetYear:
    mov rax, 25
    int 80h
    ret

syseasterEgg:
    mov rax, 26
    int 80h
    ret

sysctrlPressed:
    mov rax, 27
    int 80h
    ret

sysclearKbEntry:
    mov rax, 28
    int 80h
    ret