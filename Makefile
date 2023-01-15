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
SRCS		=	srcs/main.c srcs/executor.c srcs/exec_simple_cmd.c \
				srcs/builtins1.c srcs/builtins2.c srcs/env_initiate.c \
				srcs/env_utils.c srcs/dictionary.c srcs/dictionary_utils.c \
				srcs/dictionary_cleanup.c srcs/redirect.c srcs/cleanup.c \
				srcs/parser.c srcs/tokenizer.c srcs/expansions.c \
				srcs/command_builder.c srcs/sanitizers.c srcs/tlist_ops.c \
				srcs/collapse_and_merge.c
OBJS		=	${SRCS:.c=.o}
LEX_TEST_SRCS	=	srcs/executor.c srcs/exec_simple_cmd.c srcs/builtins1.c \
					srcs/builtins2.c srcs/env_initiate.c srcs/env_utils.c \
					srcs/dictionary.c srcs/dictionary_utils.c \
					srcs/dictionary_cleanup.c srcs/redirect.c srcs/cleanup.c \
					tests/lexer/*.c
LEX_TEST_OBJS	=	${LEX_TEST_SRCS:.c=.o}
PARSE_TEST_SRCS	=	srcs/executor.c srcs/exec_simple_cmd.c srcs/builtins1.c \
					srcs/builtins2.c srcs/env_initiate.c srcs/env_utils.c \
					srcs/dictionary.c srcs/dictionary_utils.c \
					srcs/dictionary_cleanup.c srcs/redirect.c srcs/cleanup.c \
					tests/parser/*.c
PARSE_TEST_OBJS	=	${PARSE_TEST_SRCS:.c=.o}
EXEC_TEST_SRCS	=	tests/executor/env_tests.c \
				tests/executor/absolute_path_cmd_tests.c \
				tests/executor/pipe_tests.c tests/executor/redirect_in_tests.c \
				tests/executor/builtin_cmd_tests.c \
				tests/executor/redirect_and_pipe_tests.c \
				tests/executor/redirect_out_tests.c \
				tests/executor/redirect_in_out_tests.c \
				tests/executor/relative_path_cmd_tests.c srcs/executor.c \
				srcs/exec_simple_cmd.c srcs/builtins1.c srcs/builtins2.c \
				srcs/env_initiate.c srcs/env_utils.c srcs/dictionary.c \
				srcs/dictionary_utils.c srcs/dictionary_cleanup.c \
				srcs/redirect.c srcs/cleanup.c
EXEC_TEST_OBJS	=	${EXEC_TEST_SRCS:.c=.o}
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
		make re && valgrind --track-fds=yes ./minishell
leaks:
		make && valgrind --show-leak-kinds=all --leak-check=full --show-reachable=yes --error-limit=no --suppressions=inc/readline.supp --log-file=valg_errors.log ./minishell
		# make && valgrind --show-leak-kinds=all --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=minimalraw.log ./minishell
lex_tester:	$(LEX_TEST_OBJS) $(LIB)
		$(CC) -g -no-pie -fsanitize=address $(CFLAGS) -I ../inc/minishell.h -lreadline $(LEX_TEST_OBJS) $(LIB) -lreadline -o minishell
parser_tester:	$(PARSE_TEST_OBJS) $(LIB)
		$(CC) -g -no-pie -fsanitize=address $(CFLAGS) -I ../inc/minishell.h -lreadline $(PARSE_TEST_OBJS) $(LIB) -lreadline -o minishell
exec_tester:	$(EXEC_TEST_OBJS) $(LIB)
		$(CC) -g $(CFLAGS) -I ../inc/minishell.h -lreadline $(EXEC_TEST_OBJS) $(LIB) -lreadline -o minishell
clean:
		${RM} $(OBJS) $(PARSE_TEST_OBJS) $(EXEC_TEST_OBJS)
fclean:	clean
		${RM} ${NAME} ${LIB}
re:		fclean all

.PHONY: all clean fclean re
