/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:09:46 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 18:24:43 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	command_not_found(char *command)
{
	if (ft_isadirectory(command) == TRUE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": is a directory\n", 2);
		global_exit_status(126);
	}
	else if (access(command, F_OK) == 0 && access(command, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": permission denied\n", 2);
		global_exit_status(126);
	}
	else if (access(command, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		global_exit_status(127);
	}
}

void	execute_simple_command(t_shell *minishell, t_simple command,
		int *backup_fd)
{
	if (file_redirection(command))
		return ;
	if (command.command_and_args == NULL || command.command_and_args[0] == NULL)
		return (remove_heredocs(command));
	if (command_is_builtin(&minishell, command, backup_fd) != 127)
	{
		restore_file_redirection(command, backup_fd[STDIN], backup_fd[STDOUT]);
		return ;
	}
	minishell->env_array = envlist_to_array(minishell->env);
	if (command_in_path(minishell, command, backup_fd) == 127)
		if (command_with_absolute_path(command, minishell, backup_fd) == 127)
			command_not_found(command.command_and_args[0]);
	restore_file_redirection(command, backup_fd[STDIN], backup_fd[STDOUT]);
	return ;
}
