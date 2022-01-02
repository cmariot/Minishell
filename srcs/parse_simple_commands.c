/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:12:24 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/02 14:48:37 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_command_and_args(t_simple *command)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (command->command_array[i] != NULL)
	{
		while (command->command_array[i])
		{
			if (is_redirection(command->command_array[i]))
			{
				if (command->command_array[i + 1] != NULL)
					i += 2;
				else if (command->command_array[i + 1] == NULL)
					return (-1);
			}
			else
				command->command_and_args[j++]
					= ft_strdup(command->command_array[i++]);
		}
	}
	return (0);
}

int	get_len(char **command_array)
{
	int		len;
	size_t	i;

	i = 0;
	len = 0;
	while (command_array[i] != NULL)
	{
		if (is_redirection(command_array[i]))
		{
			if (command_array[i + 1] != NULL)
				i += 2;
			else if (command_array[i + 1] == NULL)
				return (len + 1);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	get_command_and_args(t_simple *command)
{
	int		len;

	len = get_len(command->command_array);
	if (len == 0)
		return (0);
	command->command_and_args = ft_calloc(len + 1, sizeof(char *));
	if (!command->command_and_args)
		return (-1);
	fill_command_and_args(command);
	return (0);
}

int	get_commands(t_simple *command, char **splitted_line, size_t array_index)
{
	int	i;
	int	len;

	len = 0;
	while (splitted_line[array_index + len] != NULL)
	{
		len++;
		if (ft_strcmp(splitted_line[array_index + len], "|") == 0)
			break ;
		else if (ft_strcmp(splitted_line[array_index + len], ";") == 0)
			break ;
	}
	command->command_array = ft_calloc(len + 1, sizeof(char *));
	if (!command->command_array)
		return (array_index);
	i = 0;
	while (i < len)
		command->command_array[i++] = ft_strdup(splitted_line[array_index++]);
	return (array_index + 1);
}

/* Fill the simple commands array (simple commands are
 * delimitated by '|' if there is, or all the command
 * if there isnt) :
 * count them, malloc the array of simple command, and on this array put :
 *	- all the elememt of the simple command in command
 *	- only the element which aren't linked to the
 *	redirections in command_and_args */
int	get_simple_commands(t_command_line *command_line,
		char **splitted_line, t_env *env)
{
	size_t	i;
	size_t	array_index;

	i = 0;
	while (splitted_line[i] != NULL
		&& contains_equal(splitted_line[i], env) == TRUE)
		i++;
	if (i >= 1)
		return (0);
	command_line->number_of_simple_commands
		= count_commands(command_line->splitted_line);
	command_line->command
		= ft_calloc(command_line->number_of_simple_commands + 1,
			sizeof(t_simple));
	array_index = 0;
	while (i < command_line->number_of_simple_commands)
	{
		array_index = get_commands(&command_line->command[i],
				splitted_line, array_index);
		if (get_command_and_args(&command_line->command[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
