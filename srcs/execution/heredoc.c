/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/07 10:52:06 by cmariot          ###   ########.fr       */
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

int	heredoc_return(char *file, int fd, char **line)
{
	if (*line)
		free(*line);
	close(fd);
	catch_signal(INTERACTIVE);
	rl_getc_function = rl_getc;
	if (return_global_exit_status() == 128 + SIGINT)
	{
		unlink(file);
		return (-1);
	}
	return (0);
}

int	create_heredoc(char *file, char *limiter, t_env *env)
{
	int		fd;
	char	*line;
	int		expansion;

	if (file == NULL || limiter == NULL)
		return (-1);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (heredoc_error());
	catch_signal(HEREDOC);
	expansion = need_to_expand_heredoc(&limiter);
	while (1)
	{
		line = readline("heredoc ➤ ");
		if (!line)
			ft_putchar('\n');
		if (ft_strcmp(line, limiter) == 0 || line == NULL || !line)
			break ;
		if (expansion == TRUE)
			line_expansion(&line, env);
		print(fd, "%s\n", line);
		if (line)
			free(line);
	}
	return (heredoc_return(file, fd, &line));
}
