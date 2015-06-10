;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_cat.s                                           :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/31 11:25:54 by vroche            #+#    #+#             ;;
;;   Updated: 2015/04/02 16:05:29 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

%define BUFF_SIZE 65536
%define WRITE 0x2000004
%define READ 0x2000003

global _ft_cat

section .bss
		buff: resb BUFF_SIZE

section .text

_ft_cat:
		mov r15, rdi

cat_loop:
		mov rdi, r15
		lea rsi, [rel buff]
		mov rdx, BUFF_SIZE
		mov rax, READ
		syscall
		jc return
		cmp rax, 0
		jle return
		mov rdi, 1
		lea rsi, [rel buff]
		mov rdx, rax
		mov rax, WRITE
		syscall
		jc return
		cmp rax, 0
		jle return
		jmp cat_loop

return:
		mov rdi, r15
		ret
