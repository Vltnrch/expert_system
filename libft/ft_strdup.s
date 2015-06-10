;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_strdup.s                                        :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/29 18:12:14 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/30 09:41:40 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

extern _malloc
extern _ft_strlen
extern _ft_strcpy

global _ft_strdup

section .text

_ft_strdup:
		push rdi
		call _ft_strlen
		mov rdi, rax
		inc rdi
		call _malloc
		cmp rax, 0
		jz return
		pop rsi
		dec rdi
		mov rcx, rdi
		mov rdi, rax
		call _ft_strcpy
		ret

return:
		pop rsi
		ret