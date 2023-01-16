/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:51:12 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 18:37:26 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int			exec_simple_cmd(t_command *cmd);

/**
 * @brief				Update the shell level of minishell on execution at startup
 * 						Note: If SHLVL is unset by calling process, SHLVL is exported
 * 						with default value 1
 * @param env_manager	Environment variable manager dictionary
 */
static void	update_shlvl(t_dict *env_manager)
{
	t_pair	*shlvl;
	char	*temp;

	shlvl = retrieve_from_dict(env_manager, "SHLVL");
	if (!shlvl)
	{
		insert_into_dict(&env_manager, "SHLVL", "1");
		return ;
	}
	temp = shlvl->value;
	shlvl->value = ft_itoa(ft_atoi(temp) + 1);
	free(temp);
}

/**
 * @brief				Helper function to find the index of a specific character in a
 * 						string if it exists
 *
 * @param s				String to search through
 * @param c				Character to look for
 * @return int			Index of occurance OR -1 if not found
 */
int	find_pos(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief				Function to generate an envrionment variable manager from
 * 						the envrionment variables passed into minishell by the
 * 						calling process.
 *
 * @param envp			Pointer to array of characters with all variables
 * @return t_dict*		Pointer to generated dictionary of environment variables
 */
t_dict	*generate_env_manager(char **envp)
{
	t_dict	*env_manager;
	int		i;
	char	*key;
	char	*value;
	int		pos;

	i = 0;
	env_manager = create_dict(50);
	while (envp[i])
	{
		pos = find_pos(envp[i], '=');
		if (pos != -1)
		{
			key = ft_substr(envp[i], 0, pos);
			value = ft_substr(envp[i], pos + 1, -1);
			insert_into_dict(&env_manager, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	update_shlvl(env_manager);
	g_krsh.envp = dict_to_string_arr(env_manager);
	return (env_manager);
}

void	ext_not_found(t_command *cmd)
{
	if (exec_builtin(cmd) == EXIT_FAILURE
		&& search_absolute_path(cmd->argv) == EXIT_FAILURE
		&& search_relative_path(cmd->argv) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, " :Command not found\n", 19);
		exit(ERROR_COMMAND_NOT_FOUND);
	}
}

/**
 * @brief			Function to execute a simple command
 *
 * @param cmd		Command struct to execute
 * @param c			command as a char *
 * @param av		command and its parameters for use by execve
 * @return int		Status code of child process after execution
 */
int	exec_simple_cmd(t_command *cmd)
{
	pid_t	pid;

	if (exec_single_builtin(cmd) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error while forking\n");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (perform_io_redirections(cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ext_not_found(cmd);
		exit(g_krsh.status_code);
	}
	else
		signal(SIGINT, SIG_IGN);
	g_krsh.last_child_pid = pid;
	return (EXIT_SUCCESS);
}
