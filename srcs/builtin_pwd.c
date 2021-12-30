/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:58:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/30 19:00:12 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Try to display pwd by getting the value in the env linked list,
 * if it fails try to get the pwd value with the getcdw function,
 * else return -1. */

int	pwd_builtin(t_shell *minishell)
{
	char	*pwd;

	pwd = get_env_value("PWD", minishell->env);
	if (pwd != NULL)
	{
		ft_putstr(pwd);
		ft_putstr("\n");
		free(pwd);
		return (0);
	}
	else if (pwd == NULL)
	{
		pwd = getcwd(NULL, 255);
		ft_putstr(pwd);
		ft_putstr("\n");
		free(pwd);
		return (0);
	}
	return (-1);
}
