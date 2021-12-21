/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/21 11:38:43 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_value(char *word, t_env *env)
{
	size_t	len;
	int		i;

	len = 0;
	while (word[i])
	{
		if (ft_isalnum(word[i]) == 0)
			break ;
		len++;
		i++;
	}
	printf("LEN = %lu\n", len);
	return (0);
}

char **expand_env_variable(char **splitted_line, t_env *env)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	while (splitted_line[i])
	{
		while (splitted_line[i][j])
		{
			if (splitted_line[i][j] == '$')
			{
				search_value(&splitted_line[i][j], env);
			}
			j++;
		}
		i++;
	}
	return (new);
}
