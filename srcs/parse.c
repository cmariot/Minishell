/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 14:29:53 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_line(t_command_line *command_line)
{
	int	i;

	printf("\n***************************\n");
	printf("\nligne de commande : [%s]\n\n", command_line->line);
	printf("splitted line :\n");
	i = 0;
	while (command_line->splitted_line[i])
	{
		printf("splitted_line[%d] = [%s]\n", i, command_line->splitted_line[i]);
		i++;
	}
	if (command_line->main.command)
	{
		printf("\n\nSTRUCT main :\n");
		printf("\nmain.command = [%s]\n", command_line->main.command);
		if (command_line->main.args)
		{
			i = 0;
			while (command_line->main.args[i])
			{
				printf("command_line->main.args[%d] = [%s]\n",
					i, command_line->main.args[i]);
				i++;
			}
		}
		if (command_line->number_of_pipes)
		{
			printf("\ncommand_line->number_of_pipes = %d\n",
				command_line->number_of_pipes);
		}
		if (command_line->number_of_redirections)
		{
			printf("\ncommand_line->number_of_redirections = %d\n",
				command_line->number_of_redirections);
		}
	}
	printf("\n***************************\n");
}

// renvoie le nombre d'arguments derriere la 1ere commande
// on break si on rencontre un caractere qui n'est pas un argument
// heredoc a gerer, d'autres cas ici ?
int	get_main_args_number(char **args_array)
{
	int	args_number;

	args_number = 0;
	while (args_array[args_number] != NULL)
	{
		if (ft_strcmp(args_array[args_number], "|") == 0)
			break ;
		else if (ft_strcmp(args_array[args_number], "<<") == 0)
			break ;
		else if (ft_strcmp(args_array[args_number], ">>") == 0)
			break ;
		else if (ft_strcmp(args_array[args_number], "<") == 0)
			break ;
		else if (ft_strcmp(args_array[args_number], ">") == 0)
			break ;
		args_number++;
	}
	return (args_number);
}

int	put_in_main(char **splitted_line, t_main_command *main)
{
	int	number_of_main_args;
	int	i;

	main->command = ft_strdup(splitted_line[0]);
	number_of_main_args = 0;
	if (splitted_line[1])
	{
		number_of_main_args = get_main_args_number(splitted_line + 1);
		main->args = ft_calloc(number_of_main_args + 1, sizeof(char *));
		if (!main->args)
			return (0);
		i = 0;
		while (i < number_of_main_args)
		{
			main->args[i] = ft_strdup(splitted_line[i + 1]);
			i++;
		}
	}
	return (number_of_main_args);
}

//Modifier le split pour ajouter le charset,
//
//verifier le charset pour la structure main
//count the number of pipes
//put in struct s_pipe_command
//count the number of redirections
//put in struct s_redir
void	parse(t_command_line *command_line)
{
	int	main_args_nb;
	int	i;

	if (command_line->line != NULL)
	{
		command_line->splitted_line = ft_split(command_line->line, ' ');
		if (command_line->splitted_line != NULL)
		{
			main_args_nb = put_in_main(command_line->splitted_line,
					&command_line->main);
			if (command_line->splitted_line[main_args_nb + 1] != NULL)
			{
				i = main_args_nb + 1;
				while (command_line->splitted_line[i])
				{
					if (ft_strcmp(command_line->splitted_line[i], "|") == 0)
						command_line->number_of_pipes++;
					else if (ft_strcmp(command_line->splitted_line[i], "<<") == 0)
						command_line->number_of_redirections++;
					else if (ft_strcmp(command_line->splitted_line[i], ">>") == 0)
						command_line->number_of_redirections++;
					else if (ft_strcmp(command_line->splitted_line[i], "<") == 0)
						command_line->number_of_redirections++;
					else if (ft_strcmp(command_line->splitted_line[i], ">") == 0)
						command_line->number_of_redirections++;
					i++;
				}
			}
		}
		print_command_line(command_line);
	}
}
