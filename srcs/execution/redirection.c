/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:02:31 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 21:44:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	if (access(file, F_OK) != 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(file, R_OK) != 0)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	return (1);
}

int	do_input_redirection(t_redir redir, int number_of_redirections,
	int i, bool heredoc_opt)
{
	int		file_fd;

	if (ft_strcmp(redir.redir_type, "<<") == 0)
	{
		file_fd = create_heredoc(redir.filename, heredoc_opt);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == number_of_redirections - 1)
			dup2(file_fd, STDIN);
		close(file_fd);
	}
	else if (ft_strcmp(redir.redir_type, "<") == 0)
	{
		file_fd = open(redir.filename, O_RDONLY);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == number_of_redirections - 1)
			dup2(file_fd, STDIN);
		close(file_fd);
	}
	return (0);
}

int	input_redirection(t_simple command, bool heredoc_opt)
{
	size_t	i;

	if (command.number_of_redirections)
	{
		i = 0;
		while (i < command.number_of_redirections)
		{
			do_input_redirection(command.redir[i],
				command.number_of_redirections, i, heredoc_opt);
			i++;
		}
	}
	return (0);
}

int	do_output_redirection(t_redir redir, int number_of_redirections, int i)
{
	int		file_fd;

	if (ft_strcmp(redir.redir_type, ">>") == 0)
	{
		file_fd = open(redir.filename,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == number_of_redirections - 1)
			dup2(file_fd, STDOUT);
		close(file_fd);
	}
	else if (ft_strcmp(redir.redir_type, ">") == 0)
	{
		file_fd = open(redir.filename,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == number_of_redirections - 1)
			dup2(file_fd, STDOUT);
		close(file_fd);
	}
	return (0);
}

int	output_redirection(t_simple command)
{
	size_t	i;

	if (command.number_of_redirections)
	{
		i = 0;
		while (i < command.number_of_redirections)
		{
			do_output_redirection(command.redir[i],
				command.number_of_redirections, i);
			i++;
		}
	}
	return (0);
}
