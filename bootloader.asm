[BITS 16]
org 0x7c00

;Инициализация сегментных регистров
xor ax, ax		
mov dx, ax
mov ss, ax		;ss-stack segment
mov ds, ax		;ds-data segment
mov es, ax		;es,fs,gs-дополнительные сегментные регистры
mov fs, ax		
mov gs, ax
jmp 0x0:start		;инициализация cs-code segment

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
	mov ax,3h		;Change video mode
	int 10h

	mov ah, 13h		;write string
	mov al, 0x01		;write mode without attributes

	mov bl, 0x0f		;attribute
	mov cx, msg_len	
	mov bp, msg
	int 10h

read_sector:
	mov bx, 0x07e0
	mov es, bx
	mov ah, 2h
	mov al, 10h		;Count of sectors 
	xor ch, ch		;Cylinder number
	mov cl, 2h		;Sector number
	xor dh, dh		;Head number
	xor dl, 80h		;Disk number
	xor bx, bx
	int 13h

	jmp 0x7e00

	mov cx, 80h
	mov bl, 0x0f
	xor bh, bh
	xor bp, bp
	xor dx, dx
	sub bp, 512

times 510-($-$$) db 0

dw 0xaa55
