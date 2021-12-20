/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:44:04 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/20 12:53:37 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe_args(char **splitted_line, int i)
{
	int	nf_of_args;

	nf_of_args = 0;
	printf("ON PART DE [%s]\n", splitted_line[i]);
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
	int				nf_of_args;
	int				j;

	i++;
	if (splitted_line[i])
		pipe->command = ft_strdup(splitted_line[i]);
	nf_of_args = count_pipe_args(splitted_line, ++i);
	pipe->args = ft_calloc(nf_of_args + 2, sizeof(char *));
	if (pipe->args)
	{
		pipe->args[0] = ft_strdup(pipe->command);
		j = 1;
		while (j < nf_of_args + 1)
			pipe->args[j++] = ft_strdup(splitted_line[i++]);
	}
	return (i);
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
			i = create_pipe_struct(splitted_line, i, &pipe[pipe_index++]);
		i++;
	}
	return (pipe);
}
