/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 20:27:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			free(splitted_line[i]);
			splitted_line[i] = value;
		}
		i++;
	}
}
