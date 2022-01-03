/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/03 16:06:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_array(char **splitted_line, int i)
{
	int	j;

	if (splitted_line[i + 1] == NULL)
	{
		free(splitted_line[i]);
		splitted_line[i] = NULL;
		return ;
	}
	j = i;
	while (splitted_line[j + 1] != NULL)
	{
		free(splitted_line[j]);
		splitted_line[j] = ft_strdup(splitted_line[j + 1]);
		j++;
	}
	free(splitted_line[j]);
	splitted_line[j] = NULL;
}

size_t	get_env_name_len(char *name, size_t index)
{
	size_t	len;

	len = 0;
	while (name[index] != '\0' && name[index] != '$')
	{
		len++;
		index++;
	}
	return (len);
}

// a implementer les " et les ' : comportement bash a
//prendre comme reference mais voir comment ca fonctionne
void	expand_env_variable(char **splitted_line, t_env *env)
{
	//fonction a revoir, surement plein de leaks ...
	char	*value;
	char	*name;
	size_t	len;
	size_t	index;
	int		i;
	char	*tmp;

	i = 0;
	while (splitted_line[i])
	{
		name = NULL;
		index = 0;
		if (splitted_line[i][0] == '$' && splitted_line[i][1] != '\0')
		{
			while (splitted_line[i][index] != '\0')
			{
				len = get_env_name_len(splitted_line[i] + 1, index);
				if (name == NULL)
				{
					name = ft_substr(splitted_line[i], index + 1, len);
					if (ft_strcmp("?", name) == 0)
						value = ft_itoa(return_global_exit_status());
					else
						value = get_env_value(name, env);
				}
				else
				{
					free(name);
					name = ft_substr(splitted_line[i], index, len + 1);
					if (ft_strcmp("?", name) == 0)
						tmp = ft_itoa(return_global_exit_status());
					else
						tmp = get_env_value(name, env);
					value = ft_strjoin(value, tmp);
					if (tmp)
						free(tmp);
				}
				if (splitted_line[i][index + len + 1] == '\0')
					break ;
				index += len + 2;
			}
			if (name)
				free(name);
			if (value)
			{
				free(splitted_line[i]);
				splitted_line[i] = value;
			}
			else
			{
				remove_from_array(splitted_line, i);
				continue ;
			}
		}
		i++;
	}
}
