/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 15:54:00 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */

int	execution(char **command_path, t_simple command, char **env, int *backup_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (write(2, "minishell: fork failed.\n", 24));
	else if (pid == 0)
	{
		close(backup_fd[0]);
		close(backup_fd[1]);
		status = execve(*command_path, command.command_and_args, env);
		return (status);
	}
	waitpid(pid, &status, 0);
	if (*command_path != NULL)
		free(*command_path);
	global_exit_status(0);
	if (WIFEXITED(status))
		global_exit_status(WEXITSTATUS(status));
	return (0);
}
