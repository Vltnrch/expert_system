;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_strnew.s                                        :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/31 18:58:22 by vroche            #+#    #+#             ;;
;;   Updated: 2015/04/02 15:41:30 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

extern _malloc
extern _ft_bzero

global _ft_strnew

section .text

_ft_strnew:
		inc rdi
		push rdi
		call _malloc
		cmp rax, 0
		jz return
		pop rsi
		mov rdi, rax
		call _ft_bzero
		ret

return:
		pop rdi
		ret
