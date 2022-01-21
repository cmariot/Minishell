/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_without_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:23:33 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/21 18:16:59 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	contains_slash_no_such_file(char *command)
{
	size_t	i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '/')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": no such file or directory.\n", 2);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

/* For all the possible path of env,
   Put a '/' and the command at the end of the path,
   Check if the command exist and if it can be execute, if ok execute it.
   If it's execute, the child process stops.
   Else try the next path.  */

int	find_correct_path(char **path_array, t_simple command, char **env,
		int *backup_fd)
{
	char	*path_with_slash;
	char	*command_path;

	if (contains_slash_no_such_file(command.command_and_args[0]) == TRUE)
		return (0);
	while (*path_array)
	{
		path_with_slash = ft_strjoin(*path_array, "/");
		command_path = ft_strjoin(path_with_slash,
				command.command_and_args[0]);
		if (path_with_slash != NULL)
			free(path_with_slash);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
			if (ft_isadirectory(command_path) == FALSE)
				if (execution(&command_path, command, env, backup_fd) == 0)
					return (0);
		if (command_path != NULL)
			free(command_path);
		(path_array)++;
	}
	return (127);
}

int	command_without_path(t_shell *minishell, t_simple command,
	char **env_array, int *backup_fd)
{
	char	*path_value;
	char	**path_array;
	bool	not_found;

	not_found = FALSE;
	if (env_array == NULL)
		return (127);
	path_value = get_env_value("PATH", minishell->env);
	if (path_value == NULL)
		return (127);
	path_array = ft_split(path_value, ':');
	if (path_array == NULL)
		not_found = TRUE;
	if (not_found == FALSE
		&& find_correct_path(path_array, command, env_array, backup_fd) == 127)
		not_found = TRUE;
	if (path_value)
		free(path_value);
	ft_free_array(path_array);
	if (not_found == TRUE)
		return (127);
	else
		return (0);
}
