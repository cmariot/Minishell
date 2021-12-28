/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:12:24 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/28 17:08:27 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* count_commands() returns the number of simple commands in the line
 * A simple command is a sequence of optional variable assignments
 * followed by blank-separated words and redirections,
 * and terminated by a control operator.
 * 
 * The first word specifies the command to be executed, and is passed as
 * argument zero. The remaining words are passed as arguments to the invoked
 * command. The return value of a simple command is its exit status,
 * or 128+n if the command is terminated by signal n. */
size_t	count_commands(char **splitted_line)
{
	int	number_of_commands;
	int	i;

	i = 0;
	number_of_commands = 1;
	while (splitted_line[i])
	{
		if (ft_strcmp(splitted_line[i], "|") == 0)
			number_of_commands++;
		else if (ft_strcmp(splitted_line[i], ";") == 0)
			break ;
		i++;
	}
	return (number_of_commands);
}

int	fill_commands(t_simple *command, char **splitted_line, size_t array_index)
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
	command->command_array = ft_calloc(len + 1, sizeof(char **));
	if (!command->command_array)
		return (array_index);
	i = 0;
	while (i < len)
	{
		command->command_array[i] = ft_strdup(splitted_line[array_index++]);
		i++;
	}
	return (array_index + 1);
}

int	get_len(char **command_array)
{
	int		len;
	size_t	i;

	len = 0;
	i = 0;
	while (command_array[i])
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

int	fill_command_and_args(t_simple *command)
{
	int		len;
	size_t	i;
	size_t	j;

	len = get_len(command->command_array);
	if (len == 0)
	{
		printf("Gerer les redirections sans commande ici\n");
		return (-1);
	}
	command->command_and_args = ft_calloc(len + 1, sizeof(char *));
	if (!command->command_and_args)
		return (-1);
	i = 0;
	j = 0;
	while (command->command_array[i])
	{
		if (is_redirection(command->command_array[i]))
		{
			if (command->command_array[i + 1] != NULL)
				i += 2;
			else if (command->command_array[i + 1] == NULL)
				return (0);
		}
		else
			command->command_and_args[j++]
				= ft_strdup(command->command_array[i++]);
	}
	return (0);
}

int	get_simple_commands(t_command_line *command_line, char **splitted_line)
{
	size_t	i;
	size_t	array_index;

	command_line->number_of_simple_commands
		= count_commands(command_line->splitted_line);
	command_line->command
		= ft_calloc(command_line->number_of_simple_commands + 1,
			sizeof(t_simple));
	array_index = 0;
	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		array_index = fill_commands(&command_line->command[i],
				splitted_line, array_index);
		if (fill_command_and_args(&command_line->command[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
