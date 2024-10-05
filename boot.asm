hello:
asm "jmp hello"
call hello
 times 510-($-$$) db 0
dw 0x55aa