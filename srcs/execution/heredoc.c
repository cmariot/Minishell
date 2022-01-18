/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 08:35:33 by cmariot          ###   ########.fr       */
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
	if (access(name, F_OK) == 0)
	{
		while (access(name, F_OK) == 0)
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

int	heredoc_error(void)
{
	ft_putstr_fd("minishell: here_doc: read-only file system.\n", 2);
	return (-1);
}

int	create_heredoc(char *file, char *limiter)
{
	int		fd;
	char	*limiter_with_bn;
	char	*line;

	if (file == NULL)
		return (heredoc_error());
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (heredoc_error());
	limiter_with_bn = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd("heredoc ➤ ", 1);
		line = get_next_line(0);
		if (ft_strcmp(line, limiter_with_bn) == 0)
			break ;
		else
		{
			ft_putstr_fd(line, fd);
			free(line);
		}
	}
	free(line);
	free(limiter_with_bn);
	return (fd);
}
