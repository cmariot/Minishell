/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:11:32 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 15:37:43 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(t_pipe_command *pipe_command, t_command_line *command_line)
{
	int	i;

	i = 0;
	while (i < command_line->number_of_pipes)
	{
		if (pipe_command[i].command)
			free(pipe_command[i].command);
		if (pipe_command[i].args)
			ft_free_array(pipe_command[i].args);
		i++;
	}
	free(pipe_command);
	command_line->number_of_pipes = 0;
}

void	reset_minishell(t_command_line *command_line)
{
	if (command_line->line)
		free(command_line->line);
	command_line->line = NULL;
	ft_free_array(command_line->splitted_line);
	if (command_line->main.command != NULL)
		free(command_line->main.command);
	command_line->main.command = NULL;
	if (command_line->main.args != NULL)
		ft_free_array(command_line->main.args);
	command_line->main.args = NULL;
	if (command_line->number_of_pipes)
		free_pipes(command_line->pipe_command, command_line);
	command_line->number_of_redirections = 0;
}

// Free the structure elements before exit
void	free_minishell(t_shell *minishell)
{
	ft_lstclear_env(&minishell->env, free);
	reset_minishell(&minishell->command_line);
}
