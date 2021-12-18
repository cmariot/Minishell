/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:36:51 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/18 16:13:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir[i].redirection_type)
	{
		printf("redirection[%d].redirection_type = %s\n",
			i, redir[i].redirection_type);
		printf("redirection[%d].filename = %s\n", i, redir[i].filename);
		i++;
	}
}

void	print_pipelines(t_pipe_command *pipe_command)
{
	char	*name;
	char	*tmp;
	int		i;

	i = 0;
	while (pipe_command[i].command)
	{
		printf("pipe_command[%d].command = [%s]\n", i, pipe_command[i].command);
		tmp = ft_itoa(i);
		name = ft_strjoin("pipe_command[", tmp);
		free(tmp);
		tmp = ft_strjoin(name, "].arg");
		ft_putarray(tmp, pipe_command[i].args);
		ft_putchar('\n');
		free(tmp);
		free(name);
		i++;
	}
}

void	print_command_line(t_command_line *command_line)
{
	printf("\n***************************\n");
	printf("\nligne de commande : [%s]\n\n", command_line->line);
	printf("splitted line :\n");
	ft_putarray("splitted_line", command_line->splitted_line);
	if (command_line->main.command)
	{
		printf("\ncommand_line->main.command = [%s]\n",
			command_line->main.command);
		if (command_line->main.args)
			ft_putarray("command_line->main.args", command_line->main.args);
		if (command_line->number_of_pipes)
		{
			printf("\ncommand_line->number_of_pipes = %d\n\n",
				command_line->number_of_pipes);
			print_pipelines(command_line->pipe_command);
		}
		if (command_line->number_of_redirections)
		{
			printf("\ncommand_line->number_of_redirections = %d\n",
				command_line->number_of_redirections);
			print_redir(command_line->redirection);
		}
	}
	printf("\n***************************\n\n");
}
