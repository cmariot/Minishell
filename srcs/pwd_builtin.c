/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:58:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/30 15:59:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_shell *minishell)
{
	char	*pwd;

	pwd = get_env_value("PWD", minishell->env);
	if (pwd != NULL)
	{
		ft_putstr(pwd);
		ft_putstr("\n");
		free(pwd);
	}
}
