/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 15:23:37 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If only one simple command -> execute the simple command,
 * else, create a pipeline -> connect the output of the command to
 * the input of the next command */

void	execute(t_shell *minishell, t_command_line *command_line)
{
	int	backup_fd[2];

	backup_fd[0] = dup(STDIN);
	backup_fd[1] = dup(STDOUT);
	signal_catcher(1);
	if (command_line->number_of_simple_commands == 1)
		execute_simple_command(minishell, command_line->command[0], backup_fd);
	else
		create_pipeline(command_line, minishell, backup_fd);
	signal_catcher(0);
	dup2(backup_fd[0], STDIN);
	dup2(backup_fd[1], STDOUT);
	close(backup_fd[0]);
	close(backup_fd[1]);
	return ;
}
