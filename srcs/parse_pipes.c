/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:44:04 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 11:05:44 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char **splitted_line, int i)
{
	int	len;

	len = 0;
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
		len++;
		i++;
	}
	return (len);
}

t_pipe_command	*put_in_pipe(t_command_line *command_line,
		char **splitted_line, int args_index)
{
	t_pipe_command	*pipe;
	int				len;
	int				i;
	int				j;

	len = command_line->number_of_pipes + 1;
	pipe = ft_calloc(len, sizeof(t_pipe_command));
	if (!pipe)
		return (NULL);
	i = 0;
	args_index += 2;
	while (i < command_line->number_of_pipes)
	{
		if (splitted_line[args_index])
			pipe[i].command = ft_strdup(splitted_line[args_index++]);
		len = count_len(splitted_line, args_index);
		pipe[i].args = ft_calloc(len + 1, sizeof(char *));
		j = 0;
		if (pipe[i].args)
			while (j < len)
				pipe[i].args[j++] = ft_strdup(splitted_line[args_index++]);
		i++;
		args_index++;
	}
	return (pipe);
}
