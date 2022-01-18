/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:23:08 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 18:06:14 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command_in_current_directory(char *command_path, t_simple command,
		char **env, int *backup_fd)
{
	if (access(command_path + 2, F_OK) == 0
		&& access(command_path + 2, X_OK) == 0)
		if (ft_isadirectory(command_path + 2) == FALSE)
			if (!execution(&command_path, command, env, backup_fd))
				return (0);
	return (1);
}

bool	contains_slash(char **command_path)
{
	size_t	len;

	len = 0;
	while ((*command_path)[len] != '/' && (*command_path)[len])
		len++;
	if (len == ft_strlen(*command_path))
	{
		free(*command_path);
		return (FALSE);
	}
	return (TRUE);
}

/* For the command with absolut path, like './minishell' or '/bin/ls' */

int	command_with_absolute_path(t_simple command, char **env, int *backup_fd)
{
	char	*command_path;

	command_path
		= ft_strdup(command.command_and_args[0]);
	if (contains_slash(&command_path) == FALSE)
		return (127);
	if (ft_strlen(command_path) > 2 && command_path[0] == '.'
		&& command_path[0] == '/')
	{
		if (!execute_command_in_current_directory(command_path,
				command, env, backup_fd))
			return (0);
	}
	else if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		if (ft_isadirectory(command_path) == FALSE)
			if (!execution(&command_path, command, env, backup_fd))
				return (0);
	if (command_path != NULL)
		free(command_path);
	return (127);
}
