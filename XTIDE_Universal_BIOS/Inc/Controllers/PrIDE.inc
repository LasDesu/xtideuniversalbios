; Project name	:	XTIDE Universal BIOS

;
; XTIDE Universal BIOS and Associated Tools
; Copyright (C) 2009-2010 by Tomi Tilli, 2011-2013 by XTIDE Universal BIOS Team.
;
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
; Visit http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
;

%ifndef PRIDE_INC
%define PRIDE_INC

; | BIOS Segment --------- | Unknown - | ROM Chip ---------- |
;	Jumper:		J1	J2	J3	J4	J5	J6	J7
;	Disabled	N/A	N/A	OFF	OFF	OFF	OFF	OFF	= 2764 / 27C64 *
;	C800h *		OFF	OFF	ON				ON	= 27256 / 27C256
;	CA00h		ON	OFF	ON
;	CC00h		OFF	ON	ON
;	CE00h		ON	ON	ON
;
; * Defaults
; Unknown = "Factory configured - do not alter"
; Bits 11...9 of the segment address corresponds to jumpers J3...J1.

PRIDE_BIOS_SEGMENT_ADDRESS		EQU		0F000h	; Default

; Offsets from BIOS segment address
PRIDE_REGISTER_WINDOW_OFFSET	EQU	0C00h

%endif ; PRIDE_INC
