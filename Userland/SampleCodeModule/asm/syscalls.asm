GLOBAL sysWrite
GLOBAL sysRead
GLOBAL sysReadNoBlock

GLOBAL sysClearScreen
GLOBAL sysClearKbEntry

GLOBAL sysUpArrowValue
GLOBAL sysLeftArrowValue
GLOBAL sysDownArrowValue
GLOBAL sysRightArrowValue

GLOBAL sysPrintRectangle
GLOBAL sysPrintSquare

GLOBAL sysPrintRegs
GLOBAL sysSleep

GLOBAL sysGetSecs
GLOBAL sysGetMins
GLOBAL sysGetHour
GLOBAL sysGetDay
GLOBAL sysGetMonth
GLOBAL sysGetYear

GLOBAL sysBeepSound
GLOBAL sysZoomIn
GLOBAL sysZoomOut
GLOBAL sysGetZoomLevel
GLOBAL sysSetZoomLevel
GLOBAL sysPrintCursor
GLOBAL sysHideCursor
GLOBAL sysShowCursor
GLOBAL sysSetCursorPosition
GLOBAL sysCtrlPressed
GLOBAL sysGetCurrentPid
GLOBAL sysExit
GLOBAL sysCreateProcess
GLOBAL sysBlockProcess
GLOBAL sysUnblockProcess
GLOBAL sysKillProcess
GLOBAL sysNice
GLOBAL sysPs
GLOBAL sysMalloc
GLOBAL sysFree
GLOBAL sysMem
GLOBAL sysYield
GLOBAL sysCreateSem
GLOBAL sysGetSem
GLOBAL sysPostSem
GLOBAL sysWaitSem
GLOBAL sysCloseSem
GLOBAL sysWaitPid
GLOBAL sysCreatePipe
GLOBAL sysSetReadFileDescriptor
GLOBAL sysSetWriteFileDescriptor
GLOBAL sysGetReadFileDescriptor
GLOBAL sysGetWriteFileDescriptor
GLOBAL sysGetScope

section .text

sysRead:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToRead
    mov rax, 0
    int 80h
    ret

sysWrite:         ; RDI: fileDescriptor, RSI: buffer, RDX: sizeToPrint, R10: colorHex
    mov r10, rcx
    mov rax, 1
    int 80h
    ret

sysPrintRegs:
    mov rax, 2
    int 80h
    ret

sysZoomIn:
    mov rax, 3
    int 80h
    ret

sysZoomOut:
    mov rax, 4
    int 80h
    ret

sysGetZoomLevel:
    mov rax, 5
    int 80h
    ret

sysSetZoomLevel:
    mov rax, 6
    int 80h
    ret

sysUpArrowValue:
    mov rax, 7
    int 80h
    ret

sysLeftArrowValue:
    mov rax, 8
    int 80h
    ret

sysDownArrowValue:
    mov rax, 9
    int 80h
    ret

sysRightArrowValue:
    mov rax, 10
    int 80h
    ret

sysClearScreen:
    mov rax, 11
    int 80h
    ret

sysPrintSquare:
    mov r10, rcx
    mov rax, 12
    int 80h
    ret

sysPrintRectangle:
    mov r10, rcx
    mov rax, 13
    int 80h
    ret

sysSetCursorPosition:
    mov rax, 14
    int 80h
    ret

sysBeepSound:
    mov rax, 15
    int 80h
    ret

sysSleep:
    mov rax, 16
    int 80h
    ret

sysHideCursor:
    mov rax, 17
    int 80h
    ret

sysShowCursor:
    mov rax, 18
    int 80h
    ret

sysPrintCursor:
    mov rax, 19
    int 80h
    ret

sysGetSecs:
    mov rax, 20
    int 80h
    ret

sysGetMins:
    mov rax, 21
    int 80h
    ret

sysGetHour:
    mov rax, 22
    int 80h
    ret

sysGetDay:
    mov rax, 23
    int 80h
    ret

sysGetMonth:
    mov rax, 24
    int 80h
    ret

sysGetYear:
    mov rax, 25
    int 80h
    ret

sysCtrlPressed:
    mov rax, 26
    int 80h
    ret

sysClearKbEntry:
    mov rax, 27
    int 80h
    ret

sysGetCurrentPid:
    mov rax, 28
    int 80h
    ret
    
sysExit:
    mov rax, 29
    int 80h
    ret

sysCreateProcess:
    mov rax, 30
    mov r10, rcx
    int 80h
    ret

sysBlockProcess:
    mov rax, 31
    int 80h
    ret

sysUnblockProcess:
    mov rax, 32
    int 80h
    ret

sysKillProcess:
    mov rax, 33
    int 80h
    ret

sysNice:
    mov rax, 34
    int 80h
    ret

sysPs:
    mov rax, 35
    int 80h
    ret

sysMalloc:
    mov rax, 36
    int 80h
    ret

sysFree:
    mov rax, 37
    int 80h
    ret

sysMem:
    mov rax, 38
    int 80h
    ret

sysYield:
    mov rax, 39
    int 80h
    ret


sysCreateSem:
    mov rax, 40
    int 80h
    ret

sysGetSem:
    mov rax, 41
    int 80h
    ret

sysPostSem:
    mov rax, 42
    int 80h
    ret

sysWaitSem:
    mov rax, 43
    int 80h
    ret

sysCloseSem:
    mov rax, 44
    int 80h
    ret

sysWaitPid:
    mov rax, 45
    int 80h
    ret

sysCreatePipe:
    mov rax, 46
    int 80h
    ret
sysSetReadFileDescriptor:
    mov rax, 47
    int 80h
    ret
sysSetWriteFileDescriptor:
    mov rax, 48
    int 80h
    ret

sysGetReadFileDescriptor:
    mov rax, 49
    int 80h
    ret

sysGetWriteFileDescriptor:
    mov rax, 50
    int 80h
    ret

sysGetScope:
    mov rax, 51
    int 80h
    ret
sysReadNoBlock:
    mov rax, 52
    int 80h
    ret