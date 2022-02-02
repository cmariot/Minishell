/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:02:31 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/02 11:44:01 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_error(char *file)
{
	print(2, "minishell: ");
	if (ft_isadirectory(file) == TRUE)
		print(2, "%s: is a directory\n", file);
	else if (access(file, F_OK) != 0)
		print(2, "%s: no such file or directory\n", file);
	else if (access(file, R_OK) != 0)
		print(2, "%s: permission denied\n", file);
	return (global_exit_status(1));
}

int	do_input_redirection(t_redir redir, int last_redir_index,
	int i)
{
	int		file_fd;

	if (ft_strcmp(redir.redir_type, "<") == 0
		|| ft_strcmp(redir.redir_type, "<<") == 0)
	{
		file_fd = open(redir.filename, O_RDONLY);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == last_redir_index)
			dup2(file_fd, STDIN);
		close(file_fd);
	}
	return (0);
}

int	input_redirection(t_simple command)
{
	size_t	i;
	int		last_redir_index;

	if (command.number_of_redirections)
	{
		last_redir_index = command.number_of_redirections - 1;
		while (last_redir_index > 0
			&& ft_strcmp(command.redir[last_redir_index].redir_type, "<<")
			&& ft_strcmp(command.redir[last_redir_index].redir_type, "<"))
			last_redir_index--;
		i = 0;
		while (i < command.number_of_redirections)
		{
			if (do_input_redirection(command.redir[i],
					last_redir_index, i) == 1)
				return (global_exit_status(1));
			i++;
		}
	}
	return (global_exit_status(0));
}

int	do_output_redirection(t_redir redir, int i, int last_redir_index)
{
	int		file_fd;

	if (ft_strcmp(redir.redir_type, ">>") == 0)
	{
		file_fd = open(redir.filename,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == last_redir_index)
			dup2(file_fd, STDOUT);
		close(file_fd);
	}
	else if (ft_strcmp(redir.redir_type, ">") == 0)
	{
		file_fd = open(redir.filename,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (redirection_error(redir.filename));
		if (i == last_redir_index)
			dup2(file_fd, STDOUT);
		close(file_fd);
	}
	return (0);
}

int	output_redirection(t_simple command)
{
	size_t	i;
	int		last_redir_index;

	if (command.number_of_redirections)
	{
		last_redir_index = command.number_of_redirections - 1;
		while (last_redir_index > 0
			&& ft_strcmp(command.redir[last_redir_index].redir_type, ">>")
			&& ft_strcmp(command.redir[last_redir_index].redir_type, ">"))
			last_redir_index--;
		i = 0;
		while (i < command.number_of_redirections)
		{
			if (do_output_redirection(command.redir[i], i,
					last_redir_index) == 1)
				return (global_exit_status(1));
			i++;
		}
	}
	return (global_exit_status(0));
}
