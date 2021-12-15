/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:11:32 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 16:17:40 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	command_line->number_of_pipes = 0;
	command_line->number_of_redirections = 0;
}

// Free the structure elements before exit
void	free_minishell(t_shell *minishell)
{
	ft_lstclear_env(&minishell->env, free);
	reset_minishell(&minishell->command_line);
}
