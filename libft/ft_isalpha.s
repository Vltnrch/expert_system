;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_isalpha.s                                       :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/24 19:20:15 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/24 20:07:26 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

global _ft_isalpha

section .text

_ft_isalpha:
		cmp rdi, 97 ; 97 = 'a'
		jl alphamax
		cmp rdi, 122 ; 122 = 'z'
		jg return
		mov rax, 1
		ret

alphamax:
		cmp rdi, 65 ; 65 = 'A'
		jl return
		cmp rdi, 90 ; 90 = 'Z'
		jg return
		mov rax, 1
		ret
		

return:
		mov rax, 0
		ret
