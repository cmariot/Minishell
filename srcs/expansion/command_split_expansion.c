/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:11:07 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/28 10:35:02 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char quote_type, char *s, int *j)
{
	s++;
	(*j)++;
	while (*s && *s != quote_type)
	{
		s++;
		(*j)++;
	}
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;
	int		j;

	i = 0;
	words = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		j = 0;
		if (*s == '"' || *s == '\'')
			skip_quotes(*s, (char *)s, &j);
		s += j;
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			words++;
		}
		s++;
	}
	return (words);
}

static void	get_next_len_command(char **strs, unsigned int *str_len, char c)
{
	unsigned int	i;
	char			quote_type;

	*strs = *strs + *str_len;
	*str_len = 0;
	i = 0;
	while (**strs && **strs == c)
		(*strs)++;
	if (**strs == '"' || **strs == '\'')
	{
		quote_type = **strs;
		(*strs)++;
		while ((**strs) && **strs != quote_type)
			(*strs)++;
	}
	while ((*strs)[i])
	{
		if ((*strs)[i] == c)
			return ;
		(*str_len)++;
		i++;
	}
}

char	**command_split(char const *s, char c)
{
	char			**strs;
	int				words;
	int				i;
	char			*str;
	unsigned int	str_len;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	i = 0;
	str = (char *)s;
	str_len = 0;
	while (i < words)
	{
		get_next_len_command(&str, &str_len, c);
		strs[i] = (char *)malloc(sizeof(char) * (str_len + 1));
		if (strs[i] == NULL)
			return (NULL);
		ft_strlcpy(strs[i++], str, str_len + 1);
	}
	strs[i] = NULL;
	return (strs);
}