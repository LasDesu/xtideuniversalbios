; Project name	:	AssemblyLibrary
; Description	:	Defines for MS-DOS functions.
%ifndef DOS_FUNCTIONS_INC
%define DOS_FUNCTIONS_INC

; DOS interrupts
DOS_INTERRUPT_21h									EQU		21h
DOS_CTRL_C_CTRL_BREAK_HANDLER_23h					EQU		23h
DOS_CRITICAL_ERROR_HANDLER_24h						EQU		24h
DOS_TSR_MULTIPLEX_INTERRUPT_2Fh						EQU		2Fh

; DOS functions
WRITE_CHARACTER_TO_STANDARD_OUTPUT					EQU		02h		; DOS 1+
WRITE_STRING_TO_STANDARD_OUTPUT						EQU		09h		; DOS 1+
SELECT_DEFAULT_DRIVE								EQU		0Eh		; DOS 1+
GET_CURRENT_DEFAULT_DRIVE							EQU		19h		; DOS 1+
SET_INTERRUPT_VECTOR								EQU		25h		; DOS 1+
GET_DISK_TRANSFER_AREA_ADDRESS						EQU		2Fh		; DOS 2+
GET_DOS_VERSION										EQU		30h		; DOS 2+
GET_DOS_DRIVE_PARAMETER_BLOCK_FOR_SPECIFIC_DRIVE	EQU		32h		; DOS 2+
GET_INTERRUPT_VECTOR								EQU		35h		; DOS 2+
SET_CURRENT_DIRECTORY								EQU		3Bh		; DOS 2+
CREATE_OR_TRUNCATE_FILE								EQU		3Ch		; DOS 2+
OPEN_EXISTING_FILE									EQU		3Dh		; DOS 2+
CLOSE_FILE											EQU		3Eh		; DOS 2+
READ_FROM_FILE_OR_DEVICE							EQU		3Fh		; DOS 2+
WRITE_TO_FILE_OR_DEVICE								EQU		40h		; DOS 2+
SET_CURRENT_FILE_POSITION							EQU		42h		; DOS 2+
CHECK_IF_BLOCK_DEVICE_REMOTE						EQU		4409h	; DOS 3.1+
GET_CURRENT_DIRECTORY								EQU		47h		; DOS 2+
TERMINATE_WITH_RETURN_CODE							EQU		4Ch		; DOS 2+
FIND_FIRST_MATCHING_FILE							EQU		4Eh		; DOS 2+
FIND_NEXT_MATCHING_FILE								EQU		4Fh		; DOS 2+
GET_EXTENDED_ERROR_INFORMATION						EQU		59h		; DOS 3.0+

; DOS errors
ERR_DOS_FUNCTION_NUMBER_INVALID						EQU		01h
ERR_DOS_INVALID_DRIVE								EQU		0Fh
ERR_DOS_DRIVE_NOT_READY								EQU		15h


; DOS Program Segment Prefix (PSP, first 256 (100h) bytes on top of program)
struc PSP
	.int20hInstruction				resb	2
	.wSizeOfMemoryInParagraphs		resb	2
	.reservedAt4h					resb	1
	.callToDosFunctionDispatcher	resb	5
	.fpInt22hTerminate				resb	4
	.fpInt23hCtrlC					resb	4
	.fpInt24hCriticalError			resb	4
	.reservedAt16h					resb	22
	.wEnvironmentSegment			resb	2
	.reservedAt2Eh					resb	34
	.int21hAndRetfInstructions		resb	3
	.reservedAt53h					resb	9
	.FCB1							resb	16
	.FCB2							resb	20
	.DiskTransferArea:
	.bCommandLineLength				resb	1
	.szCommandLine					resb	127
endstruc


; DOS DTA (Disk Transfer Area)
struc DTA
	; Undocumented fields
	.reservedAt0h		resb	21
	; Documented fields
	.bFileAttributes	resb	1	; 15h, Attribute of matching file
	.wFileTime			resb	2	; 16h, File time
	.wFileDate			resb	2	; 18h, File date
	.dwFileSize			resb	4	; 1Ah, File size in bytes
	.szFile				resb	13	; 1Eh, ASCIZ filename + extension
endstruc


%endif ; DOS_FUNCTIONS_INC
