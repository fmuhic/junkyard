format PE console
entry start

include 'win32a.inc' 

section '.text' code readable executable

start:
    mov     eax,0

incrementer:
    inc     eax
    call    print_eax
    jmp     incrementer    

    ; Never executed
    push	0
    call	[ExitProcess]

include 'training.inc'
