/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:54:26 by rriyas            #+#    #+#             */
/*   Updated: 2022/07/26 14:22:28 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/**
 * @brief Function to calculate the length of a string
 *
 * @param str - string to find the length of
 * @return int - the number of characters in the string
 */
int ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
/**
 * @brief Function to handle various signals in the program
 *
 * @param sig - signal recieved by the program
 */
void	sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

int main(int argc, char **argv)
{
	char *s;

	signal(SIGINT, &sig_handler);
	while (2)
	{
		s = readline(">");
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
	return (0);
}