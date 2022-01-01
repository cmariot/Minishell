/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:03:11 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 13:21:50 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print "name=value" for all the values of the linked list t_env
void	env_builtin(t_env *env)
{
	while (env)
	{
		ft_putstr(env->name);
		write(1, "=", 1);
		ft_putstr(env->value);
		write(1, "\n", 1);
		env = env->next;
	}
}

// If the element name is in the linked list env, change its value,
// else add name and value
void	setenv_builtin(t_env *env, char *name, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = tmp;
	ft_lstadd_back_env(&env, ft_lstnew_env(name, value));
}

// Delete an element of the linked list that store 
// the name and the value of env.

// Find the previous element of the element with name = "name" in the list,
// Create a new link : previous_of_element->next_of_element
// free the name and the value, set them to NULL, and free the element

void	unsetenv_builtin(t_env *env, char *name)
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

void	save_in_env(char *str, size_t i, t_env *env)
{
	char	*name;
	char	*value;

	name = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 1);
	setenv_builtin(env, name, value);
	free(name);
	free(value);
}

/* During the parsing, if an argument conains an equal -> save in env */
bool	contains_equal(char *str, t_env *env)
{
	int	i;
	int	min_len;

	min_len = ft_strlen(str) - 2;
	if (min_len <= 0)
		return (FALSE);
	i = 1;
	while (i <= min_len)
	{
		if (str[i] == '=')
		{
			save_in_env(str, i, env);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
