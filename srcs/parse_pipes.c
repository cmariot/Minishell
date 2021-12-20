/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:44:04 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/20 11:27:29 by cmariot          ###   ########.fr       */
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
		char **splitted_line)
{
	t_pipe_command	*pipe;
	int				len;
	int				i;
	int				pipe_index;
	int				j;

	len = command_line->number_of_pipes + 1;
	pipe = ft_calloc(len, sizeof(t_pipe_command));
	if (!pipe)
		return (NULL);
	i = 0;
	pipe_index = 0;
	while (splitted_line[i])
	{
		if (ft_strcmp(splitted_line[i], "|") == 0)
		{
			printf("PIPE trouve\n");
			pipe[pipe_index].command = ft_strdup(splitted_line[++i]);
			printf("COMMANDE = %s\n", pipe[pipe_index].command);
			len = count_len(splitted_line, i);
			printf("NOMBRE D'ARGUMENTS = %d\n", len);
			pipe[pipe_index].args = ft_calloc(len + 2, sizeof(char *));
			j = 1;
			pipe[pipe_index].args[0] = ft_strdup(pipe[pipe_index].command);
			if (pipe[pipe_index].args)
				while (j < len + 1)
					pipe[pipe_index].args[j++] = ft_strdup(splitted_line[i++]);
			pipe_index++;
		}
		i++;
	}
	return (pipe);
}
