/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 01:34:03 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_heredoc_name(void)
{
	char	*name;
	int		number;

	number = 0;
	name = ft_strjoin("heredoc_", ft_itoa(number));
	if (name == NULL)
		return (NULL);
	if (access(name, F_OK) != -1)
	{
		while (access(name, F_OK) != -1)
		{
			if (name)
				free(name);
			number++;
			name = ft_strjoin("heredoc_", ft_itoa(number));
			if (name == NULL)
				return (NULL);
		}
	}
	return (name);
}

int	create_heredoc_file(char *filename, char *limiter_without_bn)
{
	int		heredoc_fd;
	char	*limiter_with_bn;
	char	*line;

	heredoc_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_APPEND,
			0644);
	if (heredoc_fd == -1)
		return (-1);
	limiter_with_bn = ft_strjoin(limiter_without_bn, "\n");
	while (1)
	{
		ft_putstr_fd("heredoc ➤ ", 1);
		line = get_next_line(0);
		if (ft_strcmp(line, limiter_with_bn) == 0)
			break ;
		else
		{
			ft_putstr_fd(line, heredoc_fd);
			free(line);
		}
	}
	free(line);
	free(limiter_with_bn);
	return (heredoc_fd);
}

int	create_heredoc(char *filename, bool get_heredoc, char *limiter)
{
	int		heredoc_fd;

	if (get_heredoc == TRUE)
	{
		heredoc_fd = create_heredoc_file(filename, limiter);
	}
	else
	{
		heredoc_fd = open(filename, O_RDONLY);
		if (heredoc_fd == -1)
			return (-1);
	}
	return (heredoc_fd);
}
