/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:35:27 by rriyas            #+#    #+#             */
/*   Updated: 2022/10/22 20:36:59 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief			Find and execute commands from the PATH environment variable
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int search_absolute_path(char *cmd, char **argv)
{
	int i;
	DIR *d;
	struct dirent *dir;
	char *exec_path;
	char *path = getenv("PATH");
	char **paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		d = opendir(paths[i]);
		dir = readdir(d);
		while (dir)
		{
			if (ft_strncmp(dir->d_name, cmd, 255) == 0)
			{
				exec_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
				if (execve(exec_path, argv, zundra.envp) == -1)
					perror("Error during execution of program!");
			}
			dir = readdir(d);
		}
		closedir(d);
		i++;
	}
	return 0;
}

/**
 * @brief 			Find and execute commands based on current directory (Eg. run executables)
 *
 * @param cmd		The command to be executed
 * @param argv		The parameters to the command
 * @param envp		Environment variables
 * @return int		Status code of execution (1 on SUCCESS, 0 on 'CMD NOT FOUND')
 */
int search_relative_path(char *cmd, char **argv)
{
	if (ft_strchr(cmd, '/') != 0 && execve(cmd, argv, zundra.envp) == -1)
		ft_printf("Error during execution of program!");
	return 0;
}

/**
 * @brief			Prepare the arguments of the current command as a char**
 * 					for easy execution by execve
 *
 * @param word_lst	linked list of words
 * @return char**	argv for the currently executing command
 */
char **prepare_cmd_args(t_word_list *word_lst)
{
	char **ret;
	int i;

	if (!word_lst)
		return (NULL);
	i = 0;
	ret = malloc(sizeof(char *) * (3));
	while (word_lst)
	{
		ft_printf("%d", i);
		ret[i] = word_lst->curr_word_desc->word;
		word_lst = word_lst->next;
		i++;
	}
	ret[i] = NULL;
	return ret;
}

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
 */
int cmd_executor(t_command *cmd, char **argv)
{
	pid_t pid;
	int child_status;

	if (!cmd->next && exec_builtin(cmd, argv) != 2)
		return 0;
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return -1;
	}
	if (pid == 0)
	{
		if (perform_IO_redirections(cmd) == -1)
			return -1;
		if (exec_builtin(cmd, argv) == 2 && !search_absolute_path(argv[0], argv) && !search_relative_path(argv[0], argv))
		{
			ft_printf("minishell: command not found\n");
			return 0;
		}
	}
	zundra.status_code = WEXITSTATUS(child_status);
	return WEXITSTATUS(child_status);
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
	int i;

	iterator = cmd;
	if (!cmd)
		return (0);
	prepare_pipes();
	while (iterator)
	{
		zundra.cmds = iterator;
		iterator->argv = prepare_cmd_args(iterator->words);
		cmd_executor(iterator, iterator->argv);
		iterator = iterator->next;
	}
	i = 0;
	while (i < zundra.num_of_cmds)
	{
		wait(0);
		i++;
	}
	free_commands(cmd);
	return status_code();
}