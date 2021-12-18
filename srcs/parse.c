/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/18 17:12:09 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Count the number of pipelines and the number of redirections
void	count(char **splitted_line, t_command_line *command_line)
{
	int	i;

	i = 0;
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
	return ;
}

// Pour le parsing on part sur un split de la ligne pour recuperer :
//		1- la commande
//		2- les options
//		3- les arguments supplementaires
// Et ca pour : la commande principale, chaque pipe, chaque redirection
// On veut les mettre dans un tableau de char *
// On doit sauvegarder leur position et les espaces,
// on a surtout besoin de split en fonction des pipes '|' et des
// redirections '<<', '>>', '<', '>'
// Tant qu'on a pas la 1ere commande : on passe les espaces et tabulations,
// si on trouve un '-' on cree un element de tableau, jusqu'a la fin du mot, 
// 
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
				count(command_line->splitted_line,
					command_line);
			if (command_line->number_of_pipes)
				command_line->pipe_command = put_in_pipe(command_line,
						command_line->splitted_line, args_index);
			if (command_line->number_of_redirections)
				command_line->redirection = put_in_redir(command_line,
						command_line->splitted_line);
		}
		print_command_line(command_line);
	}
}
