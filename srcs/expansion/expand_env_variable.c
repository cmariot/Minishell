/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:36:18 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 13:36:53 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* For all the str of the array, search if an environement expansion 
 * is required.*/

int	expand_env_variable(char **array, t_env *env)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		if (search_dollar_in_str(&array[i], env))
		{
			remove_from_array(array, i);
			continue ;
		}
		i++;
	}
	return (0);
}
