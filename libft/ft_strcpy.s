;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_strcpy.s                                        :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/29 18:34:41 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/30 10:21:47 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

extern _ft_strlen
extern _ft_memcpy

global _ft_strcpy

section .text

_ft_strcpy:
		push rdi
		push rsi
		mov rdi, rsi
		call _ft_strlen
		inc rax
		mov rdx, rax
		pop rsi
		pop rdi
		call _ft_memcpy
		ret
		