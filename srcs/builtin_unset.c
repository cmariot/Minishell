/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:39:32 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/05 10:42:42 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Delete an element of the linked list that store 
// the name and the value of env.

// Find the previous element of the element with name = "name" in the list,
// Create a new link : previous_of_element->next_of_element
// free the name and the value, set them to NULL, and free the element

void	remove_first_element(t_env **env)
{
	t_env	*tmp;

	tmp = (*env)->next;
	ft_lstdelone_env(*env, free);
	*env = tmp;
}

t_env *builtin_unset(t_env *env, char **names)
{
	size_t	i;
	t_env	*env_backup;
	t_env	*tmp;

	if (*names == NULL)
		return (env);
	i = 0;
	env_backup = env;
	while (names[i] != NULL)
	{
		if (*names[i] == '/')
		{
			printf("minishell: unset: '%s': not a valid identifier.\n", names[i]);
			i++;
			continue ;
		}
		if (ft_strcmp(env->name, names[i]) == 0)
		{
			remove_first_element(&env);
			i++;
			continue ;
		}
		while (env->next != NULL)
		{
			tmp = env->next;
			if (ft_strcmp(tmp->name, names[i]) == 0)
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
		env = env_backup;
		i++;
	}
	change_global_exit_status(0);
	return (env);
}
