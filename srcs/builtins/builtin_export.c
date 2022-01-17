/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:41:01 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 21:23:20 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If the element name is in the linked list env, change its value,
// else add name and value
void	add_to_env(t_shell *minishell, t_env *env, char *name, char *value)
{
	t_env	*tmp;

	if (minishell->env == NULL)
	{
		minishell->env = ft_lstnew_env(name, value);
	}
	else
	{
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
}

int	error_invalid_identifier(char **args, size_t i)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(args[i], 2);
	ft_putstr_fd("': not a valid identifier.\n", 2);
	return (-1);
}

int	get_name_len(char **args, size_t i)
{
	int	j;

	j = 0;
	if (ft_isalpha(args[i][j]) == FALSE && args[i][j] != '_')
		return (error_invalid_identifier(args, i));
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
			return (0);
		return (error_invalid_identifier(args, i));
	}
	return (j);
}

int	builtin_export(t_shell *minishell, char **args)
{
	size_t	i;
	int		name_len;
	char	*name;
	char	*value;

	i = 0;
	while (args[i] != NULL)
	{
		name_len = get_name_len(args, i);
		if (name_len == -1)
			return (1);
		name = ft_substr(args[i], 0, name_len);
		if (name)
		{
			value = ft_strdup(args[i] + name_len + 1);
			if (value)
			{
				add_to_env(minishell, minishell->env, name, value);
				free(value);
			}
			free(name);
		}
		i++;
	}
	return (0);
}
