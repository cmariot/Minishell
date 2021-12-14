/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 16:17:24 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_line(t_command_line *command_line)
{
	int	i;

	i = 0;
	printf("\n***************************\n");
	printf("ligne de commande : [%s]\n\n", command_line->line);
	printf("splitted line :\n");
	while (command_line->splitted_line[i])
	{
		printf("splitted_line[%d] = [%s]\n", i, command_line->splitted_line[i]);
		i++;
	}
	printf("\nstructure main :\n");
	printf("main.command = %s\n", command_line->main.command);
	printf("\n***************************\n");
}

int	get_main_args_number()
{
	int	args_number;

	args_number= 0;
	return (args_number);
}

void	put_in_main(char **splitted_line, t_main_command *main)
{
	main->command = ft_strdup(splitted_line[0]);
	//get_1st_command_args_number
}

void	parse(t_command_line *command_line)
{
	command_line->splitted_line = ft_split(command_line->line, ' ');
	put_in_main(command_line->splitted_line, &command_line->main);
	//count the number of pipes
	//put in struct s_pipe_command
	//count the number of redirections
	//put in struct s_redir
	print_command_line(command_line);
}
