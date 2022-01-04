/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 08:46:08 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/04 09:29:09 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_a_number(char *str_number)
{
	size_t	i;

	i = 0;
	if (str_number[0] == '-' || str_number[0] == '+')
		i++;
	if (!str_number[i])
		return (FALSE);
	while (str_number[i])
	{
		if (ft_isdigit(str_number[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	builtin_exit(t_shell *minishell, char **args)
{
	int	exit_status;

	if (args[0] == NULL)
	{
		change_global_exit_status(0);
		free_minishell(minishell);
	}
	else if (args[1] == NULL)
	{
		if (is_a_number(args[0]) == TRUE)
		{
			exit_status = ft_atoi(args[0]);
			change_global_exit_status(exit_status);
			free_minishell(minishell);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			change_global_exit_status(255);
			free_minishell(minishell);
		}
	}
	else
	{
		if (is_a_number(args[0]) == FALSE)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			change_global_exit_status(255);
			free_minishell(minishell);
		}
		else
		{
			change_global_exit_status(1);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			free_minishell(minishell);
		}
	}
}
