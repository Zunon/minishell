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

#ifndef FT_MINISHELL_H
#define FT_MINISHELL_H

#include "../lib/libft/libft.h"
#include "dictionary.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

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
	DOUBLE_QUOTE
};

/**
 * @brief Linked list of redirections
 *
 */
typedef struct s_redirect
{
	struct s_redirect *next;		/* Next element, or NULL. */
	int flags;						/* Flag value for `open'. */
	enum e_direction direction;		/* What to do with the information. */
	char* redirectee;			/* File descriptor or filename */
	char *here_doc_delim;			/* Heredoc delimeter eg. << delim. */
}	t_redirect;

typedef struct s_command{
	int id;
	t_list *words;   			/* The program name, the arguments */
	t_redirect *redirects; 			/* Redirections to perform. */
	int exit_code;		 			/* Exit status of command */
	int fd_in;
	int fd_out;
	int pipe_in;
	int pipe_out;
	struct s_command *next;
	char **argv;
}	t_command;

typedef struct s_shell
{
	t_command *cmds;
	int num_of_cmds;
	int status_code;
	int pipes[2][2];
	t_dict *env_mngr;
	char **envp;
	pid_t last_child_pid;
	int stdout_old;
} t_shell;

typedef struct s_token
{
    enum e_token_type type;
    char *contents;
	struct s_token *next;
    struct s_token *prev;
} t_token;

extern t_shell zundra;

int	ft_echo(char **cmd);
int ft_cd(char **cmd);
int ft_pwd(char **cmd);
void ft_exit(char **);
int status_code();
int exec_builtin(t_command *cmd);
void free_commands(t_command *cmd);
t_dict *generate_env_manager(char **envp);
int ft_env();
int ft_export(t_command *cmd);
int ft_unset(char **argv);
void lexer(char *argv);
t_command *parser();
int exec_simple_cmd(t_command *cmd);
int executor(t_command *cmd);
int perform_IO_redirections(t_command *cmd);
char *expand(char *word);
t_token *tokenize(char *input);
void sig_handler(int sig);
t_command *parse_input(const char *input);
t_command *recurs_desc_parser(t_token *list);
#define ERROR_DURING_EXECUTION -99
#define NO_EXECUTION_PERMISSION 126
#define ERROR_COMMAND_NOT_FOUND 127
#define CONTROL_C_INTERRUPT 1
#define NO_PIPE -666

#endif
