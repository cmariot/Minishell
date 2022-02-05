/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:41:13 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 12:47:07 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	need_to_expand_heredoc(char **limiter)
{
	size_t	len_before;
	size_t	len_after;

	global_exit_status(0);
	rl_getc_function = getc;
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
