/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/27 13:17:07 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (command_line->line)
	{
		if (!check_quote(command_line->line))
			return (-1);
		command_line->splitted_line = split_command_line(command_line->line);
		if (command_line->splitted_line == NULL)
			return (-1);
		expand_env_variable(&command_line->splitted_line,
			minishell->env);
		get_simple_commands(command_line, command_line->splitted_line);
		if (parse_redirections(command_line) == -1)
			return (-1);
		print_command_line(command_line);
	}
	return (0);
}
