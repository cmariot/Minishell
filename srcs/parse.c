/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 20:11:46 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Minishell should not interpret unclosed quotes
int	check_quotes(char *line)
{
	int		i;
	char	c;
	bool	ok;

	i = 0;
	ok = TRUE;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\''))
		{
			ok = FALSE;
			c = line[i];
			i++;
			while (line[i] != c && line[i] != '\0')
				i++;
			if (line[i] == c)
				ok = TRUE;
		}
		i++;
	}
	if (ok == TRUE)
		return (1);
	else
		printf("minishell does not interpret unclosed quotes.\n");
	return (0);
}

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (command_line->line)
	{
		if (!check_quotes(command_line->line))
			return (-1);
		command_line->splitted_line = split_command_line(command_line->line);
		if (command_line->splitted_line == NULL)
			return (-1);
		expand_env_variable(command_line->splitted_line,
			minishell->env);
		if (get_simple_commands(command_line,
				command_line->splitted_line, minishell->env) == -1)
			return (-1);
		if (parse_redirections(command_line) == -1)
			return (-1);
		print_command_line(command_line);
	}
	return (0);
}
