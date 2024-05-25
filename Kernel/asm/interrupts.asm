
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL _syscallHandler
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher

EXTERN vdClearScreen
SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

   
   
%macro exceptionHandler 1
	pushState
	push rbp
	mov rbp,rsp

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher
	push rax
	xor rax ,rax
.loop: in al,0x64
	mov cl,al
	and al,0x01
	cmp al,0
	je .loop
	mov al, 20h
	out 20h, al
	pop rax
	call vdClearScreen
	mov rsp,rbp
	pop rbp

	
	popState
	push rax 
	mov rax,[rsp+8]
	add al,3
	mov [rsp +8],rax
	pop rax
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid OpCode Exception
_exception6Handler:
	exceptionHandler 6
	
;Syscall Handling
; _syscallHandler receives parameters in the next order: rax rdi rsi rdx r10 r8 r9
; syscallDispatcher receives parameters via regs this way: rdi rsi rdx rcx r8 r9
; rax is the last parameters -> r9 = rax
; r10 is not a parameters -> rcx = r10
_syscallHandler:
	mov rcx, r10
	mov r9, rax
	call syscallDispatcher
	iretq

haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1