/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:22:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/06 17:07:11 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_tilde(char **command_array, t_env *env)
{
	size_t	i;
	char	*home;
	char	*path;
	char	*new_path;
	size_t	size;

	i = 0;
	while (command_array[i] != NULL)
	{
		if (command_array[i][0] == '~')
		{
			home = get_env_value("HOME", env);
			size = ft_strlen(command_array[i]) - 1;
			path = ft_substr(command_array[i], 1, size);
			new_path = ft_strjoin(home, path);
			if (path)
				free(path);
			if (home)
				free(home);
			free(command_array[i]);
			command_array[i] = new_path;
		}
		i++;
	}
	return (0);
}

int	expansion(t_command_line *command_line, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		expand_tilde(command_line->command[i].command_array, env);
		//expand_parameters()
		//quote_removal()
		i++;
	}
	return (0);
}
