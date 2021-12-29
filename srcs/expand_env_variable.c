/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 12:33:17 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a implementer les " et les ' : comportement bash a
//prendre comme reference mais voir comment ca fonctionne
void	expand_env_variable(char ***splitted_line, t_env *env)
{
	char	*new_value;
	int		i;
	int		j;

	i = 0;
	while ((*splitted_line)[i])
	{
		j = 0;
		while ((*splitted_line)[i][j])
		{
			if ((*splitted_line)[i][j] == '$')
			{
				new_value = get_env_value((*splitted_line)[i] + j, env);
				if (new_value != NULL)
				{
					free(*splitted_line[i]);
					(*splitted_line)[i] = new_value;
					break ;
				}
			}
			j++;
		}
		i++;
	}
}
