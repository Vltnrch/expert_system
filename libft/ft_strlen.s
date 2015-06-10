;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_strlen.s                                        :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/27 12:22:33 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/27 17:45:34 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

global _ft_strlen

section .text

_ft_strlen:
		xor rcx, rcx
		not rcx
		xor al, al
		repne scasb
		not rcx
		dec rcx
		mov rax, rcx
		ret
