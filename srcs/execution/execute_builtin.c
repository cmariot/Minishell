/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:07:23 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 14:24:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_not_builtin(t_simple command, int *fd_backup)
{
	restore_file_redirection(command, fd_backup[0], fd_backup[1], FALSE);
	return (global_exit_status(127));
}

int	command_is_builtin(t_shell **minishell, t_simple command)
{
	int		fd_backup[2];

	if (file_redirection(&fd_backup[0], &fd_backup[1], command))
		return (0);
	if (ft_strcmp(command.command_and_args[0], "cd") == 0)
		builtin_cd(*minishell);
	else if (ft_strcmp(command.command_and_args[0], "echo") == 0)
		builtin_echo(command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "exit") == 0)
		builtin_exit(*minishell, command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "pwd") == 0)
		builtin_pwd(*minishell, command.command_and_args[1]);
	else if (ft_strcmp(command.command_and_args[0], "env") == 0)
		builtin_env((*minishell)->env, command.command_and_args[1]);
	else if (ft_strcmp(command.command_and_args[0], "unset") == 0)
		(*minishell)->env = builtin_unset((*minishell)->env,
				command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "export") == 0)
		builtin_export(*minishell, command.command_and_args + 1);
	else
		return (its_not_builtin(command, fd_backup));
	restore_file_redirection(command, fd_backup[0], fd_backup[1], TRUE);
	return (0);
}
