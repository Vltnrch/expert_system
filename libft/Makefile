# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 17:32:05 by vroche            #+#    #+#              #
#    Updated: 2015/06/09 15:59:07 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HDR = -I./

CFLAGS = -Wall -Werror -Wextra

NFLAGS = -f macho64

S = ft_bzero.s \
	ft_cat.s \
	ft_isalnum.s \
	ft_isalpha.s \
	ft_isascii.s \
	ft_isdigit.s \
	ft_islower.s \
	ft_isprint.s \
	ft_isspace.s \
	ft_isupper.s \
	ft_memcpy.s \
	ft_memset.s \
	ft_puts.s \
	ft_strcat.s \
	ft_strclr.s \
	ft_strcpy.s \
	ft_strdup.s \
	ft_strlen.s \
	ft_strnew.s \
	ft_tolower.s \
	ft_toupper.s

OS = $(S:.s=.o)

C = ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memalloc.c \
	ft_strncpy.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_memdel.c \
	ft_strdel.c \
	ft_strcmp.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strchr.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strsplit.c \
	ft_itoa.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_realloc.c \
	ft_lstadd_back.c \
	ft_list_last.c \
	ft_list_size.c \
	ft_lltoa.c \
	ft_lltouab.c \
	get_next_line.c

OC = $(C:.c=.o)

$(NAME): $(OS) $(OC)
	ar rc $(NAME) $(OC) $(OS)
	ranlib $(NAME)

all: $(NAME)

%.o:%.s
	nasm $(NFLAGS) $<

%.o:%.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OC) $(OS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
