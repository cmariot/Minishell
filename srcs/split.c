/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:05:57 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 15:11:59 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

static int	ft_sizeof_word(char *str, char *charset)
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

static int	ft_count_word(char *str, char *charset)
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

static char	*ft_filltab(char *str, char *charset, int i, char *array)
{
	int	size;
	int	index;
	int	a;

	size = ft_sizeof_word(&str[i], charset);
	index = 0;
	a = 0;
	while (a < size)
	{
		array[index] = str[i];
		index++;
		i++;
		a++;
	}
	array[size] = 0;
	return (array);
}

static char	**ft_split_2(char *str, char *charset)
{
	char	**array;
	int		words;
	int		index;
	int		i;
	int		sizewords;

	words = ft_count_word(str, charset);
	array = malloc(sizeof(char **) * (words + 1));
	if (!array)
		return (NULL);
	index = -1;
	i = 0;
	while (++index < words)
	{
		sizewords = ft_sizeof_word(&str[i], charset);
		array[index] = malloc(sizeof(char *) * (sizewords + 1));
		if (!array[i])
			return (NULL);
		array[index] = ft_filltab(str, charset, i, array[index]);
		i += sizewords;
	}
	array[index] = 0;
	return (array);
}

char	**split_minishell(char *str)
{
	char	**array;
	char	*sep;

	sep = "\"\'><| ";
	array = ft_split_2(str, sep);
	return (array);
}

/*int	main(int argc, char **argv)
{
	char	*str;
	char	**array;
	int		i;
	if (argc && argv)
	{
		str = "a b c | d e f > g h i";
		array = split_minishell(str);
		i = 0;
		while (array[i])
		{
			printf("array[%d] = %s\n", i, array[i]);
			i++;
		}
	}
	return (0);
}*/
