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

typedef struct s_shell
{
	char **envp;
	int pipes[2];
	int status_code;
	int fd;
} t_shell;

t_shell zundra;

/* A structure which represents a word. */
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
};

/**
 * @brief Linked list of redirections
 *
 */
typedef struct s_redirect
{
	struct redirect *next;			/* Next element, or NULL. */
	int redirector;					/* Descriptor to be redirected. */
	int flags;						/* Flag value for `open'. */
	enum r_direction direction;	/* What to do with the information. */
	t_word_desc redirectee;			/* File descriptor or filename */
	char *here_doc_delim;				/* Heredoc delimeter eg. << delim. */
} t_redirect;

typedef struct s_command{
	WORD_LIST *words;	 /* The program name, the arguments,
							variable assignments, etc. */
	t_redirect *redirects; /* Redirections to perform. */
	int exit_code;		 /* Exit status of command */
}t_command;

//builtins1.c
int	ft_echo(char **cmd);
int ft_cd(char **cmd);
int ft_pwd();
int ft_export();
int ft_unset();

//builtins2.c
int exec_builtin(char **cmd);

// main.c
void sig_handler(int sig);

// exec.c
int search_absolute_path(char *cmd, char **argv, char **envp);
int search_relative_path(char *cmd, char **argv, char **envp);
int execute_cmd(char *cmd, char **argv, char **envp, int input);
int parse_cmd();

// tests.c
int test_output_redirect(char *cmd, char **argv, char **envp);
int test_cmd1(char *cmd, char **argv, char **envp);
int test_cmd2(char *cmd, char **argv, char **envp);
int test_cmd3(char *cmd, char **argv, char **envp);
int piper(char *cmd, char **argv, char **envp);

#endif