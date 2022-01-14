/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:56:14 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/14 11:53:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* For the last pipe, STDIN is already redirect, so just fork.
 * In the child, execute command and exit.
 * In the parent, restore the file_descriptor */
void	last_pipe(t_shell *minishell, t_command_line *command_line,
			size_t i, int *backup_fd, int *fd)
{
	int		pid;

	printf("LAST_PIPE():\nFD[0] = %d\n", fd[0]);
	printf("FD[1] = %d\n", fd[1]);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("ERROR fork()\n", 2);
	else if (pid == 0)
	{
		search_exec(minishell, command_line, i, backup_fd);
		close(backup_fd[0]);
		close(backup_fd[1]);
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &pid, 0);
		dup2(backup_fd[0], STDIN);
		dup2(backup_fd[1], STDOUT);
		close(backup_fd[0]);
		close(backup_fd[1]);
	}
}

/* For the firsts pipes, create a pipe and fork the program
 * In the child redirect output into the pipe, execute command and exit.
 * In the parent, close the fd and redirect STDIN. */
void	firsts_pipes(t_shell *minishell, t_command_line *command_line,
			size_t i, int *backup_fd, int *fd)
{
	int		pid;

	if (pipe(fd) == -1)
		ft_putstr_fd("ERROR pipe()\n", 2);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("ERROR fork()\n", 2);
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		search_exec(minishell, command_line, i, fd);
		close(fd[1]);
		close(backup_fd[0]);
		close(backup_fd[1]);
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &pid, 0);
	close(fd[1]);
	dup2(fd[0], STDIN);
	close(fd[0]);
}

/* For each simple command, connect the input and the output to the pipe,
 * except for the last one, the output is on stdout. */
void	create_pipeline(t_command_line *command_line, t_shell *minishell, int *fd)
{
	int		backup_fd[2];
	size_t	i;

	printf("CREATE_PIPELINE():\nFD[0] = %d\n", fd[0]);
	printf("FD[1] = %d\n", fd[1]);
	backup_fd[0] = dup(STDIN);
	backup_fd[1] = dup(STDOUT);
	i = 0;
	while (i < command_line->number_of_simple_commands - 1)
	{
		if (i < command_line->number_of_simple_commands - 2)
		{
			printf("On passe la ???\n");
			firsts_pipes(minishell, command_line, i, backup_fd, fd);
		}
		else
		{
			printf("CREATE_PIPELINE():\n");
			printf("FD[0] = %d\n", fd[0]);
			printf("FD[1] = %d\n", fd[1]);
			last_pipe(minishell, command_line, i, backup_fd, fd);
		}
		i++;
	}
}
