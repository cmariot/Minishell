/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:21 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/27 13:59:01 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *element)
{
	if (ft_strcmp(element, "<<") == 0)
		return (1);
	else if (ft_strcmp(element, ">>") == 0)
		return (1);
	else if (ft_strcmp(element, "<") == 0)
		return (1);
	else if (ft_strcmp(element, ">") == 0)
		return (1);
	else
		return (0);
}

int	fill_redirections(t_redir *redir, char **array, int array_index)
{
	while (array[array_index + 1] != NULL
		&& is_redirection(array[array_index]) != 1)
			array_index++;
	if (array[array_index + 1] == NULL)
	{
		printf("Minishell: syntax error near redirection. (no filename ?)\n");
		return (-1);
	}
	else
	{
		if (array[array_index])
			redir->redir_type = ft_strdup(array[array_index]);
		if (array[array_index + 1])
		{
			redir->filename = ft_strdup(array[array_index + 1]);
			return (array_index + 2);
		}
		else
			return (array_index + 1);
	}
}

//compte le nombre de redirection dans la commande simple
//cree un tableau pour chaque redirection
//remplir le tableau avec le type de redirection et le filename
int	parse_redirections(t_command_line *command_line)
{
	size_t	i;
	size_t	j;
	int		array_index;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		array_index = 0;
		command_line->command[i].number_of_redirections = 0;
		j = 0;
		while (command_line->command[i].command_array[j])
			if (is_redirection(command_line->command[i].command_array[j++]))
				command_line->command[i].number_of_redirections++;
		if (command_line->command[i].number_of_redirections == 0)
		{
			i++;
			continue ;
		}
		command_line->command[i].redir
			= ft_calloc(command_line->command[i].number_of_redirections + 1,
				sizeof(t_redir));
		if (!command_line->command[i].redir)
			return (-1);
		j = 0;
		while (j < command_line->command[i].number_of_redirections)
		{
			array_index = fill_redirections(&command_line->command[i].redir[j],
					command_line->command[i].command_array, array_index);
			if (array_index == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
