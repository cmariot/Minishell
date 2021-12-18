/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:34:44 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/18 17:54:35 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//if splitted_line[0] == << on fait +2 ? / cas particuliers
int	put_in_main(char **splitted_line, t_main_command *main)
{
	int	number_of_main_args;
	int	i;

	i = 0;
	if (ft_strcmp(splitted_line[0], "<<") == 0)
		i = 2;
	main->command = ft_strdup(splitted_line[i]);
	number_of_main_args = 0;
	number_of_main_args = get_main_args_number(splitted_line + 1);
	main->args = ft_calloc(number_of_main_args + 2, sizeof(char *));
	if (!main->args)
		return (0);
	i = 0;
	while (i < number_of_main_args + 1)
	{
		main->args[i] = ft_strdup(splitted_line[i]);
		i++;
	}
	return (number_of_main_args);
}
