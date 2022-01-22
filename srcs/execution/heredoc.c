/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/22 16:27:27 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_heredoc_name(void)
{
	char	*name;
	char	*str_itoa;
	int		number;

	number = 0;
	while (1)
	{
		str_itoa = ft_itoa(number);
		if (str_itoa == NULL)
			return (NULL);
		name = ft_strjoin("heredoc_", str_itoa);
		free(str_itoa);
		if (name == NULL)
			return (NULL);
		if (access(name, F_OK) != 0)
			break ;
		free(name);
		number++;
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
	char	*line;

	if (file == NULL || limiter == NULL)
		return (-1);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (heredoc_error());
	catch_signal(HEREDOC);
	while (1)
	{
		ft_putstr_fd("heredoc ➤ ", STDOUT);
		line = gnl_without_bn(STDIN);
		if (ft_strcmp(line, limiter) == 0 || line == NULL)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	if (return_global_exit_status() >= 128)
	{
		printf("KO\n");
		return (-1);
	}
	catch_signal(COMMAND);
	free(line);
	close(fd);
	return (0);
}
