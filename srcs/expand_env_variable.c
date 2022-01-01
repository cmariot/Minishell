/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 21:28:31 by cmariot          ###   ########.fr       */
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

// a implementer les " et les ' : comportement bash a
//prendre comme reference mais voir comment ca fonctionne
void	expand_env_variable(char **splitted_line, t_env *env)
{
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (splitted_line[i])
	{
		if (splitted_line[i][0] == '$')
		{
			name = ft_strdup(splitted_line[i] + 1);
			value = get_env_value(name, env);
			if (value != NULL)
			{
				free(splitted_line[i]);
				splitted_line[i] = value;
			}
			else
			{
				remove_from_array(splitted_line, i);
				i--;
			}
		}
		i++;
	}
}
