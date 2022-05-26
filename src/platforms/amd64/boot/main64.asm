; Copyright 2022, Gary L. Greene Jr. <greeneg@yggdrasilsoft.com>
;
; This source code is part of the xOS kernel and is licensed under the terms of
; the GNU Lesser General Public License, v2.1.

global long_mode_start ; make global to allow nasm to find it when linking

section .text
bits 64 ; we're now in 64-bit land
long_mode_start:
    ; initialize data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; print `OK`
    mov dword [0xb8000], 0x2f4b2f4f ; symbolic of "OK"

    hlt