/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:22:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/22 22:27:09 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion(t_command_line *command_line, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		if (expand_tilde(command_line->command[i].command_array, env))
			return (1);
		//gestion erreur a verifier sur expand_env_variable
		if (expand_env_variable(command_line->command[i].command_array, env))
			return (1);
		quotes_removal(command_line->command[i].command_array);
		i++;
	}
	return (0);
}
