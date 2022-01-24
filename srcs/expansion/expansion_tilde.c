/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:10:13 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/24 16:53:30 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_tilde(char **str, char **home)
{
	size_t	size;
	char	*path;
	char	*new_path;

	size = ft_strlen(*str) - 1;
	path = ft_substr(*str, 1, size);
	free(*str);
	if (!path)
	{
		free(*home);
		return (1);
	}
	new_path = ft_strjoin(*home, path);
	free(path);
	free(*home);
	if (!new_path)
		return (1);
	*str = new_path;
	return (0);
}

int	expand_tilde(char **command_array, t_env *env)
{
	size_t	i;
	char	*home;

	i = 0;
	while (command_array[i] != NULL)
	{
		if (command_array[i][0] == '~')
		{
			home = get_env_value("HOME", env);
			if (!home)
				return (1);
			if (replace_tilde(&(command_array[i]), &home))
				return (1);
		}
		i++;
	}
	return (0);
}
