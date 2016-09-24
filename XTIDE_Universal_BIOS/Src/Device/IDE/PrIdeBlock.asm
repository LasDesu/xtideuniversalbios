
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
	push 	si
	mov		si, PRIDE_REGISTER_WINDOW_OFFSET
	push	ds
	mov		ds, dx	; Segment for JR-IDE/ISA and ADP50L
ALIGN JUMP_ALIGN
.InswLoop:
	%rep 8	; WORDs	
	movsw	; Move word from [DS:SI] to [ES:DI]
	dec		si
	dec		si
	%endrep
	loop	.InswLoop
	pop		ds
	pop		si
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
	push	es	; from ES
	pop		ds	; to DS
	UNROLL_SECTORS_IN_CX_TO_QWORDS
	push	di
	mov		di, PRIDE_REGISTER_WINDOW_OFFSET
	mov		es, dx	; Segment for PrIDE
ALIGN JUMP_ALIGN
.OutswLoop:
	%rep 4	; WORDs
	movsw	; Move word from [DS:SI] to [ES:DI]
	dec		di
	dec		di
	%endrep
	loop	.OutswLoop
	pop		di
	pop		ds
	ret
