/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/06 12:57:00 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_exit_status(pid_t pid)
{
	if (WIFEXITED(pid))
		global_exit_status(WEXITSTATUS(pid));
	else if (WIFSIGNALED(pid))
		global_exit_status(WTERMSIG(pid));
}

void	close_backup_fd(int *backup_fd)
{
	close(backup_fd[0]);
	close(backup_fd[1]);
}

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */

int	execution(char **command_path, t_simple command, t_shell *minishell,
	int *backup_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print(2, "minishell: fork failed.\n"));
	else if (pid == 0)
	{
		close_backup_fd(backup_fd);
		pid = execve(*command_path, command.command_and_args,
				minishell->env_array);
		if (pid == -1)
		{
			if (*command_path != NULL)
				free(*command_path);
			global_exit_status(0);
			free_minishell(minishell);
		}
		exit(pid);
	}
	waitpid(pid, &pid, 0);
	if (return_global_exit_status() < 128)
		change_exit_status(pid);
	if (*command_path != NULL)
		free(*command_path);
	return (0);
}
