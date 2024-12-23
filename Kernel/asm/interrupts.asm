GLOBAL _cli
GLOBAL _sti
GLOBAL pic_master_mask
GLOBAL pic_slave_mask
GLOBAL halt_cpu
GLOBAL request_schedule
GLOBAL _hlt
GLOBAL _irq_00_handler
GLOBAL _irq_01_handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _exception_0_handler
GLOBAL _exception_6_handler
GLOBAL _syscall_handler
GLOBAL get_regs
GLOBAL save_regs_in_buffer
EXTERN kb_get_key
EXTERN irq_dispatcher
EXTERN exception_dispatcher
EXTERN syscall_dispatcher
EXTERN get_stack_base
EXTERN schedule
SECTION .text

%macro save_regs_in_buffer 0	;; Once you enter here, regs[0]=RIP, regs[1]=RFLAGS, regs[2]=RSP
    mov [regs + 8*3], rax
    mov [regs + 8*4], rbp
    mov [regs + 8*5], rcx
    mov [regs + 8*6], rdx
    mov [regs + 8*7], rsi
    mov [regs + 8*8], rdi
    mov [regs + 8*9], rbx
    mov [regs + 8*10], r8
    mov [regs + 8*11], r9
    mov [regs + 8*12], r10
    mov [regs + 8*13], r11
    mov [regs + 8*14], r12
    mov [regs + 8*15], r13
    mov [regs + 8*16], r14
    mov [regs + 8*17], r15
%endmacro

%macro push_state_no_rax 0
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

%macro pop_state_no_rax 0
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
%endmacro

%macro push_state 0
	push rax
	push_state_no_rax
%endmacro

%macro pop_state 0
	pop_state_no_rax
	pop rax
%endmacro

%macro irq_handler_master 1
	push_state

	mov rdi, %1 ; pasaje de parametro
	call irq_dispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	pop_state
	iretq
%endmacro

%macro save_int_regs 0

	push rax
	mov rax, [rsp + 8]	; RIP Contexto anterior
	mov [regs], rax

	mov rax, [rsp + 8*3] ; RFLAGS Contexto anterior
	mov [regs + 8*1], rax

	mov rax, [rsp + 8*4] ; RSP Contexto anterior
	mov [regs + 8*2], rax

	pop rax

%endmacro
   
%macro exception_handler 1
	mov rdi, %1 ; pasaje de parametro
	call exception_dispatcher
	
	call get_stack_base

	mov [rsp+8*3], rax	;; Piso el RFLAGS

	mov rax, userland
	mov [rsp],rax		;; Piso la direccion de retorno 

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

pic_master_mask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

pic_slave_mask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq_00_handler:
	
	cli
	push_state
	mov rdi, 0 ; pasaje de parametro
	call irq_dispatcher
	
	mov rdi, rsp
	call schedule
	
	mov rsp, rax ; Cambio de proceso
	mov al, 20h ; EOI para el PIC
	out 20h, al
	pop_state
	sti
	
	iretq
	;irq_handler_master 0

;Keyboard
_irq_01_handler:
	push rax
	call kb_get_key
	cmp al, 0x38
	pop rax
	jne .continue
		save_int_regs
		save_regs_in_buffer
		
.continue:
	irq_handler_master 1

;Cascade pic never called
_irq02Handler:
	irq_handler_master 2

;Serial Port 2 and 4
_irq03Handler:
	irq_handler_master 3

;Serial Port 1 and 3
_irq04Handler:
	irq_handler_master 4

;USB
_irq05Handler:
	irq_handler_master 5


;Zero Division Exception
_exception_0_handler:
	save_int_regs
	save_regs_in_buffer
	exception_handler 0

;Invalid OpCode Exception
_exception_6_handler:
	save_int_regs
	save_regs_in_buffer
	exception_handler 6

get_regs:
	mov rax,regs
	ret	


;Syscall Handling
; _syscall_handler receives parameters in the next order: rax rdi rsi rdx r10 r8 r9
; syscall_dispatcher receives parameters via regs this way: rdi rsi rdx rcx r8 r9
; rax is the last parameters -> r9 = rax
; r10 is not a parameter -> rcx = r10
_syscall_handler:
	; --- ARQUI ---
	save_int_regs
	mov rcx, r10
	mov r9, rax
	; --- ARQUI ---
	push_state_no_rax
	call syscall_dispatcher
	pop_state_no_rax
	iretq

halt_cpu:
	cli
	hlt
	ret

request_schedule:
	int 20h
	ret

section .data
regs dq 18
userland equ 0x400000