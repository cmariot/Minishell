/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:23:08 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 18:53:17 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command_in_current_directory(char *command_path, t_simple command,
		t_shell *minishell, int *backup_fd)
{
	if (access(command_path + 2, F_OK) == 0
		&& access(command_path + 2, X_OK) == 0)
		if (ft_isadirectory(command_path + 2) == FALSE)
			if (!execution(&command_path, command, minishell, backup_fd))
				return (0);
	return (1);
}

/* For the command with absolut path, like './minishell' or '/bin/ls' */

int	command_with_absolute_path(t_simple command, t_shell *minishell,
	int *backup_fd)
{
	char	*command_path;

	if (contains_slash(command.command_and_args[0]) == FALSE)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		global_exit_status(127);
		return (1);
	}
	command_path
		= ft_strdup(command.command_and_args[0]);
	if (ft_strlen(command_path) > 2 && command_path[0] == '.'
		&& command_path[0] == '/')
	{
		if (!execute_command_in_current_directory(command_path,
				command, minishell, backup_fd))
			return (0);
	}
	else if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		if (ft_isadirectory(command_path) == FALSE)
			if (!execution(&command_path, command, minishell, backup_fd))
				return (0);
	if (command_path != NULL)
		free(command_path);
	return (127);
}
