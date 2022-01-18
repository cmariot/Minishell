/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:07:23 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 17:15:41 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_is_builtin(t_shell **minishell, t_simple command, int *backup_fd)
{
	if (ft_strcmp(command.command_and_args[0], "cd") == 0)
		builtin_cd(*minishell);
	else if (ft_strcmp(command.command_and_args[0], "echo") == 0)
		builtin_echo(command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "exit") == 0)
		builtin_exit(*minishell, command.command_and_args + 1, backup_fd);
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
		return (global_exit_status(127));
	return (0);
}
