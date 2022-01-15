/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:58:43 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/15 17:12:30 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Try to display pwd by getting the value in the env linked list,
 * if it fails try to get the pwd value with the getcdw function,
 * else return -1. */

int	error_invalid_option(void)
{
	ft_putstr_fd("minishell: pwd: invalid option\n", 2);
	return (2);
}

int	builtin_pwd(t_shell *minishell, char *first_arg)
{
	char	*pwd;

	if (first_arg != NULL)
		if (first_arg[0] == '-' && first_arg[1] != '\0')
			return (error_invalid_option());
	pwd = get_env_value("PWD", minishell->env);
	if (pwd != NULL)
	{
		ft_putstr(pwd);
		ft_putchar('\n');
		free(pwd);
		return (0);
	}
	else
	{
		pwd = getcwd(NULL, 255);
		ft_putstr(pwd);
		ft_putchar('\n');
		free(pwd);
		return (0);
	}
}
