/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 20:49:18 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If only one simple command -> execute the simple command,
 * else, create a pipeline -> connect the output of the command to
 * the input of the next command */

void	execute(t_shell *minishell, t_command_line *command_line)
{
	signal_catcher(1);
	if (command_line->number_of_simple_commands == 1)
		execute_simple_command(minishell, command_line->command[0]);
	else
		create_pipeline(command_line, minishell);
	signal_catcher(0);
	return ;
}
