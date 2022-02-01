/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 08:46:08 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/31 18:27:47 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_not_num(char *arg, t_shell *minishell)
{
	print(2, "minishell: exit: %s", arg);
	print(2, ": numeric argument required\n");
	global_exit_status(2);
	free_minishell(minishell);
}

void	exit_error(char *first_arg, char**args, t_shell *minishell)
{
	if (*first_arg != '\0')
	{
		exit_error_not_num(args[0], minishell);
		free_minishell(minishell);
	}
	else
	{
		print(2, "minishell: exit: too many arguments\n");
		global_exit_status(1);
	}
}

void	builtin_exit(t_shell *minishell, char **args, int *backup_fd)
{
	long long	exit_status;
	char		*first_arg;

	close(backup_fd[0]);
	close(backup_fd[1]);
	if (args[0] == NULL)
		free_minishell(minishell);
	first_arg = args[0];
	exit_status = ft_strtoll(args[0], &first_arg);
	if (args[1] == NULL)
	{
		if (*first_arg != '\0')
			exit_error_not_num(args[0], minishell);
		else
		{
			if (exit_status > 255)
				exit_status -= 256;
			global_exit_status(exit_status);
			free_minishell(minishell);
		}
	}
	else
		exit_error(first_arg, args, minishell);
}
