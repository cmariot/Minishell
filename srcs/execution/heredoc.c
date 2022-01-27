/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/27 17:41:10 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_heredocs(t_simple command)
{
	size_t	i;

	if (command.number_of_redirections == 0)
		return ;
	i = 0;
	while (i < command.number_of_redirections)
	{
		if (ft_strcmp(command.redir[i].redir_type, "<<") == 0)
			unlink(command.redir[i].filename);
		i++;
	}
	return ;
}

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
	print(2, "minishell: here_doc: read-only file system.\n");
	return (-1);
}

int	heredoc_return(char *file)
{
	if (return_global_exit_status() == 128 + SIGINT)
	{
		unlink(file);
		return (-1);
	}
	return (0);
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
		line = readline("heredoc ➤ ");
		if (ft_strcmp(line, limiter) == 0 || line == NULL)
			break ;
		print(fd, "%s\n", line);
		free(line);
	}
	catch_signal(INTERACTIVE);
	close(fd);
	if (line)
		free(line);
	return (heredoc_return(file));
}
