;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_tolower.s                                       :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/24 20:50:59 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/24 21:01:10 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

global _ft_tolower

section .text

_ft_tolower:
	mov rax, rdi
	cmp rax, 65 ; 65 = 'A'
	jl return
	cmp rax, 90 ; 90 = 'Z'
	jg return
	add rax, 32
	ret

return:
	ret
