/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 08:46:08 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 15:35:10 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_not_num(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	global_exit_status(2);
}

void	exit_error(char *first_arg, char**args)
{
	if (*first_arg != '\0')
		exit_error_not_num(args[0]);
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		global_exit_status(1);
	}
}

void	builtin_exit(t_shell *minishell, char **args, int *backup_fd)
{
	long long	exit_status;

	if (args[0] == NULL)
		global_exit_status(0);
	else
	{
		exit_status = ft_strtoll(args[0], &(args[0]));
		if (args[1] == NULL)
		{
			if (args[0][0] != '\0')
				exit_error_not_num(args[0]);
			else
			{
				if (exit_status > 255)
					exit_status -= 256;
				global_exit_status(exit_status);
			}
		}
		else
			exit_error(args[0], args);
	}
	close(backup_fd[0]);
	close(backup_fd[1]);
	free_minishell(minishell);
}
