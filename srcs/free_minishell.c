/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:11:32 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 14:34:46 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_command_line *command_line, int j,
		size_t *number_of_redirections)
{
	size_t	i;

	i = 0;
	while (i < *number_of_redirections)
	{
		if (command_line->command[j].redir[i].redir_type != NULL)
		{
			free(command_line->command[j].redir[i].redir_type);
		}
		command_line->command[j].redir[i].redir_type = NULL;
		if (command_line->command[j].redir[i].filename != NULL)
		{
			free(command_line->command[j].redir[i].filename);
		}
		command_line->command[j].redir[i].filename = NULL;
		i++;
	}
	if (command_line->command[j].redir)
		free(command_line->command[j].redir);
	*number_of_redirections = 0;
}

void	free_simple_commands(t_command_line *command_line)
{
	size_t	i;

	i = 0;
	while (i != command_line->number_of_simple_commands)
	{
		ft_free_array(command_line->command[i].command_array);
		ft_free_array(command_line->command[i].command_and_args);
		if (command_line->command[i].number_of_redirections > 0)
			free_redirections(command_line, i,
				&command_line->command[i].number_of_redirections);
		i++;
	}
	if (command_line->command)
		free(command_line->command);
	command_line->number_of_simple_commands = 0;
}

void	reset_minishell(t_command_line *command_line)
{
	if (command_line->line)
		free(command_line->line);
	command_line->line = NULL;
	ft_free_array(command_line->splitted_line);
	free_simple_commands(command_line);
}

// Free the structure elements before exit
void	free_minishell(t_shell *minishell)
{
	ft_lstclear_env(&minishell->env, free);
	close(0);
	close(1);
	close(2);
	reset_minishell(&minishell->command_line);
}
