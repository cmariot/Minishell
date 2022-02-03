/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:11:07 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/03 20:37:57 by cmariot          ###   ########.fr       */
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

	*strs = *strs + *str_len;
	*str_len = 0;
	i = 0;
	while (**strs && **strs == c)
		(*strs)++;
	while ((*strs)[i])
	{
		if ((*strs)[i] == c)
			return ;
		(*str_len)++;
		i++;
	}
}

char	**command_split(char *str, char c)
{
	char			**array;
	int				array_len;
	int				i;
	unsigned int	str_len;

	if (!str)
		return (NULL);
	array_len = count_words(str, c);
	array = ft_calloc(sizeof(char *), array_len + 1);
	if (!array)
		return (NULL);
	i = 0;
	str_len = 0;
	while (i < array_len)
	{
		get_next_len_command(&str, &str_len, c);
		array[i] = ft_calloc(sizeof(char), (str_len + 1));
		if (array[i] == NULL)
			return (NULL);
		ft_strlcpy(array[i++], str, str_len + 1);
	}
	return (array);
}
