/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:12:24 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/07 12:33:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		char **splitted_line)
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
		array_index = get_commands(&command_line->command[i],
				splitted_line, array_index);
		i++;
	}
	return (0);
}
