/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:41:01 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/20 19:21:24 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	export_without_args(t_env *env)
{
	while (env != NULL)
	{
		if (env->name && env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
	return (global_exit_status(0));
}

int	export(t_shell *minishell, char **args, size_t i, size_t name_len)
{
	char	*name;
	char	*value;

	name = ft_substr(args[i], 0, name_len);
	if (name == NULL)
		return (global_exit_status(1));
	value = ft_strdup(args[i] + name_len + 1);
	if (!value)
	{
		free(name);
		return (0);
	}
	add_to_env(minishell, minishell->env, name, value);
	free(value);
	free(name);
	return (0);
}

int	builtin_export(t_shell *minishell, char **args)
{
	size_t	i;
	int		name_len;

	i = 0;
	if (args[i] == NULL)
		return (export_without_args(minishell->env));
	while (args[i] != NULL)
	{
		name_len = get_name_len(args, i);
		if (name_len == -1)
			return (global_exit_status(1));
		else if (name_len == 0)
		{
			i++;
			continue ;
		}
		if (export(minishell, args, i, name_len) == 1)
			return (1);
		i++;
	}
	return (global_exit_status(0));
}
