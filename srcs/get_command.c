/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:08:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 14:29:33 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_cmd_line(t_command_line *command_line)
{
	if (command_line->line != NULL)
		free(command_line->line);
	command_line->line = NULL;
}

// If the values aren't NULL, free the structure variables,
// Update yhe values on each loop.
void	get_command(t_shell *minishell, t_command_line *command_line)
{
	reset_cmd_line(command_line);
	minishell->prompt = get_prompt(minishell);
	if (command_line->line != NULL)
		free(command_line->line);
	command_line->line = readline(minishell->prompt);
	if (rl_on_new_line() == 0)
		add_history(command_line->line);
}
