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
#define MINISHELL_H

#include "../lib/libft/libft.h"
#include "hashtable.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

// /* A structure which represents a word. */
typedef struct s_word_desc
{
	char *word;			/* Zero terminated string. */
	int dollar_present; /* Non-zero means dollar sign present. */
	int quoted;			/* Non-zero means single, double, or back quote
				   or backslash is present. */
} t_word_desc;

/* A linked list of words. */
typedef struct word_list
{
	struct word_list *next;
	t_word_desc *word;
} WORD_LIST;

/* Instructions describing what kind of thing to do for a redirection. */
enum r_direction
{
	r_input,
	r_output,
	r_output_append,
	r_here_doc
};

/**
 * @brief Linked list of redirections
 *
 */
typedef struct s_redirect
{
	int id;
	struct s_redirect *next;			/* Next element, or NULL. */
	int redirector;					/* Descriptor to be redirected. */
	int flags;						/* Flag value for `open'. */
	enum r_direction direction;		/* What to do with the information. */
	t_word_desc redirectee;			/* File descriptor or filename */
	char *here_doc_delim;			/* Heredoc delimeter eg. << delim. */
}	t_redirect;

typedef struct s_command{
	WORD_LIST *words;	 /* The program name, the arguments */
	t_redirect *redirects; /* Redirections to perform. */
	int exit_code;		 /* Exit status of command */
	int num_redirections;
	int fd_in;
	int fd_out;
	int stdout_old;
	int stdin_old;
	struct s_command *next;
}	t_command;

typedef struct s_shell
{
	t_command *cmds;
	int status_code;
	int fd;
	t_hash_table *env_mngr;
	char **envp;
} t_shell;

//builtins1.c
int	ft_echo(char **cmd);
int ft_cd(char **cmd);
int ft_pwd();

//builtins2.c
int exec_builtin(char **cmd);

// main.c
void sig_handler(int sig);

// exec.c
int search_absolute_path(char *cmd, char **argv);
int search_relative_path(char *cmd, char **argv);
int execute_cmd(char *cmd, char **argv, char **envp, int input);
int parse_cmd();
int cmd_executor(t_command *cmd, char *c, char **av);
int undo_redirections(t_command *cmd);

// env.c
int ft_env();
int ft_export(char *key, char *value);
int ft_unset(char *key);

// tests.c
int test_output_redirect(char *cmd, char **argv, char **envp);
int test_cmd1(char *cmd, char **argv, char **envp);
int test_cmd2(char *cmd, char **argv, char **envp);
int test_cmd3(char *cmd, char **argv, char **envp);
int piper(char *cmd, char **argv, char **envp);
int c1();
int c2();

extern t_shell zundra;
#endif