section .multiboot_header
header_start:
    ; multiboot2 magic number to support grub2
    dd 0xe85250d6 ; data define
    ; architecture specific data
    dd 0 ; switch to protected mode on ia32
    ; header length
    dd header_end - header_start
    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; end tag
    dw 0 ; write 0
    dw 0 ; write 0
    dd 8 ; write 8
header_end:
