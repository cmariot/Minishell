/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:07:23 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 16:18:32 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_redirection(int *fd, int *fd_backup, t_simple command,
	int fd_output)
{
	fd_backup[0] = dup(fd[STDIN]);
	fd_backup[1] = dup(fd[STDOUT]);
	input_redirection(command, TRUE);
	output_redirection(command, fd_output);
}

void	restore_builtin_redirection(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN);
	dup2(stdout_backup, STDOUT);
	close(stdin_backup);
	close(stdout_backup);
}

int	its_not_builtin(int *fd_backup)
{
	restore_builtin_redirection(fd_backup[0], fd_backup[1]);
	return (global_exit_status(127));
}

int	command_is_builtin(t_shell **minishell, t_simple command, int *fd,
	int fd_output)
{
	int		fd_backup[2];

	builtin_redirection(fd, fd_backup, command, fd_output);
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
		return (its_not_builtin(fd_backup));
	restore_builtin_redirection(fd_backup[0], fd_backup[1]);
	return (0);
}
