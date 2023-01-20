valgrind -s --track-fds=yes --tool=memcheck --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=.ignore_readline.txt ./minishell
