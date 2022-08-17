format PE console
entry start

include 'win32a.inc' 

section '.text' code readable executable

start:
    call    read_hex
    mov     edx, eax
    call    read_hex
    add     eax, edx
    call    print_eax

	push	0
	call	[ExitProcess]

include 'training.inc'
