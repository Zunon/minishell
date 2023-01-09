/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:11:11 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/09 19:06:44 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Allocate memory for required number of pipes & open necessary file
 * 					descriptors.
 * 					First and last pipe are dummy pipes with STDIN and STDOUT
 *
 */
static int prepare_pipes()
{
	int i;

	i = 0;
	zundra.pipes = malloc(sizeof(int *) * (zundra.num_of_cmds + 1));
	while (i <= zundra.num_of_cmds)
	{
		zundra.pipes[i] = malloc(sizeof(int) * 2);
		if (i != 0 && i != zundra.num_of_cmds)
			if (pipe(zundra.pipes[i]) == -1)
			{
				perror("PARENT - Failed to create pipe: ");
				return (EXIT_FAILURE);
			}
		i++;
	}
	zundra.pipes[0][0] = STDIN_FILENO;
	zundra.pipes[0][1] = STDOUT_FILENO;
	zundra.pipes[zundra.num_of_cmds][0] = STDIN_FILENO;
	zundra.pipes[zundra.num_of_cmds][1] = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}

/**
 * @brief			Close all pipes safely from the parent process
 *
 */
static int close_parent_pipes()
{
	int i;

	i = 1;
	while (i < zundra.num_of_cmds)
	{
		// printf("%d", i);
		if (close(zundra.pipes[i][0]) == -1)
		{
			ft_printf("closing %d\n", zundra.pipes[i][0]);
			perror("PARENT - Error while closing pipe read end: ");
			return (EXIT_FAILURE);
		}
		if (close(zundra.pipes[i][1]) == -1)
		{
			ft_printf("closing %d\n", zundra.pipes[i][1]);
			perror("PARENT - Error while closing pipe write end: ");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief			Get the number of words in the given word list.
 * 					Used to help deicde how many bytes of memory to allocate for
 * 					the argument list of a command
 *
 * @param word_lst 	t_word_lst variable to get the size of
 * @return int		Number of strings present (Excluding NULL element)
 */
static int get_word_list_length(t_word_list *word_lst)
{
	int i;

	i = 0;
	while (word_lst)
	{
		word_lst = word_lst->next;
		i++;
	}
	return (i);
}

/**
 * @brief			Prepare the arguments of the current command as a char**
 * 					for easy execution by execve
 *
 * @param word_lst	linked list of words
 * @return char**	argv for the currently executing command
 */
static char **prepare_cmd_args(t_word_list *word_lst)
{
	char **ret;
	int i;

	if (!word_lst)
		return (NULL);
	i = 0;
	ret = malloc(sizeof(char *) * (1 + get_word_list_length(word_lst)));
	while (word_lst)
	{
		ret[i] = word_lst->curr_word_desc->word;
		word_lst = word_lst->next;
		i++;
	}
	ret[i] = NULL;
	return ret;
}

/**
 * @brief			Phase 3 of the shell - execution of commands takes place here
 *
 * @param cmd		Linked list of commands to execute in the current pipeline
 * @return int		Status code of last executed command
 */
int executor(t_command *cmd)
{
	t_command *iterator;
	int status;

	iterator = cmd;
	if (!cmd)
		return (EXIT_SUCCESS);
	zundra.stdout_old = dup(STDOUT_FILENO);
	prepare_pipes();
	while (iterator)
	{
		zundra.cmds = iterator;
		iterator->argv = prepare_cmd_args(iterator->words);
		exec_simple_cmd(iterator, iterator->argv);
		iterator = iterator->next;
	}
	close(zundra.stdout_old);
	close_parent_pipes();
	waitpid(zundra.last_child_pid, &status, 0);
	zundra.status_code = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > -1)
		;
	return (zundra.status_code);
}