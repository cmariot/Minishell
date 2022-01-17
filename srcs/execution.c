/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 16:46:59 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redirection(int *stdin_backup, int *stdout_backup,
		t_simple command, int fd_output)
{
	*stdin_backup = dup(STDIN);
	*stdout_backup = dup(STDOUT);
	input_redirection(command, FALSE);
	output_redirection(command, fd_output);
}

void	restore_file_redirection(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, 0);
	dup2(stdout_backup, 1);
	close(stdin_backup);
	close(stdout_backup);
}

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */
int	execution(char **command_path, t_simple command, char **env,
	int fd_output)
{
	pid_t	pid;
	int		status;
	int		stdin_backup;
	int		stdout_backup;

	file_redirection(&stdin_backup, &stdout_backup, command, fd_output);
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("Error, fork() failed.\n", 2);
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		status = execve(*command_path,
				command.command_and_args, env);
		return (status);
	}
	waitpid(pid, &status, 0);
	restore_file_redirection(stdin_backup, stdout_backup);
	if (*command_path != NULL)
		free(*command_path);
	global_exit_status(0);
	if (WIFEXITED(status))
		global_exit_status(WEXITSTATUS(status));
	return (0);
}
