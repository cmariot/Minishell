/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:29:13 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/04 16:31:28 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If the element name is in the linked list env, change its value,
// else add name and value
void	add_to_env(t_env *env, char *name, char *value)
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

int	builtin_export(t_env *env, char **args)
{
	size_t	i;
	size_t	j;
	char	*name;
	char	*value;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strlen(args[i]) > 2)
		{
			//not a valid identifier
			if (args[i][0] == '-')
				return (1);
			j = 0;
			while (args[i][j] && args[i][j] != '=')
				j++;
			//not a valid identifier
			if (j == 0)
				return (1);
			name = ft_substr(args[i], 0, j);
			value = ft_strdup(args[i] + j + 1);
			if (ft_strcmp(name, "") != 0 && value)
				add_to_env(env, name, value);
			if (name)
				free(name);
			if (value)
				free(value);
		}
		i++;
	}
	return (0);
}


