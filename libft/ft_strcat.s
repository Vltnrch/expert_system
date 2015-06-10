;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_strcat.s                                        :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/30 10:05:28 by vroche            #+#    #+#             ;;
;;   Updated: 2015/04/02 16:15:35 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

extern _ft_strlen

global _ft_strcat

section .text

_ft_strcat:
		mov r15, rdi

end_s1:
		cmp byte [rdi], 0
		je cpy
		inc rdi
		jmp end_s1

cpy:
		cmp byte [rsi], 0
		je end
		mov rax, [rsi]
		mov [rdi], al
		inc rsi
		inc rdi
		jmp cpy

end:
		mov byte [rdi], 0
		mov rax, r15
		ret
