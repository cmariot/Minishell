/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/20 16:20:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */

int	execution(char **command_path, t_simple command, char **env, int *backup_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (write(2, "minishell: fork failed.\n", 24));
	else if (pid == 0)
	{
		close(backup_fd[0]);
		close(backup_fd[1]);
		execve(*command_path, command.command_and_args, env);
	}
	waitpid(pid, &pid, 0);
	if (WIFEXITED(pid))
		global_exit_status(WEXITSTATUS(pid));
	if (WIFSIGNALED(pid))
	{
		global_exit_status(WTERMSIG(pid));
		if (return_global_exit_status() != 131)
			global_exit_status(return_global_exit_status() + 128);
	}
	if (*command_path != NULL)
		free(*command_path);
	return (0);
}
