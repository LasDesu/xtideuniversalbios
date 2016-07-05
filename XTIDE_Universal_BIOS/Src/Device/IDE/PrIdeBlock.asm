
; Section containing code
SECTION .text


; --------------------------------------------------------------------------------------------------
;
; READ routines follow
;
; --------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------
; IdePioBlock_ReadFromPrIDE
;	Parameters:
;		CX:		Block size in 512 byte sectors
;		DX:		IDE Data port address
;		ES:DI:	Normalized ptr to buffer to receive data
;	Returns:
;		Nothing
;	Corrupts registers:
;		AX, BX, CX
;--------------------------------------------------------------------
ALIGN JUMP_ALIGN
IdePioBlock_ReadFromPrIDE:
	UNROLL_SECTORS_IN_CX_TO_OWORDS
	mov		bx, PRIDE_REGISTER_WINDOW_OFFSET
	push	ds
	mov		ds, dx	; Segment for JR-IDE/ISA and ADP50L
ALIGN JUMP_ALIGN
.InswLoop:
	%rep 8	; WORDs
	mov		al, [bx + 0]
	mov		ah, [bx + 1]
	stosw						; Store word to [ES:DI]
	%endrep
	loop	.InswLoop
	pop	ds
	ret
	

; --------------------------------------------------------------------------------------------------
;
; WRITE routines follow
;
; --------------------------------------------------------------------------------------------------

;--------------------------------------------------------------------
; IdePioBlock_WriteToPrIDE
;	Parameters:
;		CX:		Block size in 512-byte sectors
;		DX:		IDE Data port address
;		ES:SI:	Normalized ptr to buffer containing data
;	Returns:
;		Nothing
;	Corrupts registers:
;		AX, BX, CX
;--------------------------------------------------------------------
ALIGN JUMP_ALIGN
IdePioBlock_WriteToPrIDE:
	push	ds
	UNROLL_SECTORS_IN_CX_TO_QWORDS
	push	es
	pop		ds
	mov		bx, PRIDE_REGISTER_WINDOW_OFFSET
	mov		es, dx	; Segment for JR-IDE/ISA and ADP50L
ALIGN JUMP_ALIGN
.OutswLoop:
	%rep 4	; WORDs
	lodsw						; Load word from [DS:SI]
	mov		[es:bx + 1], ah
	mov		[es:bx + 0], al
	%endrep
	loop	.OutswLoop
	push	ds
	pop		es
	pop		ds
	ret
