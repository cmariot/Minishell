/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:39:32 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/10 19:47:00 by cmariot          ###   ########.fr       */
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

t_env	*builtin_unset(t_env *env, char **names)
{
	size_t	i;
	size_t	j;
	t_env	*env_backup;
	t_env	*tmp;
	bool	error;

	if (*names == NULL || env == NULL)
	{
		change_global_exit_status(0);
		return (env);
	}
	i = 0;
	error = FALSE;
	env_backup = env;
	while (names[i] != NULL)
	{
		j = 0;
		while (names[i][j] != '\0')
		{
			if (i == 0 && names[i][j] == '-' && names[i][j + 1] != '\0')
			{
				ft_putstr_fd("minishell: unset: '", 2);
				ft_putstr_fd(names[i], 2);
				ft_putstr_fd("': invalid option.\n", 2);
				change_global_exit_status(2);
				return (env);
			}
			else if (ft_isalnum(names[i][j]) == FALSE && names[i][j] != '_')
			{
				ft_putstr_fd("minishell: unset: '", 2);
				ft_putstr_fd(names[i], 2);
				ft_putstr_fd("': not a valid identifier.\n", 2);
				error = TRUE;
				break ;
			}
			j++;
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
	if (error == FALSE)
		change_global_exit_status(0);
	if (error == TRUE)
		change_global_exit_status(1);
	return (env);
}
