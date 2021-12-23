/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:21 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/23 17:39:58 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *element)
{
	if (ft_strcmp(element, "<<") == 0)
		return (1);
	else if (ft_strcmp(element, "<<") == 0)
		return (1);
	else if (ft_strcmp(element, "<") == 0)
		return (1);
	else if (ft_strcmp(element, ">") == 0)
		return (1);
	else
		return (0);
}

void	parse_redirections(t_command_line *command_line)
{
	size_t	i;
	int		j;
	int		number_of_redirections;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		number_of_redirections = 0;
		j = 0;
		while (command_line->command[i].command_array[j])
		{
			if (is_redirection(command_line->command[i].command_array[j]))
				number_of_redirections++;
			j++;
		}
		printf("NOMBRE DE REDIR DANS COMMANDE %lu = %d\n",
			i, number_of_redirections);
		i++;
	}
}
