/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:07:04 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/25 11:43:31 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the name of a env[i] line
char	*get_name_in_env(char *env_line)
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
char	*get_value_in_env(char *env_line)
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

// Save the name and the value of char **env in a linked list
t_env	*save_env(char **env)
{
	t_env	*env_list;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	if (!env)
	{
		//a verifier ... mais on doit gerer le cas
		env_list = ft_lstnew_env(NULL, NULL);
		return (env_list);
	}
	while (env[i])
	{
		name = get_name_in_env(env[i]);
		if (name == NULL)
			break ;
		value = get_value_in_env(env[i]);
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

// Initialize the value of the structure to default value
void	init_minishell(t_shell *minishell, char **env)
{
	minishell->env = save_env(env);
	minishell->command_line.line = NULL;
	minishell->command_line.splitted_line = NULL;
	minishell->command_line.number_of_simple_commands = 0;
	minishell->command_line.command = NULL;
}
