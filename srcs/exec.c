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

	i = 0;
	ret = malloc(sizeof(char *) * zundra.num_of_cmds);
	while (word_lst)
	{
		ret[i] = word_lst->word->word;
		ft_printf("%s\n", ret[i]);
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
int cmd_executor(t_command *cmd, char *c, char **av)
{
	pid_t pid;
	int child_status;

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
		if (exec_builtin(av) != 2 && !search_absolute_path(c, av) && !search_relative_path(c, av))
		{
			ft_printf("minishell: command not found\n");
			return 0;
		}
	}
	zundra.status_code = WEXITSTATUS(child_status);
	return WEXITSTATUS(child_status);
}