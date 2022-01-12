/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:02:31 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/12 08:39:03 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(char *filename)
{
	int		heredoc_fd;
	char	*limiter;
	char	*line;

	heredoc_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (heredoc_fd == -1)
		return (-1);
	limiter = ft_strjoin(filename, "\n");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT);
		line = get_next_line(STDIN);
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

int	create_redirection(t_simple command, int previous_stdin, int previous_stdout)
{
	size_t	i;
	int		fd;

	fd = previous_stdout;
	if (command.number_of_redirections)
	{
		i = 0;
		while (i < command.number_of_redirections)
		{
			printf("STDIN = %d et STDOUT = %d\n", previous_stdin, previous_stdout);
			if (ft_strcmp(command.redir[i].redir_type, ">>") == 0)
				fd = open(command.redir[i].filename, O_RDWR | O_CREAT | O_APPEND, 0644);
			else if (ft_strcmp(command.redir[i].redir_type, ">") == 0)
				fd = open(command.redir[i].filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (ft_strcmp(command.redir[i].redir_type, "<<") == 0)
				fd = create_heredoc(command.redir[i].filename);
			else if (ft_strcmp(command.redir[i].redir_type, "<") == 0)
				fd = open(command.redir[i].filename, O_RDONLY);
			if (fd == -1)
			{
				//gerer erreur
				ft_putstr_fd("error\n", 2);
				return (1);
			}
			i++;
		}
	}
	return (fd);
}
