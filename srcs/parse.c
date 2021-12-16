/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 11:05:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Count the number of pipelines and the number of redirections
void	count(char **splitted_line, int i, t_command_line *command_line)
{
	while (splitted_line[i])
	{
		if (ft_strcmp(splitted_line[i], "|") == 0)
			command_line->number_of_pipes++;
		else if (ft_strcmp(splitted_line[i], "<<") == 0)
			command_line->number_of_redirections++;
		else if (ft_strcmp(splitted_line[i], ">>") == 0)
			command_line->number_of_redirections++;
		else if (ft_strcmp(splitted_line[i], "<") == 0)
			command_line->number_of_redirections++;
		else if (ft_strcmp(splitted_line[i], ">") == 0)
			command_line->number_of_redirections++;
		i++;
	}
}

//Modifier le split pour ajouter le charset,
//verifier le charset pour la structure main
//count the number of pipes
//put in struct s_pipe_command
//count the number of redirections
//put in struct s_redir
void	parse(t_command_line *command_line)
{
	int	args_index;

	if (command_line->line)
	{
		command_line->splitted_line = ft_split(command_line->line, ' ');
		if (command_line->splitted_line)
		{
			args_index = put_in_main(command_line->splitted_line,
					&command_line->main);
			if (command_line->splitted_line[args_index + 1])
				count(command_line->splitted_line, args_index + 1,
					command_line);
			if (command_line->number_of_pipes)
				command_line->pipe_command = put_in_pipe(command_line,
						command_line->splitted_line, args_index);
		}
		print_command_line(command_line);
	}
}
