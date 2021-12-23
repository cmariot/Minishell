/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/23 14:43:52 by cmariot          ###   ########.fr       */
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

int	fill_commands(t_simple command, char **splitted_line, size_t array_index)
{
	int	i;
	int	len;

	len = array_index;
	while (splitted_line[len])
	{
		if (ft_strcmp(splitted_line[len], "|") == 0)
			break ;
		else if (ft_strcmp(splitted_line[len], ";") == 0)
			break ;
		len++;
	}
	printf("LEN = %d\n", len);
	while (splitted_line[array_index])
	{
		printf("splitted_line[%lu] = %s\n", array_index, splitted_line[array_index]);
		array_index++;
	}
	return (array_index);
}

void	get_simple_commands(t_command_line *command_line, char **splitted_line)
{
	size_t	i;
	size_t	array_index;

	command_line->number_of_simple_commands
		= count_commands(command_line->splitted_line);
	printf("NUMBER OF SIMPLE COMMANDS = %lu\n",
		command_line->number_of_simple_commands);
	command_line->command
		= ft_calloc(command_line->number_of_simple_commands + 1,
			sizeof(t_simple));
	array_index = 0;
	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		fill_commands(command_line->command[i], splitted_line, array_index);
		i++;
	}
}

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (!check_quote(command_line->line)
		&& !check_semicolon(command_line->line))
		return (-1);
	if (command_line->line)
	{
		command_line->splitted_line = split_command_line(command_line->line);
		if (command_line->splitted_line == NULL)
			return (-1);
		expand_env_variable(&command_line->splitted_line,
			minishell->env);
		get_simple_commands(command_line, command_line->splitted_line);
	}
	return (0);
}
