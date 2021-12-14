/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 18:29:09 by cmariot          ###   ########.fr       */
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
	printf("\n\nSTRUCT main :\n");
	printf("\nmain.command = [%s]\n", command_line->main.command);
	printf("\nmain.args :\n");
	i = 0;
	while (command_line->main.args[i])
	{
		printf("command_line->main.args[%d] = [%s]\n",
			i, command_line->main.args[i]);
		i++;
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
	return (number_of_main_args);
}

//Modifier le split pour ajouter le charset,
//verifier le charset pour la structure main
//count the number of pipes
//put in struct s_pipe_command
//count the number of redirections
//put in struct s_redir
void	parse(t_command_line *command_line)
{
	int	main_args_nb;

	command_line->splitted_line = ft_split(command_line->line, ' ');
	main_args_nb = put_in_main(command_line->splitted_line,
			&command_line->main);
	print_command_line(command_line);
}
