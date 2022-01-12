/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:02:31 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/12 19:39:45 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(char *filename, bool get_heredoc)
{
	int		heredoc_fd;
	char	*limiter;
	char	*line;

	if (get_heredoc == TRUE)
	{
		heredoc_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
		if (heredoc_fd == -1)
			return (-1);
		limiter = ft_strjoin(filename, "\n");
		while (1)
		{
			ft_putstr_fd("heredoc ➤ ", 1);
			line = get_next_line(0);
			if (ft_strcmp(line, limiter) == 0)
				break ;
			else
			{
				ft_putstr_fd(line, heredoc_fd);
				free(line);
			}
		}
		free(line);
		free(limiter);
		return (heredoc_fd);
	}
	else
	{
		heredoc_fd = open("here_doc", O_RDONLY);
		if (heredoc_fd == -1)
			return (-1);
		return (heredoc_fd);
	}
}

int	input_error(void)
{
	ft_putstr_fd("minishell: error\n", 2);
	return (1);
}

int	input_redirection(t_simple command, bool heredoc_opt)
{
	size_t	i;
	int		fd;

	if (command.number_of_redirections)
	{
		i = 0;
		while (i < command.number_of_redirections)
		{
			if (ft_strcmp(command.redir[i].redir_type, "<<") == 0)
				fd = create_heredoc(command.redir[i].filename, heredoc_opt);
			else if (ft_strcmp(command.redir[i].redir_type, "<") == 0)
				fd = open(command.redir[i].filename, O_RDONLY);
			if (fd == -1)
				return (input_error());
			if (i == command.number_of_redirections - 1)
				dup2(fd, STDIN);
			close(fd);
			i++;
		}
	}
	return (0);
}

int	output_error(void)
{
	//erreur a mettre a jour : pas le droit de creation dans le dossier 
	ft_putstr_fd("minishell: error\n", 2);
	return (1);
}

int	output_redirection(t_simple command)
{
	size_t	i;
	int		fd;

	if (command.number_of_redirections)
	{
		i = 0;
		while (i < command.number_of_redirections)
		{
			if (ft_strcmp(command.redir[i].redir_type, ">>") == 0)
				fd = open(command.redir[i].filename,
						O_RDWR | O_CREAT | O_APPEND, 0644);
			else if (ft_strcmp(command.redir[i].redir_type, ">") == 0)
				fd = open(command.redir[i].filename,
						O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (output_error());
			if (i == command.number_of_redirections - 1)
				dup2(fd, STDOUT);
			close(fd);
			i++;
		}
	}
	return (0);
}
