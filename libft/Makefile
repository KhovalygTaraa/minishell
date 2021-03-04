# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 17:06:30 by swquinc           #+#    #+#              #
#    Updated: 2021/01/24 16:27:25 by swquinc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_split.c ft_memccpy.c ft_memchr.c ft_putchar_fd.c \
ft_itoa.c ft_memcmp.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_strchr.c ft_strdup.c ft_strlen.c ft_putendl_fd.c \
ft_strlcpy.c ft_strjoin.c ft_strmapi.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_strlcat.c \
ft_tolower.c ft_toupper.c ft_memmove.c ft_lstsize.c \
ft_lstadd_front.c ft_memset.c ft_memcpy.c ft_atof.c \
ft_lstnew.c ft_substr.c ft_lstlast.c ft_split_upd.c \
ft_line_malloc.c get_next_line.c ft_blstadd_front.c \
ft_lstadd_back.c ft_blstadd_back.c ft_strjoin_free.c \
ft_atod.c ft_blstnew.c ft_strcmp.c 

OBJ = $(SRC:.c=.o)

HEADERS = libft.h

RULES = all clean fclean re 

.PHONY: $(RULES)

all: $(NAME)

%.o: %.c $(HEADERS)
	gcc -Wall -Wextra -Werror -c $< -o $@ -I $(HEADERS)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
