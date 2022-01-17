/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:21 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 22:42:50 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return 1 if char *element is a redirection string
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

// put the redirection values in the t_redir *redir structure
int	fill_redirections(t_redir *redir, int *array_index, char **array)
{
	while (array[(*array_index) + 1] != NULL
		&& is_redirection(array[*array_index]) != 1)
			(*array_index)++;
	if (array[(*array_index) + 1] == NULL)
		return (0);
	else
	{
		if (array[*array_index])
			redir->redir_type = ft_strdup(array[*array_index]);
		if (array[(*array_index) + 1])
		{
			redir->filename = ft_strdup(array[(*array_index) + 1]);
			if (ft_strcmp(redir->redir_type, "<<") == 0)
				create_heredoc(redir->filename, TRUE);
			*array_index += 2;
		}
		else
			*array_index += 1;
		return (0);
	}
}

//pour chaque redirection d'une commande simple, remplir la structure
int	fill_redirection_array(t_command_line *command_line, size_t i)
{
	int		array_index;
	size_t	j;

	j = 0;
	array_index = 0;
	while (j < command_line->command[i].number_of_redirections)
		if (fill_redirections(&command_line->command[i].redir[j++],
				&array_index, command_line->command[i].command_array) == -1)
			return (-1);
	return (0);
}

size_t	get_number_of_redir(char **command_array)
{
	size_t	number_of_redirections;
	size_t	j;

	number_of_redirections = 0;
	j = 0;
	while (command_array[j] != NULL)
	{
		if (is_redirection(command_array[j]) == 1)
		{
			number_of_redirections++;
		}
		j++;
	}
	return (number_of_redirections);
}

//compte le nombre de redirection dans la commande simple
//cree un tableau pour chaque redirection
//remplir le tableau avec le type de redirection et le filename
int	parse_redirections(t_command_line *command_line)
{
	size_t	i;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		command_line->command[i].number_of_redirections
			= get_number_of_redir(command_line->command[i].command_array);
		if (command_line->command[i].number_of_redirections == 0)
		{
			i++;
			continue ;
		}
		command_line->command[i].redir = ft_calloc(sizeof(t_redir),
				command_line->command[i].number_of_redirections + 1);
		if (!command_line->command[i].redir)
			return (-1);
		if (fill_redirection_array(command_line, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}