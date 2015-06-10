;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_isspace.s                                       :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/04/02 17:07:03 by vroche            #+#    #+#             ;;
;;   Updated: 2015/04/02 18:32:22 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

global _ft_isspace

section .text

_ft_isspace:
		cmp rdi, 32
		je return_ok
		cmp rdi, 9
		jl return
		cmp rdi, 13
		jg return
		mov rax, 1
		ret

return:
		mov rax, 0
		ret

return_ok:
		mov rax, 1
		ret
