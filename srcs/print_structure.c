/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:07:37 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/25 12:16:00 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_and_args(char **command_and_args, int command_index)
{
	int	i;

	i = 0;
	while (command_and_args[i])
	{
		printf("command_line.command[%d].command_and_args[%d] = [%s]\n",
			command_index, i, command_and_args[i]);
		i++;
	}
}

void	print_simple_command(t_command_line *command_line)
{
	size_t	i;
	int		j;

	printf("\ncommand_line.number_of_simple_commands = %lu\n\n",
		command_line->number_of_simple_commands);
	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		printf("command_line.command[%lu] :\n", i);
		j = 0;
		while (command_line->command[i].command_array[j])
		{
			printf("command_line.command[%lu].command_array[%d] = %s\n",
				i, j, command_line->command[i].command_array[j]);
			j++;
		}
		print_command_and_args(command_line->command[i].command_and_args, i);
		ft_putchar('\n');
		i++;
	}
}

void	print_command_line(t_command_line *command_line)
{
	size_t	i;

	printf("-------------------------------------------------\n\n");
	printf("command_line.line = [%s]\n\n", command_line->line);
	if (command_line->splitted_line != NULL)
	{
		i = 0;
		while (command_line->splitted_line[i])
		{
			printf("command_line.splitted_line[%lu] = [%s]\n",
				i, command_line->splitted_line[i]);
			i++;
		}
	}
	if (command_line->number_of_simple_commands)
		print_simple_command(command_line);
	printf("-------------------------------------------------\n\n");
}
