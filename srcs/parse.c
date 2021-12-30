/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/30 18:45:11 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* count_commands() returns the number of simple commands in the line
 * A simple command is a sequence of optional variable assignments
 * followed by blank-separated words and redirections,
 * and terminated by a control operator.
 * 
 * The first word specifies the command to be executed, and is passed as
 * argument zero. The remaining words are passed as arguments to the invoked
 * command. The return value of a simple command is its exit status,
 * or 128+n if the command is terminated by signal n. */
size_t	count_commands(char **splitted_line)
{
	int	number_of_commands;
	int	i;

	i = 0;
	number_of_commands = 1;
	while (splitted_line[i])
	{
		if (ft_strcmp(splitted_line[i], "|") == 0)
			number_of_commands++;
		else if (ft_strcmp(splitted_line[i], ";") == 0)
			break ;
		i++;
	}
	return (number_of_commands);
}

// Minishell should not interpret unclosed quotes
int	check_quote(char *line)
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
		if (!check_quote(command_line->line))
			return (-1);
		command_line->splitted_line = split_command_line(command_line->line);
		if (command_line->splitted_line == NULL)
			return (-1);
		expand_env_variable(&command_line->splitted_line,
			minishell->env);
		if (get_simple_commands(command_line,
				command_line->splitted_line) == -1)
			return (-1);
		if (parse_redirections(command_line) == -1)
			return (-1);
		print_command_line(command_line);
	}
	return (0);
}
