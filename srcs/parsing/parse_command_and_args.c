/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_and_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:27 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/31 10:58:33 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_command_and_args(t_simple *command)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (command->command_array[i] != NULL)
	{
		if (is_redirection(command->command_array[i]))
		{
			if (command->command_array[i + 1] != NULL)
				i += 2;
			else if (command->command_array[i + 1] == NULL)
				return (0);
		}
		else
		{
			command->command_and_args[j]
				= ft_strdup(command->command_array[i]);
			if (!command->command_and_args[j])
				return (1);
			j++;
			i++;
		}
	}
	return (0);
}

int	get_command_and_args_len(char **command_array)
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

int	get_command_and_args(t_command_line *command_line)
{
	int		len;
	size_t	i;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		len = get_command_and_args_len(command_line->command[i].command_array);
		if (len == 0)
		{
			i++;
			continue ;
		}
		command_line->command[i].command_and_args
			= ft_calloc(len + 1, sizeof(char *));
		if (!command_line->command[i].command_and_args)
			return (1);
		if (fill_command_and_args(&command_line->command[i]))
			return (1);
		i++;
	}
	return (0);
}
