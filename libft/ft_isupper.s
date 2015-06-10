;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_isupper.s                                       :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/04/02 18:20:42 by vroche            #+#    #+#             ;;
;;   Updated: 2015/04/02 18:22:47 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

global _ft_isupper

section .text

_ft_isupper:
		cmp rdi, 65
		jl return
		cmp rdi, 90
		jg return
		mov rax, 1
		ret

return:
		mov rax, 0
		ret
