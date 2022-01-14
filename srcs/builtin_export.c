/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:41:01 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/14 16:20:03 by cmariot          ###   ########.fr       */
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

int	builtin_export(t_shell *minishell, char **args)
{
	size_t	i;
	size_t	j;
	char	*name;
	char	*value;

	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		if (ft_isalpha(args[i][j]) == FALSE && args[i][j] != '_')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier.\n", 2);
			return (1);
		}
		j++;
		while (args[i][j] != '\0' && args[i][j] != '=')
		{
			if (args[i][j] == '_' || ft_isalnum(args[i][j]) == TRUE)
				j++;
			else
				break ;
		}
		if (args[i][j] != '=')
		{
			if (args[i][j] == '\0')
			{
				i++;
				continue ;
			}
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier.\n", 2);
			return (1);
		}
		name = ft_substr(args[i], 0, j);
		if (name)
		{
			value = ft_strdup(args[i] + j + 1);
			if (value)
			{
				if (minishell->env == NULL)
					minishell->env = ft_lstnew_env(name, value);
				else
					add_to_env(minishell->env, name, value);
				free(value);
			}
			free(name);
		}
		i++;
	}
	return (0);
}
