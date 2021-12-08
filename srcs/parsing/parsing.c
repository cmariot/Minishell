/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:01:19 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/08 12:53:59 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_struct(t_command_table *line_struct)
{
	line_struct->splitted_line = NULL;
	line_struct->command = NULL;
	line_struct->args = NULL;
	line_struct->pipe = 0;
	line_struct->command2 = NULL;
	line_struct->args2 = NULL;
	line_struct->redir_in = 0;
	line_struct->redir_out = 0;
	line_struct->heredoc = 0;
	line_struct->redir_out_append = 0;
	line_struct->filename = NULL;
}

void	get_booleans(char *splitted, t_command_table *line_struct)
{
	if (ft_strcmp(splitted, "|") == 0)
		line_struct->pipe = 1;
	else if (ft_strcmp(splitted, "<") == 0)
		line_struct->redir_in = 1;
	else if (ft_strcmp(splitted, ">") == 0)
		line_struct->redir_out = 1;
	else if (ft_strcmp(splitted, "<<") == 0)
		line_struct->heredoc = 1;
	else if (ft_strcmp(splitted, ">>") == 0)
		line_struct->redir_out_append = 1;
}

int	parse(char	*line)
{
	t_command_table	line_struct;
	int				i;

	init_struct(&line_struct);
	line_struct.splitted_line = ft_split(line, ' ');
	i = 0;
	while (line_struct.splitted_line[i] != NULL)
	{
		get_booleans(line_struct.splitted_line[i], &line_struct);
		i++;
	}
	printf("HEREDOC = %d\n", line_struct.heredoc);
	i = 0;
	while (line_struct.splitted_line[i])
	{
		free(line_struct.splitted_line[i]);
		i++;
	}
	free(line_struct.splitted_line);
	return (0);
}

int	main(void)
{
	char	*command;

	command = "ls -la";
	parse(command);
	return (0);
}
