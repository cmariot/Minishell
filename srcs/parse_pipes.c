/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:44:04 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/22 14:43:51 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe_args(char **splitted_line, int i)
{
	int	nf_of_args;

	nf_of_args = 0;
	while (splitted_line[i])
	{
		if (ft_strcmp(splitted_line[i], "|") == 0)
			break ;
		else if (ft_strcmp(splitted_line[i], "<<") == 0)
			break ;
		else if (ft_strcmp(splitted_line[i], ">>") == 0)
			break ;
		else if (ft_strcmp(splitted_line[i], "<") == 0)
			break ;
		else if (ft_strcmp(splitted_line[i], ">") == 0)
			break ;
		nf_of_args++;
		i++;
	}
	return (nf_of_args);
}

int	create_pipe_struct(char **splitted_line, int i, t_pipe_command *pipe)
{
	int				nb_of_args;
	int				j;

	if (splitted_line[i + 1])
		pipe->command = ft_strdup(splitted_line[i + 1]);
	nb_of_args = count_pipe_args(splitted_line, i + 1);
	pipe->args = ft_calloc(nb_of_args + 1, sizeof(char *));
	if (pipe->args)
	{
		j = 0;
		pipe->args[j++] = ft_strdup(pipe->command);
		while (j < nb_of_args)
		{
			i++;
			pipe->args[j++] = ft_strdup(splitted_line[i + 1]);
		}
	}
	return (i + 1);
}

t_pipe_command	*put_in_pipe(t_command_line *command_line,
		char **splitted_line)
{
	t_pipe_command	*pipe;
	int				pipe_index;
	int				i;

	i = command_line->number_of_pipes + 1;
	pipe = ft_calloc(i, sizeof(t_pipe_command));
	if (!pipe)
		return (NULL);
	i = 0;
	pipe_index = 0;
	while (splitted_line[i] && pipe_index < command_line->number_of_pipes)
	{
		if (ft_strcmp(splitted_line[i], "|") == 0)
		{
			i = create_pipe_struct(splitted_line, i, &pipe[pipe_index]);
			pipe_index++;
		}
		i++;
	}
	return (pipe);
}
