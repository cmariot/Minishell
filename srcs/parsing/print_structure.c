/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:07:37 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 13:11:04 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirections(t_command_line *command_line, size_t i)
{
	size_t	j;

	j = 0;
	while (j < command_line->command[i].number_of_redirections)
	{
		printf("command_line->command[%lu].redir[%lu].redir_type = [%s]\n",
			i, j, command_line->command[i].redir[j].redir_type);
		printf("command_line->command[%lu].redir[%lu].filename = [%s]\n",
			i, j, command_line->command[i].redir[j].filename);
		j++;
	}
}

void	print_command_and_args(char **command_and_args, int command_index)
{
	int	i;

	i = 0;
	while (command_and_args[i])
	{
		printf("command_line.command[%d].command_and_args[%d] = [%s]\n",
			command_index, i, command_and_args[i]);
		i++;
	}
}

void	print_simple_command(t_command_line *command_line)
{
	size_t	i;

	printf("\ncommand_line.number_of_simple_commands = %lu\n\n",
		command_line->number_of_simple_commands);
	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		printf("command_line.command[%lu] :\n", i);
		if (command_line->command[i].command_and_args != NULL)
			print_command_and_args(command_line->command[i].command_and_args,
				i);
		printf("command_line->command[%lu].number_of_redirections = %lu\n",
			i, command_line->command[i].number_of_redirections);
		if (command_line->command[i].number_of_redirections)
			print_redirections(command_line, i);
		ft_putchar('\n');
		i++;
	}
}

/* Affichage de la ligne de commande reccuperee par readline
 * 1- Ligne complete
 * 2- Ligne splittee
 * 3- Nombre de commandes simples (= commandes separees par des pipes)
 * 4- Pour chaque commande simple :
 *		- command_array = Commande, arguments et redirections
 *		- command_and_args = Commande et arguments seulement
 *		- redir = Type de redirection et filename */
void	print_command_line(t_command_line *command_line)
{
	size_t	i;

	printf("-------------------------------------------------\n\n");
	printf("command_line.line = [%s]\n\n", command_line->line);
	if (command_line->splitted_line != NULL)
	{
		i = 0;
		while (command_line->splitted_line[i])
		{
			printf("command_line.splitted_line[%lu] = [%s]\n",
				i, command_line->splitted_line[i]);
			i++;
		}
	}
	if (command_line->number_of_simple_commands)
		print_simple_command(command_line);
	printf("-------------------------------------------------\n\n");
}
