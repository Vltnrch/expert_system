;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_puts.s                                          :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/30 11:35:31 by vroche            #+#    #+#             ;;
;;   Updated: 2015/04/02 13:22:04 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

%define WRITE 0x2000004

extern _ft_strlen

global _ft_puts

section .data
		msgnull: db "(null)", 10, 0

section .rodata
		eol db 0x0a

section .text

_ft_puts:
		cmp rdi, 0
		je null
		mov r15, rdi
		call _ft_strlen
		mov rdi, 1
		mov rsi, r15
		mov rdx, rax
		mov rax, WRITE
		syscall
		jc return
		mov r15, rax
		mov rdi, 1
		lea rsi, [rel eol]
		mov rdx, 1
		mov rax, WRITE
		syscall
		jc return
		mov rax, r15
		inc rax
		ret

null:
		mov rax, WRITE
		mov rdi, 1
		lea rsi, [rel msgnull]
		mov rdx, 7
		syscall
		jc return
		ret

return:
		ret
