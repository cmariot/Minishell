/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:08:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 15:24:02 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// Get the prompt and use readline to show the prompt and store the input line
void	get_command_line(t_shell *minishell, t_command_line *command_line)
{
	minishell->prompt = get_prompt(minishell);
	//command_line->line = readline(minishell->prompt);
	ft_putstr(minishell->prompt);
	command_line->line = gnl_without_bn(0);
	if (ft_strcmp(command_line->line, "") == 0)
	{
		free(command_line->line);
		command_line->line = NULL;
	}
	//if (rl_on_new_line() == 0)
	//{
	//	add_history(command_line->line);
	//}
	free(minishell->prompt);
}
