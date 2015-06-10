;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_strclr.s                                        :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/31 17:55:21 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/31 18:13:14 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

extern _ft_strlen
extern _ft_bzero

global _ft_strclr

section .text

_ft_strclr:
		cmp rdi, 0
		je return
		mov r15, rdi
		call _ft_strlen
		mov rdi, r15
		mov rsi, rax
		call _ft_bzero

return:
		xor rax, rax
		ret
