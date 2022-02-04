/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 21:40:17 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/04 12:24:38 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_value(char **str, size_t *i, char **name, char **value);

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

int	heredoc_return(char *file, int fd)
{
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

bool	need_to_expand_heredoc(char **limiter)
{
	size_t	len_before;
	size_t	len_after;

	len_before = ft_strlen(*limiter);
	str_quotes_removal(limiter);
	len_after = ft_strlen(*limiter);
	if (len_before != len_after)
		return (FALSE);
	else
		return (TRUE);
}

int	get_name_in_line(char **str, size_t *i, t_env *env)
{
	int		len;
	char	*name;
	char	*value;

	if ((*str)[*i + 1] == '\'' || (*str)[*i + 1] == '"')
		return (0);
	len = 0;
	if (ft_isdigit((*str)[*i + len + 1]) == TRUE)
		while (ft_isdigit((*str)[*i + len + 1]) == TRUE)
			len++;
	else if ((*str)[*i + 1] == '?')
		return (expand_exit_status(str, i));
	else
		while (ft_isalnum((*str)[*i + len + 1]) == TRUE)
			len++;
	if (len == 0)
		return (0);
	name = ft_substr((*str), *i + 1, len);
	value = get_env_value(name, env);
	if (search_value(str, i, &name, &value) == -1)
		return (1);
	return (0);
}

int	search_dollar_in_line(char **str, t_env *env)
{
	size_t	i;
	int		ret;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			ret = get_name_in_line(str, &i, env);
			if (ret == 1)
				return (-1);
		}
		i++;
	}
	return (0);
}

void	line_expansion(char **line, t_env *env)
{
	if (search_dollar_in_line(line, env) == -1)
	{
		if (*line)
			free(*line);
		*line = ft_calloc(sizeof(char), 1);
	}
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
	global_exit_status(0);
	rl_getc_function = getc;
	expansion = need_to_expand_heredoc(&limiter);
	while (1)
	{
		line = readline("heredoc ➤ ");
		//if (line == NULL)
		//	print(1, "\n");
		if (ft_strcmp(line, limiter) == 0 || line == NULL || !line)
			break ;
		if (expansion == TRUE)
			line_expansion(&line, env);
		print(fd, "%s\n", line);
		if (line)
			free(line);
	}
	if (line)
		free(line);
	return (heredoc_return(file, fd));
}
