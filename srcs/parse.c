/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/09 19:30:29 by cmariot          ###   ########.fr       */
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
		if (line[i] == '\\' || line[i] == ';')
		{
			ok = FALSE;
			break ;
		}
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
	{
		ft_putstr_fd("minishell does not interpret unclosed quotes ", 2);
		ft_putstr_fd("or unspecified special characters like \\ or ;.\n", 2);
		change_global_exit_status(1);
	}
	return (0);
}

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (command_line->line)
	{
		if (!check_quotes(command_line->line))
			return (-1);
		command_line->splitted_line = get_tokens_array(command_line->line);
		if (command_line->splitted_line == NULL)
			return (-1);
		if (get_simple_commands(command_line,
				command_line->splitted_line) == -1)
			return (-1);
		expansion(command_line, minishell->env);
		get_command_and_args(command_line);
		if (parse_redirections(command_line) == -1)
			return (-1);
		//print_command_line(command_line);
	}
	return (0);
}
