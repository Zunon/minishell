# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 20:38:43 by rriyas            #+#    #+#              #
#    Updated: 2022/10/23 17:45:56 by rriyas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIB			=	./lib/libft/libft.a
CC			=	gcc
RM			=	rm -rf
SRCS		=	srcs/main.c srcs/exec.c srcs/builtins1.c srcs/builtins2.c
OBJS		=	${SRCS:.c=.o}
HEADER		=	./lib/libft/libft.h
CFLAGS	=	# -Wall -Wextra -Werror

all:	${NAME}


$(NAME):	${OBJS} ${LIB}
		$(CC) -g $(CFLAGS) ${OBJS} ${LIB} -lreadline -o minishell

$(LIB):
		make -C ./lib/libft/

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME} ${LIB}

re:		fclean all

.PHONY: all clean fclean re
