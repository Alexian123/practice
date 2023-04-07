global _start

section .data
    msg: db "Hello, World!", 0xA    ; 0xA = '\n'
    len: equ $ - msg                ; current offset - msg offset


section .text
_start:
    ; syscall: write(1, msg, len)
    mov eax, 4      ; 4 -> write syscall number
    mov ebx, 1      ; 1 -> stdout file descriptor
    mov ecx, msg
    mov edx, len
    int 0x80        ; interrupt 128 -> execute syscall

    ; syscall: exit(0)
    mov al, 1       ; 1 -> exit syscall number
    mov ebx, 0
    int 0x80

