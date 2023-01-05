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
	int redirector;					/* Descriptor to be redirected. */
	int flags;						/* Flag value for `open'. */
	enum r_direction direction;		/* What to do with the information. */
	t_word_desc redirectee;			/* File descriptor or filename */
	char *here_doc_delim;			/* Heredoc delimeter eg. << delim. */
}	t_redirect;

typedef struct s_command{
	int id;
	t_word_list *words;   /* The program name, the arguments */
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
	int num_of_cmds;
	int **pipes;
	t_dict *env_mngr;
	char **envp;
} t_shell;

t_shell zundra;

//builtins1.c
int	ft_echo(char **cmd);
int ft_cd(char **cmd);
int ft_pwd();

//builtins2.c
void ft_exit(char **);
int status_code();
int exec_builtin(char **cmd);

//cleanup.c
void free_redirects(t_redirect *redir);
void free_word_list(t_word_list *word_list);
void free_commands(t_command *cmd);

//dictionary_cleanup.c
void destroy_pair(t_pair *p);
void destroy_dict(t_dict *t);

//dictionary_utils.c
void print_pair(t_pair *p);
void print_dict(t_dict *t);
t_dict *duplicate_dictionary(t_dict *dict);
t_dict *sort_dictionary(t_dict *dict, int (*compare)(char *, char *, size_t));
char **dict_to_string_arr(t_dict *dict);

//dictionary.c
t_dict *create_dict(int s);
t_pair *retrieve_from_dict(t_dict *t, char *key);
void insert_into_dict(t_dict **t, char *key, char *value);
void remove_from_dict(t_dict *t, char *key);
t_dict *resize_dict(t_dict *t, int newCapacity);

// env.c
int ft_env();
int ft_export(char **argv);
int ft_unset(char **argv);

// main.c
void sig_handler(int sig);
void lexer(char **argv);
t_command *parser();
int executor(t_command *cmd);

// exec.c
int search_absolute_path(char *cmd, char **argv);
int search_relative_path(char *cmd, char **argv);
char **prepare_cmd_args(t_word_list *word_lst);
int cmd_executor(t_command *cmd, char **argv);

//redirect.c
int redirect_input(t_command *cmd, t_redirect *current);
int redirect_output(t_command *cmd, t_redirect *current);
int perform_IO_redirections(t_command *cmd);
void prepare_pipes();
int piper(t_command *cmd);


#endif