/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 08:46:08 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/04 10:57:39 by cmariot          ###   ########.fr       */
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

void	exit_error_num_arg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	change_global_exit_status(2);
}

void	builtin_exit(t_shell *minishell, char **args)
{
	if (args[0] == NULL)
		change_global_exit_status(0);
	else if (args[1] == NULL)
	{
		if (is_a_number(args[0]) == TRUE)
			change_global_exit_status(ft_atoi(args[0]));
		else
			exit_error_num_arg(args[0]);
	}
	else
	{
		if (is_a_number(args[0]) == FALSE)
			exit_error_num_arg(args[0]);
		else
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			change_global_exit_status(1);
		}
	}
	free_minishell(minishell);
}
