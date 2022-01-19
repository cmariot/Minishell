/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:22:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/19 09:07:44 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion(t_command_line *command_line, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		expand_tilde(command_line->command[i].command_array, env);
		expand_env_variable(command_line->command[i].command_array, env);
		variable_declaration(command_line->command[i].command_array, env);
		quotes_removal(command_line->command[i].command_array);
		i++;
	}
	return (0);
}
