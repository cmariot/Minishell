/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:10:13 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/07 14:12:06 by cmariot          ###   ########.fr       */
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
