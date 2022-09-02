# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 20:38:43 by rriyas            #+#    #+#              #
#    Updated: 2022/09/02 23:30:05 by rriyas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIB			=	libft.a
CC			=	gcc
RM			=	rm -rf
SRCS		=	srcs/main.c
OBJS		=	${SRCS:.c=.o}


CFLAGS	=	 -Wall -Wextra -Werror


$(NAME):	${OBJS} ${LIB}
#		${CC} ${CFLAGS} -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include  ${OBJS} -lreadline libft.a -o minishell
#		$(CC) -g $(CFLAGS) $(OBJS) libft.a -lreadline -o minishell
		$(CC) -g $(CFLAGS) ${SRCS} libft.a -lreadline -o minishell
$(LIB):
		make -C lib/libft/
		mv lib/libft/libft.a libft.a

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
