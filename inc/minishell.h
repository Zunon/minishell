/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:50:36 by rriyas            #+#    #+#             */
/*   Updated: 2022/10/22 20:37:12 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "dictionary.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <pthread.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define ERROR_DURING_EXECUTION -99
# define NO_EXECUTION_PERMISSION 126
# define ERROR_COMMAND_NOT_FOUND 127
# define CONTROL_C_INTERRUPT 1
# define NO_PIPE -666

/* Instructions describing what kind of thing to do for a redirection. */
enum e_direction
{
	INPUT,
	OUTPUT,
	OUTPUT_APPEND,
	HERE_DOC,
};

enum e_token_type
{
	VARIABLE,
	WORD,
	REDIRECTION,
	PIPE,
	WHITESPACE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	QUOTED,
	ERROR
};

/**
 * @brief Linked list of redirections
 *
 */
typedef struct s_redirect
{
	struct s_redirect	*next;
	int					flags;
	enum e_direction	direction;
	char				*redirectee;
	char				*here_doc_delim;
}	t_redirect;

typedef struct s_command
{
	int					id;
	t_list				*words;
	t_redirect			*redirects;
	int					exit_code;
	int					fd_in;
	int					fd_out;
	int					pipe_in;
	int					pipe_out;
	struct s_command	*next;
	char				**argv;
}	t_command;

typedef struct s_shell
{
	t_command	*cmds;
	int			num_of_cmds;
	int			status_code;
	int			**pipes;
	t_dict		*env_mngr;
	char		**envp;
	pid_t		last_child_pid;
	int			stdout_old;
}	t_shell;

typedef struct s_token
{
	enum e_token_type	type;
	char				*contents;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

int			ft_echo(char **cmd);
int			ft_cd(char **cmd);
int			ft_pwd(char **cmd);
void		ft_exit(char **cmd);
int			exec_builtin(t_command *cmd);
void		free_commands(t_command *cmd);
t_dict		*generate_env_manager(char **envp);
int			ft_env(void);
int			ft_export(t_command *cmd);
int			ft_unset(char **argv);
int			exec_simple_cmd(t_command *cmd);
int			executor(t_command *cmd);
int			perform_IO_redirections(t_command *cmd);
char		*expand(char *word);
t_token		*tokenize(char *input);
void		sig_handler(int sig);
t_command	*parse_input(const char *input);
t_command	*token_to_cmd_converter(t_token *list);
int			find_pos(char *s, char c);
t_token		*discard_dollar(t_token *list);
t_token		*split_words_on_whitespace(t_token *list);
t_token		*token_split(char *string);
t_token		*token_last(t_token *list);
t_token		*merge_quotation_tokens(t_token *quote);
void		print_tokens(t_token *list); // REMOVE BEFORE SUBMISSION
t_token		*discard_whitespace(t_token *list);
t_token		*expand_variables(t_token *list);
t_token		*disquote(t_token *list);
void		clear_tokenlist(t_token **list);
t_token		*collapse_quotes(t_bool single, t_token *list);
t_token		*merge_words(t_token *list);
t_bool		parse_pipeline(t_token *list);

extern t_shell	g_krsh; // RENAME BEFORE SUBMISSION to g_krsh

#endif
