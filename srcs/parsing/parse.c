/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/07 10:54:45 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	skip_verif_inside_quotes(char *line, int *i)
{
	bool	ok;
	char	c;

	ok = FALSE;
	c = line[*i];
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
		(*i)++;
	if (line[*i] == c)
		ok = TRUE;
	return (ok);
}

int	check_empty_redir(t_command_line *command_line,
		size_t number_of_simple_commands)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < number_of_simple_commands)
	{
		j = 0;
		if (command_line->command[i].number_of_redirections)
		{
			while (j < command_line->command[i].number_of_redirections)
			{
				if (!(command_line->command[i].redir[j].filename))
				{
					print(2, "minishell: syntax error ");
					print(2, "near redirection\n");
					return (global_exit_status(1));
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	check_empty_pipe(t_command_line *command_line,
		size_t number_of_simple_commands)
{
	size_t	i;

	if (number_of_simple_commands == 1)
		return (0);
	i = 0;
	while (i < number_of_simple_commands)
	{
		if (!command_line->command[i].command_and_args
			&& command_line->command[i].number_of_redirections == 0)
		{
			print(2, "minishell: syntax error ");
			print(2, "near unexpected token '|'\n");
			return (global_exit_status(2));
		}
		i++;
	}
	return (0);
}

// Minishell should not interpret unclosed quotes
int	check_quotes(char *line)
{
	int		i;
	bool	ok;

	i = 0;
	ok = TRUE;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\''))
			ok = skip_verif_inside_quotes(line, &i);
		if (line[i] == '\0' || line[i] == '#')
			break ;
		i++;
	}
	if (ok == TRUE)
		return (0);
	else
	{
		print(2, "minishell does not interpret unclosed quotes\n");
		return (global_exit_status(1));
	}
}

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (command_line->line[0] == '\0')
		return (1);
	if (check_quotes(command_line->line))
		return (1);
	if (get_tokens_array(command_line->line, &command_line->splitted_line))
		return (1);
	if (get_simple_commands(command_line, command_line->splitted_line))
		return (1);
	if (get_command_and_args(command_line))
		return (1);
	if (command_and_args_expansion(command_line, minishell->env))
		return (1);
	if (parse_redirections(command_line, minishell->env))
		return (1);
	if (check_empty_pipe(command_line,
			command_line->number_of_simple_commands))
		return (1);
	if (check_empty_redir(command_line,
			command_line->number_of_simple_commands))
		return (1);
	if (expansion(command_line, minishell->env))
		return (1);
	return (0);
}
