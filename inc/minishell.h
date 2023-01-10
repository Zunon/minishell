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

// /* A structure which represents a word. */
typedef struct s_word_desc
{
	char *word;						/* Zero terminated string. */
	int dollar_present; 			/* Non-zero means dollar sign present. */
	int quoted;						/* Non-zero means single, double, or back quote
				   						or backslash is present. */
	int assignment;					/* Non-zero means that this word contains an
				   						assignment. */
} t_word_desc;

/* A linked list of words. */
typedef struct s_word_list
{
	struct s_word_list *next;
	t_word_desc *curr_word_desc;
} t_word_list;

/* Instructions describing what kind of thing to do for a redirection. */
enum r_direction
{
	r_input,
	r_output,
	r_output_append,
	r_here_doc,
	r_pipe_in,
	r_pipe_out
};

/**
 * @brief Linked list of redirections
 *
 */
typedef struct s_redirect
{
	struct s_redirect *next;		/* Next element, or NULL. */
	int flags;						/* Flag value for `open'. */
	enum r_direction direction;		/* What to do with the information. */
	t_word_desc redirectee;			/* File descriptor or filename */
	char *here_doc_delim;			/* Heredoc delimeter eg. << delim. */
}	t_redirect;

typedef struct s_command{
	int id;
	t_word_list *words;   			/* The program name, the arguments */
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

extern t_shell zundra;

int	ft_echo(char **cmd);
int ft_cd(char **cmd);
int ft_pwd();
void ft_exit(char **);
int status_code();
int exec_builtin(t_command *cmd, char **argv);
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

#define ERROR_DURING_EXECUTION -99
#define NO_EXECUTION_PERMISSION 126
#define ERROR_COMMAND_NOT_FOUND 127
#define CONTROL_C_INTERRUPT 130
#define NO_PIPE -666

#endif
