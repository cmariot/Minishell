/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/06 16:58:29 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//simple_command
//	redirection
//	execution
//		builtins
//		if no slash -> search binary in path
//			if found
//				fork
//				exit status -> waitpid
//		else try to execute directly
//			fork
//			exit status -> waitpid
//	restore redirection
//
//pipeline

/* If only one simple command -> execute the simple command,
 * else, create a pipeline -> connect the output of the command to
 * the input of the next command */

void	execute(t_shell *minishell, t_command_line *command_line)
{
	int	backup_fd[2];

	backup_fd[STDIN] = dup(STDIN);
	backup_fd[STDOUT] = dup(STDOUT);
	if (command_line->number_of_simple_commands <= 1)
		execute_simple_command(minishell, command_line->command[0], backup_fd);
	else
		create_pipeline(command_line, minishell, backup_fd);
	dup2(backup_fd[STDIN], STDIN);
	dup2(backup_fd[STDOUT], STDOUT);
	close(backup_fd[STDIN]);
	close(backup_fd[STDOUT]);
	return ;
}
