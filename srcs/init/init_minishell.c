/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:07:04 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 19:00:19 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the name of a env[i] line
char	*get_name_in_env(char *env_line)
{
	char	*name;
	int		len;

	len = 0;
	while (env_line[len] != '=' && env_line[len])
		len++;
	name = ft_substr(env_line, 0, len);
	return (name);
}

// Return the value of a env[i] line
char	*get_value_in_env(char *env_line)
{
	char	*value;
	int		len;
	int		equal_index;

	len = ft_strlen(env_line);
	equal_index = 0;
	while (env_line[equal_index] != '=' && env_line[equal_index])
		equal_index++;
	value = ft_substr(env_line, equal_index + 1, len - 1);
	return (value);
}

// Save the name and the value of char **env in a linked list
t_env	*save_env(char **env)
{
	t_env	*env_list;
	char	*name;
	char	*value;

	env_list = NULL;
	while (*env != NULL)
	{
		name = get_name_in_env(*env);
		if (!name)
			continue ;
		value = get_value_in_env(*env);
		if (env_list == NULL)
			env_list = ft_lstnew_env(name, value);
		else
			ft_lstadd_back_env(&env_list, ft_lstnew_env(name, value));
		free(name);
		free(value);
		env++;
	}
	return (env_list);
}

// Initialize the value of the structure to default value
void	init_minishell(t_shell *minishell, char **env)
{
	if (env != NULL)
		minishell->env = save_env(env);
	else
		minishell->env = NULL;
	minishell->command_line.line = NULL;
	minishell->command_line.splitted_line = NULL;
	minishell->command_line.number_of_simple_commands = 0;
	minishell->command_line.command = NULL;
	minishell->env_array = NULL;
}
