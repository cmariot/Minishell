/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 00:40:04 by cmariot          ###   ########.fr       */
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
		if (line[i] == '#')
			break ;
		i++;
	}
	if (ok == TRUE)
		return (1);
	else
	{
		ft_putstr_fd("minishell does not interpret unclosed quotes\n", 2);
		global_exit_status(1);
		return (0);
	}
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
					ft_putstr_fd("minishell: syntax error ", 2);
					ft_putstr_fd("near redirection\n", 2);
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
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putstr_fd("near unexpected token '|'\n", 2);
			return (global_exit_status(1));
		}
		i++;
	}
	return (0);
}

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (command_line->line)
	{
		if (!check_quotes(command_line->line))
			return (-1);
		if (command_line->line[0] == '\0')
			return (0);
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
		if (check_empty_pipe(command_line,
				command_line->number_of_simple_commands))
			return (-1);
		if (check_empty_redir(command_line,
				command_line->number_of_simple_commands))
			return (-1);
		//print_command_line(command_line);
	}
	return (0);
}
