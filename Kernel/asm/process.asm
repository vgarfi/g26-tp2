GLOBAL create_initial_stack

create_initial_stack:

create_initial_stack: 
	mov r8, rsp
	mov rsp, rdi
	push 0x0
	push rdi ; stack base
	push 0x202
	push 0x8
	push rcx ; code
	push 0x0
	push 0x1
    push 0x2
    push 0x3
    push 0x4
    push rsi ; argc
    push rdx ; argv
    push 0x8 ; wrapper
    push 0x9
    push 0x10
    push 0x11
    push 0x12
    push 0x13
    push 0x14
    push 0x15
	mov rax,rsp
	mov rsp,r8
	ret
