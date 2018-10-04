[BITS 16]
org 0x7c00

xor ax, ax
mov dx, ax
mov ss, ax
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
jmp 0x0:start
 
msg: db 'Hello World', 0
msg_len: equ $-msg

;start:
;	mov ax, 0xb800  			;;video memory begins here
;	mov gs, ax
;
;	mov cx, 25*80				;;25 lines and 80 columns
;	xor bx, bx

;spaces:
;	mov [gs:bx], byte ' '			
;	mov [gs:bx+1], byte 0x1a	;;attribute (fon text)
;	add bx, 2
;	loop spaces
;
;	mov cx, msg_len
;	xor si, si
;	xor bx, bx

;out:
;	mov di, [msg+si]
;	mov [gs:bx], di
;	mov [gs:bx+1], byte 0x1a
;	inc si
;	add bx, 2
;	loop out

;	jmp $


start:
	mov ax,3h
	int 10h

	mov ah, 13h
	mov al, 0x01

	mov bl, 0x0f
	mov cx, msg_len	
	mov bp, msg
	int 10h

read_sector:
	mov al, 0x4
	xor ch, ch
	mov cl, 0x02
	xor dh, dh
	mov dl, 0x80
	int 13h


times 510-($-$$) db 0

dw 0xaa55
