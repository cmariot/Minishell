/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:04:13 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 08:59:00 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Save the name and the value of char **env in a linked list
t_env	*save_env(char **env)
{
	t_env	*env_list;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		name = get_name(env[i]);
		if (name == NULL)
			break ;
		value = get_value(env[i]);
		if (value == NULL)
			free(name);
		if (value == NULL)
			break ;
		if (i == 0)
			env_list = ft_lstnew_env(name, value);
		else
			ft_lstadd_back_env(&env_list, ft_lstnew_env(name, value));
		free(name);
		free(value);
		i++;
	}
	return (env_list);
}

// Return the name of a env[i] line
char	*get_name(char *env_line)
{
	char	*name;
	int		len;
	int		i;

	len = 0;
	while (env_line[len] != '=')
		len++;
	name = ft_calloc(len + 1, sizeof(char));
	if (name == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = env_line[i];
		i++;
	}
	return (name);
}

// Return the value of a env[i] line
char	*get_value(char *env_line)
{
	char	*value;
	int		len;
	int		equal_index;
	int		i;

	len = ft_strlen(env_line);
	equal_index = 0;
	while (env_line[equal_index] != '=')
		equal_index++;
	value = ft_calloc(len - equal_index, sizeof(char));
	if (value == NULL)
		return (NULL);
	i = 0;
	while (equal_index + 1 < len)
	{
		value[i] = env_line[equal_index + 1];
		equal_index++;
		i++;
	}
	return (value);
}

// print "name=value" for all the values of the linked list t_env
void	print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->name != NULL && env->value != NULL)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
