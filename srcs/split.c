/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:05:57 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 19:24:53 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sizeof_word(char *str, char *charset)
{
	int	size;
	int	sep;

	size = 0;
	sep = ft_charset(*str, charset);
	if (sep)
		return (1);
	while (*str && !sep)
	{
		sep = ft_charset(*str, charset);
		++size;
		++str;
	}
	if (*str != 0)
		size--;
	return (size);
}

// Tout ce qui est apres un charactere # est considere
// comme un commentaire en bash, tester avec "echo abcd #efg",
// on devrait s'arreter quand on voit le charactere '#'
int	ft_count_word(char *str, char *charset)
{
	int	words;
	int	state;

	words = 0;
	state = 1;
	while (*str)
	{
		if (ft_charset(*str, charset))
		{
			state = 1;
			words++;
		}
		else
		{
			if (state == 1)
				++words;
			state = 0;
		}
		++str;
	}
	return (words);
}

char	*ft_filltab(char *str, char *charset, int i, char *array)
{
	int	size;
	int	index;

	size = ft_sizeof_word(&str[i], charset);
	index = 0;
	while (index < size)
	{
		array[index++] = str[i++];
	}
	return (array);
}

char	**ft_split_2(char *str, char *charset)
{
	char	**array;
	int		words;
	int		index;
	int		i;
	int		sizewords;

	words = ft_count_word(str, charset);
	array = ft_calloc((words + 1), sizeof(char **));
	if (!array)
		return (NULL);
	index = -1;
	i = 0;
	while (++index < words)
	{
		sizewords = ft_sizeof_word(&str[i], charset);
		array[index] = ft_calloc((sizewords + 1), sizeof(char *));
		if (!array[i])
			return (NULL);
		array[index] = ft_filltab(str, charset, i, array[index]);
		i += sizewords;
	}
	return (array);
}

char	**split_line(char *str)
{
	char	**array;
	char	*sep;

	sep = "\"\'><| ";
	array = ft_split_2(str, sep);
	return (array);
}
