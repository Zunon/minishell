/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:09:10 by rriyas            #+#    #+#             */
/*   Updated: 2023/01/05 16:24:06 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/dictionary.h"

int test_env()
{
	return 0;
}

int test_export_no_arg()
{
	return 0;
}

int test_export_with_args()
{
	return 0;
}

int test_unset_no_args()
{
	return 0;
}

int test_unset_existing_var()
{
	return 0;
}

int test_unset_missing_var()
{
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	test_env();
	test_export_no_arg();
	test_export_with_args();
	test_unset_no_args();
	test_unset_existing_var();
	test_unset_missing_var();
	return 0;
}