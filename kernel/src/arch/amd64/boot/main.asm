; Copyright 2022, Gary L. Greene Jr. <greeneg@yggdrasilsoft.com>
;
; This source code is part of the xOS kernel and is licensed under the terms of
; the GNU Lesser General Public License, v2.1.

global start
extern long_mode_start

section .text
bits 32
start:
    mov esp, stack_top

    ; test that we were started using a multiboot conformant bootloader
    call check_multiboot
    ; verify chip returns cpuid data
    call check_cpuid
    ; check that 64-bit support is possble on the chip
    call check_long_mode

    ; now we need to set up paging
    call setup_page_tables
    call enable_paging

    ; load global descriptor table
    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start

    hlt

check_multiboot:
    ; check if the magic number multiboot bootloaders store in the eax register is present
    cmp eax, 0x36d76289 ; compare eax
    jne .no_multiboot ; jump to the no_multiboot label if the compare above fails
    ret
.no_multiboot:
    mov al, "M"
    jmp error

check_cpuid:
    ; check if the CPU supports the cpuid feature
    ; to check this, we flip the flags register, if it completes correctly, it's supported
    ; otherwise, it's not
    pushfd
    pop eax
    mov ecx, eax
    ; flip the bit
    xor eax, 1 << 21 ; 21 is the cpuid flag register
    push eax
    popfd
    ; now check if flag had been stored correctly
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .no_cpuid
    ret
.no_cpuid:
    mov al, "C"
    jmp error

check_long_mode:
    ; Unfortunately, due to issues with early x86_64 and em64t chips, we need
    ; to check for these various flags to see if there is full support in the
    ; host's CPU
    ; first check for extended processor info
    mov eax, 0x80000000
    cpuid ; implicitly takes eax as argument
    ; if we get back a number higher than the one currently stored in eax, the
    ; cpu supports extended processor info
    cmp eax, 0x80000001
    jb .no_long_mode

    ; set the flag to enable long-mode
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29 ; 29 is the LM register
    jz .no_long_mode
    ret
.no_long_mode:
    mov al, "L"
    jmp error

setup_page_tables:
    ; identity map the first 1G of memory to allow the CPU to map where
    ; RAM is virtually <-> physically
    ; linked lists, all the way down....
    mov eax, page_table_l3
    ; inside the first 12 bytes, certain items are stored for controlling
    ; the access and such of the page registers. First we need the 'present'
    ; and 'writable' flags
    or eax, 0b11 ; present, writable
    mov [page_table_l4], eax

    ; do the same for the l3 table
    mov eax, page_table_l2
    or eax, 0b11 ; present, writable
    mov [page_table_l3], eax

    ; loop over the remaining 512 pages in the l2 pagetable to fill out the
    ; rest of the 1G pagetable map
    mov ecx, 0 ; counter
.loop:

    mov eax, 0x200000 ; 2MiB
    mul ecx ; multiply eax by ecx to get the address for the next page
    ; add the present and writable bits in again
    or eax, 0b10000011 ; huge page, present, writable
    mov [page_table_l2 + ecx * 8], eax ; assign to the next valid page in L2

    inc ecx ; increment the counter
    cmp ecx, 512 ; at the end?
    jne .loop ; nope, iterate once more through the loop

    ret

enable_paging:
    ; actually enable paging and enter long mode
    ;
    ; pass pagetable to the CPU
    mov eax, page_table_l4
    mov cr3, eax

    ; enable PAE
    mov eax, cr4
    or eax, 1 << 5 ; PAE register
    mov cr4, eax

    ; finally, enable long-mode
    mov ecx, 0xC0000080 ; EFER (Extended Feature Enable register)
    rdmsr ; read the EFER into eax
    or eax, 1 << 8 ; the long-mode register
    wrmsr ; write the LM register back into the EFER

    ; Now that LM is up, enable paging
    mov eax, cr0 ; cr0 is the paging register
    or eax, 1 << 31 ; 31 is the register for enabling paging
    mov cr0, eax ; and go!

    ret

error:
    ; print "ERR: X" where X is the error code. When done, halt the CPU
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt

; statically allocated variables and structures
section .bss
align 4096 ; aligning our page tables on 4096 byte segments
page_table_l4:
    resb 4096
page_table_l3:
    resb 4096
page_table_l2:
    resb 4096
; our stack frames
stack_bottom:
    resb 4096 * 4 ; 16 k of stack for initial. C will take over once we get
                  ; beyond the 16-bit mode stuff
stack_top:

; need a global descriptor table (not normally used, as we have paging enabled)
; so we can enter 64-bit mode
section .rodata
gdt64:
    dq 0 ; requires a zeroth entry
    ; 43 is the 'executable' flag,
    ; 44 is the 'code and data' segement type flag
    ; 47 is the 'present' flag
    ; 53 is the '64-bit' flag
.code_segment: equ $ - gdt64 ; offset
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; code segment flags
.pointer:
    dw $ - gdt64 - 1 ; take the current memory address, and subtract it to get
                     ; the length to the pointer address
    dq gdt64         ; store address
