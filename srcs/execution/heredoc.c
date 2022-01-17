/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 21:40:56 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_file(char *filename)
{
	int		heredoc_fd;
	char	*limiter;
	char	*line;

	heredoc_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC | O_APPEND,
			0644);
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

int	create_heredoc(char *filename, bool get_heredoc)
{
	int		heredoc_fd;

	if (get_heredoc == TRUE)
	{
		heredoc_fd = create_heredoc_file(filename);
	}
	else
	{
		heredoc_fd = open("here_doc", O_RDONLY);
		if (heredoc_fd == -1)
			return (-1);
	}
	return (heredoc_fd);
}
