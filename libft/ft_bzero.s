;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;
;;                                                                            ;;
;;                                                        :::      ::::::::   ;;
;;   ft_bzero.s                                         :+:      :+:    :+:   ;;
;;                                                    +:+ +:+         +:+     ;;
;;   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        ;;
;;                                                +#+#+#+#+#+   +#+           ;;
;;   Created: 2015/03/21 17:34:56 by vroche            #+#    #+#             ;;
;;   Updated: 2015/03/30 09:24:22 by vroche           ###   ########.fr       ;;
;;                                                                            ;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;;

extern _ft_memset

global _ft_bzero

section .text

_ft_bzero:
		mov rdx, rsi
		xor rsi, rsi
		call _ft_memset
		ret
