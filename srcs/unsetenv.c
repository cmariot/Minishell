/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:30:33 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 09:10:21 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Delete an element of the linked list that store 
// the name and the value of env.

// Find the previous element of the element with name = "name" in the list,
// Create a new link : previous_of_element->next_of_element
// free the name and the value, set them to NULL, and free the element

void	ft_unsetenv(t_env *env, char *name)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (ft_strcmp(tmp->name, name) == 0)
		{
			env->next = tmp->next;
			free(tmp->name);
			tmp->name = NULL;
			free(tmp->value);
			tmp->value = NULL;
			free(tmp);
			break ;
		}
		env = env->next;
	}
}
