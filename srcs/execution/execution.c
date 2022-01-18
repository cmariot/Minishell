/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 13:51:32 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_redirection(int *stdin_backup, int *stdout_backup,
		t_simple command)
{
	*stdin_backup = dup(STDIN);
	*stdout_backup = dup(STDOUT);
	if (input_redirection(command) == 1)
		return (1);
	if (output_redirection(command) == 1)
		return (1);
	return (0);
}

void	restore_file_redirection(t_simple command, int stdin_backup,
		int stdout_backup)
{
	size_t	i;

	i = 0;
	while (i < command.number_of_redirections)
	{
		if (ft_strcmp(command.redir[i].redir_type, "<<") == 0)
			unlink(command.redir[i].filename);
		i++;
	}
	dup2(stdin_backup, STDIN);
	dup2(stdout_backup, STDOUT);
	close(stdin_backup);
	close(stdout_backup);
}

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */
int	execution(char **command_path, t_simple command, char **env)
{
	pid_t	pid;
	int		status;
	int		stdin_backup;
	int		stdout_backup;

	if (file_redirection(&stdin_backup, &stdout_backup, command))
		return (1);
	pid = fork();
	if (pid < 0)
		return (write(2, "minishell: fork failed.\n", 24));
	else if (pid == 0)
	{
		status = execve(*command_path,
				command.command_and_args, env);
		return (status);
	}
	waitpid(pid, &status, 0);
	restore_file_redirection(command, stdin_backup, stdout_backup);
	if (*command_path != NULL)
		free(*command_path);
	global_exit_status(0);
	if (WIFEXITED(status))
		global_exit_status(WEXITSTATUS(status));
	return (0);
}
