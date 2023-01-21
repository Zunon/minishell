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
CC			=	gcc -g
RM			=	rm -rf
SRCS		=	srcs/main.c srcs/parser.c srcs/tokenizer.c srcs/expansions.c \
				srcs/sanitizers.c srcs/tlist_ops.c \
				srcs/merge_adjacent_words.c srcs/collapse_quotes.c \
				srcs/executor/exec_simple_cmd.c srcs/executor/executor.c \
				srcs/executor/redirect.c srcs/executor/signals.c \
				srcs/executor/initiator/conv_tok_to_cmd.c \
				srcs/executor/initiator/extract_redirects.c \
				srcs/executor/initiator/extract_words.c \
				srcs/executor/heredoc/construct_heredoc.c \
				srcs/executor/heredoc/handle_heredoc.c \
				srcs/executor/cleanup/cleanup.c \
				srcs/executor/builtins/cd.c srcs/executor/builtins/echo.c \
				srcs/executor/builtins/exit.c srcs/executor/builtins/pwd.c \
				srcs/executor/builtins/exec_builtin.c \
				srcs/executor/builtins/exec_builtin_parent.c \
				srcs/executor/builtins/env/dictionary_cleanup.c \
				srcs/executor/builtins/env/dictionary_utils.c \
				srcs/executor/builtins/env/dictionary.c \
				srcs/executor/builtins/env/env_initiate.c \
				srcs/executor/builtins/env/env.c \
				srcs/executor/builtins/env/export.c \
				srcs/executor/builtins/env/unset.c \
				srcs/executor/builtins/env/update_env.c
OBJS		=	${SRCS:.c=.o}

HEADER		=	./lib/libft/libft.h
CFLAGS		=	-L /usr/local/Cellar/readline/8.1/lib \
				-I /usr/local/Cellar/readline/8.1/include \
				# -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJS) $(LIB)
		$(CC) $(CFLAGS) -I ../inc/minishell.h -lreadline $(OBJS) $(LIB) -lreadline -o minishell

$(LIB):
		make -C ./lib/libft/

fd_leaks:
		make && valgrind --track-fds=yes ./minishell
leaks:
		make && valgrind --trace-children=yes --show-leak-kinds=all --leak-check=full --show-reachable=yes --error-limit=no --suppressions=inc/readline.supp  --track-fds=yes ./minishell
		# make && valgrind --show-leak-kinds=all --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=minimalraw.log ./minishell
clean:
		${RM} $(OBJS)
fclean:	clean
		${RM} ${NAME} ${LIB}
re:		fclean all

.PHONY: all clean fclean re
