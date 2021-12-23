/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:36:51 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/23 10:46:02 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	print_redir(t_redir *redir, int nb_of_redirection)
//{
//	int	i;
//
//	printf("command_line->number_of_redirections = %d\n\n", nb_of_redirection);
//	i = 0;
//	while (i < nb_of_redirection)
//	{
//		printf("redirection[%d].redirection_type = [%s]\n",
//			i, redir[i].redirection_type);
//		printf("redirection[%d].filename = [%s]\n", i, redir[i].filename);
//		ft_putchar('\n');
//		i++;
//	}
//}
//
//void	print_pipelines(t_pipe_command *pipe_command, int nb_of_pipes)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	printf("\ncommand_line->number_of_pipes = %d\n\n", nb_of_pipes);
//	while (i < nb_of_pipes)
//	{
//		if (pipe_command[i].command)
//			printf("pipe_command[%d].command = [%s]\n",
//				i, pipe_command[i].command);
//		if (pipe_command[i].args)
//		{
//			j = 0;
//			while (pipe_command[i].args[j])
//			{
//				printf("pipe_command[%d].args[%d] = [%s]\n",
//					i, j, pipe_command[i].args[j]);
//				j++;
//			}
//		}
//		ft_putchar('\n');
//		i++;
//	}
//}
//
//void	print_command_line(t_command_line *command_line)
//{
//	printf("\n***************************\n");
//	printf("\nligne de commande : [%s]\n\n", command_line->line);
//	printf("splitted line :\n");
//	ft_putarray("splitted_line", command_line->splitted_line);
//	if (command_line->main.command)
//	{
//		printf("\ncommand_line->main.command = [%s]\n",
//			command_line->main.command);
//		if (command_line->main.args)
//			ft_putarray("command_line->main.args", command_line->main.args);
//		if (command_line->number_of_pipes)
//			print_pipelines(command_line->pipe_command,
//				command_line->number_of_pipes);
//		if (command_line->number_of_redirections)
//			print_redir(command_line->redirection,
//				command_line->number_of_redirections);
//	}
//	printf("\n***************************\n\n");
//}
