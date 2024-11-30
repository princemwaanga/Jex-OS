bits 32
global _start
extern kernel_early
extern main

%include "boot/32bit-gdt.asm"

section .text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd -(0x1BADB002 + 0x00);checksum

_start:
	cli
	mov esp,stack
	call kernel_early
	call main
	hlt

section .bss
resb 8192

stack:
