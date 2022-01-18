/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:56:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 15:25:18 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_error(void)
{
	ft_putstr_fd("minishell: error: pipe failed.\n", 2);
}

void	fork_error(void)
{
	ft_putstr_fd("minishell: error: fork failed.\n", 2);
}

/* For the last pipe, STDIN is already redirect, so just fork.
 * In the child, execute command and exit.
 * In the parent, restore the file_descriptor */
void	last_pipe(t_shell *minishell, t_simple command, int *backup_fd)
{
	execute_simple_command(minishell, command, backup_fd);
}

/* For the firsts pipes, create a pipe and fork the program
 * In the child redirect output into the pipe, execute command and exit.
 * In the parent, close the fd and redirect STDIN. */
void	firsts_pipes(t_shell *minishell, t_simple command, int *backup_fd)
{
	int		pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (pipe_error());
	pid = fork();
	if (pid == -1)
		return (fork_error());
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT);
		execute_simple_command(minishell, command, backup_fd);
		close(pipe_fd[1]);
		close(backup_fd[0]);
		close(backup_fd[1]);
		free_minishell(minishell);
		exit(return_global_exit_status());
	}
	waitpid(pid, &pid, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN);
	close(pipe_fd[0]);
}

/* For each simple command, connect the input and the output to the pipe,
 * except for the last one, the output is on stdout. */
void	create_pipeline(t_command_line *command_line, t_shell *minishell,
		int *backup_fd)
{
	size_t	i;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		if (i < command_line->number_of_simple_commands - 1)
			firsts_pipes(minishell, command_line->command[i], backup_fd);
		else
			last_pipe(minishell, command_line->command[i], backup_fd);
		i++;
	}
}
