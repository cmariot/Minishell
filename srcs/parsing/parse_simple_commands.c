/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:12:24 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 13:25:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands_len(char *str)
{
	size_t	i;
	char	quote_type;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote_type = str[i];
			i++;
			while (str[i] != quote_type)
				i++;
		}
		if (str[i] == '|' && str[i + 1] == '\0')
			return (0);
		else if (str[i] == '|' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (-1);
}

int	get_commands(t_simple *command, char **splitted_line, size_t array_index,
	int j)
{
	int	len;
	int	ret;

	len = 0;
	ret = 0;
	while (splitted_line[array_index + len] != NULL)
	{
		ret = count_commands_len(splitted_line[array_index + len]);
		if (ret == 0 || ret == 1)
			break ;
		len++;
	}
	command->command_array = ft_calloc(len + 1, sizeof(char *));
	if (!command->command_array)
		return (-1);
	j = 0;
	while (j++ < len)
	{
		command->command_array[j - 1] = ft_strdup(splitted_line[array_index++]);
		if (!command->command_array[j - 1])
			return (-1);
	}
	if (ret == 0)
		return (array_index + 1);
	return (array_index);
}

void	count_in_str(char *splitted_line, int *number_of_commands)
{
	size_t	i;
	char	quote_type;

	i = 0;
	while (splitted_line[i])
	{
		if (splitted_line[i] == '"' || splitted_line[i] == '\'')
		{
			quote_type = splitted_line[i];
			i++;
			while (splitted_line[i] != quote_type)
				i++;
		}
		if (splitted_line[i] == '|')
			(*number_of_commands)++;
		i++;
	}
}

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
	int		number_of_commands;
	int		i;

	i = 0;
	number_of_commands = 1;
	while (splitted_line[i])
	{
		count_in_str(splitted_line[i], &number_of_commands);
		i++;
	}
	return (number_of_commands);
}

/* Fill the simple commands array (simple commands are
 * delimitated by '|' if there is, or all the command
 * if there isnt) :
 * count them, malloc the array of simple command, and on this array put :
 *	- all the elememt of the simple command in command
 *	- only the element which aren't linked to the
 *	redirections in command_and_args */
int	get_simple_commands(t_command_line *command_line,
		char **splitted_line)
{
	size_t	i;
	int		j;
	ssize_t	array_index;

	command_line->number_of_simple_commands
		= count_commands(command_line->splitted_line);
	command_line->command = ft_calloc(sizeof(t_simple),
			command_line->number_of_simple_commands + 1);
	if (!command_line->command)
		return (1);
	array_index = 0;
	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		j = 0;
		array_index = get_commands(&command_line->command[i],
				splitted_line, array_index, j);
		if (array_index == -1)
			return (1);
		i++;
	}
	return (0);
}
