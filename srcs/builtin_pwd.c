/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:58:43 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/12 12:47:32 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Try to display pwd by getting the value in the env linked list,
 * if it fails try to get the pwd value with the getcdw function,
 * else return -1. */

int	builtin_pwd(t_shell *minishell, char *first_arg)
{
	char	*pwd;

	if (first_arg != NULL)
	{
		if (first_arg[0] == '-' && first_arg[1] != '\0')
		{
			ft_putstr_fd("minishell: pwd: invalid option\n", 2);
			return (2);
		}
	}
	pwd = get_env_value("PWD", minishell->env);
	if (pwd != NULL)
	{
		ft_putstr(pwd);
		ft_putchar('\n');
		free(pwd);
		return (0);
	}
	else if (pwd == NULL)
	{
		pwd = getcwd(NULL, 255);
		ft_putstr(pwd);
		ft_putchar('\n');
		free(pwd);
		return (0);
	}
	return (1);
}
