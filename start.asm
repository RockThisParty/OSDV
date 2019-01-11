; vim:ft=nasm
[bits 16]
;[org 0x7e00]


; |----------------------2 bytes--------------------|
;
; +-------------------------------------------------+
; | segment address 24-31  | flags #2  | len 16-19  | +6
; +-------------------------------------------------+
; | flags #1               | segment address 16-23  | +4
; +-------------------------------------------------+
; | segment address bits 0-15                       | +2
; +-------------------------------------------------+
; | segment length bits 0-15                        | +0
; +-------------------------------------------------+


cli			;disable interrupts

lgdt[gdt_descriptor]	;initial gdt

mov eax, cr0		;cr0->0
or al, 1
mov cr0, eax

jmp 0x08:start

[bits 32]

start:
    mov ax, 0x10	;second descriptor- data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov ss, ax
    mov gs, ax
    
    mov edx, 0xb8000 + 160
    mov esi, msg
    mov ah, 0x0f
    call print
	
    extern cmain
    call cmain

    jmp $


print:
    mov al, [esi]
    cmp al, 0
    je .end
    mov [edx], ax
    add edx, 2
    inc esi
    jmp print
.end:
    ret

gdt_null:
    dd 0
    dd 0

gdt_code:
    dw 0xffff		;limit 0-15
    dw 0		;base 0-23
    db 0
    db 0x9A		;access byte 10011010
			;7: 1 - valid sector
			;6-5: privelege (0 - kernel)
			;4: reserved 1
			;3: 1 - code segment
			;2: 0 - c b executed from kernel
			;1: 1 - readable
			;0: 0 - reserved
    db 0xCF		;11001111 flags + limit 16-19
			;granularity -  1
			;1 - 32 bit
    db 0		;base 24-31

gdt_data:
    dw 0xffff		;segment length
    dw 0		;segment address 0-15
    db 0		;16-23
    db 0x92		;10010010
			;7: 1 - valid sector
			;6-5: privelege (0 - kernel)
			;4: reserved 1
			;3: 0 - data segment
			;2: 0 - segment grows up
			;1: 1 - writable
			;0: 0 - reserved
    db 0xCF		;11001111 flags + limit 16-19
			;granularity -  1
			;1 - 32 bit protected flags 2, segment length 16-19
    db 0x0		;segment address 24-31

gdt_descriptor:
    dw gdt_descriptor - gdt_null -1
    dd gdt_null

msg db 'protected mode', 0

times 512 - ($ - $$) db 0
