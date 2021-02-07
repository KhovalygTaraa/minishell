#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 19:48:56 by hovalygta         #+#    #+#              #
#    Updated: 2021/01/20 12:34:41 by swquinc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRC_NAME		=	main.c \
					parser.c \
					parse_echo.c \
					parse_env.c \
					executor.c \
					exec.c \
					exec_cd.c \
					exec_echo.c \
					exec_env.c \
					exec_exit.c \
					exec_export.c \
					exec_pwd.c \
					exec_unset.c \
					utils.c \
					error_handler.c \
					signal.c

SRC_DIR			=	srcs
OBJ_DIR			=	obj
LIBFT_DIR		=	libft

LIBFT_A			=	$(LIBFT_DIR)/libft.a

CC				=	gcc
FLAGS			=	#-Wall -Wextra -Werror
INCLUDES		= 	-I includes -I $(LIBFT_DIR)

OBJ 			= 	$(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./includes/minishell.h
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(LIBFT_A) -o $(NAME)

clean:
	/bin/rm -f $(OBJ_DIR)/*
	/bin/rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
