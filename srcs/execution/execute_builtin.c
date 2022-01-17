/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:07:23 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 22:44:19 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_redirection(int *fd_backup, t_simple command)
{
	if (command.number_of_redirections == 0)
		return ;
	fd_backup[0] = dup(STDIN);
	fd_backup[1] = dup(STDOUT);
	input_redirection(command, FALSE);
	output_redirection(command);
}

void	restore_builtin_redirection(t_simple command,
	int stdin_backup, int stdout_backup)
{
	if (command.number_of_redirections == 0)
		return ;
	dup2(stdin_backup, STDIN);
	dup2(stdout_backup, STDOUT);
	close(stdin_backup);
	close(stdout_backup);
}

int	its_not_builtin(t_simple command, int *fd_backup)
{
	restore_builtin_redirection(command, fd_backup[0], fd_backup[1]);
	return (global_exit_status(127));
}

int	command_is_builtin(t_shell **minishell, t_simple command)
{
	int		fd_backup[2];

	builtin_redirection(fd_backup, command);
	if (ft_strcmp(command.command_and_args[0], "cd") == 0)
		global_exit_status(builtin_cd(*minishell));
	else if (ft_strcmp(command.command_and_args[0], "echo") == 0)
		global_exit_status(builtin_echo(command.command_and_args + 1));
	else if (ft_strcmp(command.command_and_args[0], "exit") == 0)
		builtin_exit(*minishell, command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "pwd") == 0)
		global_exit_status(builtin_pwd(*minishell,
				command.command_and_args[1]));
	else if (ft_strcmp(command.command_and_args[0], "env") == 0)
		global_exit_status(builtin_env((*minishell)->env,
				command.command_and_args[1]));
	else if (ft_strcmp(command.command_and_args[0], "unset") == 0)
		(*minishell)->env = builtin_unset((*minishell)->env,
				command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "export") == 0)
		global_exit_status(builtin_export(*minishell,
				command.command_and_args + 1));
	else
		return (its_not_builtin(command, fd_backup));
	restore_builtin_redirection(command, fd_backup[0], fd_backup[1]);
	return (0);
}
