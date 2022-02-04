/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:39:32 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/04 14:45:03 by cmariot          ###   ########.fr       */
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

int	not_valid_identifier(char *identifier)
{
	print(2, "minishell: unset: '%s'", identifier);
	print(2, ": not a valid identifier.\n");
	return (global_exit_status(1));
}

int	check_unset_error(char **names, size_t i)
{
	size_t	j;

	j = 0;
	while (names[i][j] != '\0')
	{
		if (j == 0)
		{
			if (names[i][j] == '-' && names[i][j + 1] != '\0')
			{
				print(2, "minishell: unset: '%s': invalid option.\n", names[i]);
				return (global_exit_status(2));
			}
			else if (ft_isalnum(names[i][j]) == FALSE
				&& names[i][j] != '_' && names[i][j] != '$')
				return (not_valid_identifier(names[i]));
			else if (ft_isdigit(names[i][j]) == TRUE)
				return (not_valid_identifier(names[i]));
		}
		else
			if (ft_isalnum(names[i][j]) == FALSE && names[i][j] != '_'
				&& names[i][j] != '$')
				return (not_valid_identifier(names[i]));
		j++;
	}
	return (0);
}

void	remove_from_env(t_env *env, char **names, size_t i)
{
	t_env	*tmp;

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
}

t_env	*builtin_unset(t_env *env, char **names)
{
	size_t	i;

	if (*names == NULL || env == NULL)
	{
		global_exit_status(0);
		return (env);
	}
	i = 0;
	while (names[i] != NULL)
	{
		if (check_unset_error(names, i))
			return (env);
		if (ft_strcmp(env->name, names[i]) == 0)
		{
			remove_first_element(&env);
			i++;
			continue ;
		}
		remove_from_env(env, names, i);
		i++;
	}
	global_exit_status(0);
	return (env);
}
