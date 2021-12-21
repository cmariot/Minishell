/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:14:11 by flee              #+#    #+#             */
/*   Updated: 2021/12/20 14:23:10 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

int		ft_sizeof_word(char *str, char *charset)
{
	int	size;
	int sep;

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

int		ft_count_word(char *str, char *charset)
{
	int words;
	int state;

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
	int size;
	int index;
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
	return(array);
}

char	**split_line(char *str, char *charset)
{
	char	**array;
	int		words;
	int 	index;
	int 	i;
	int 	sizewords;

	words = ft_count_word(str, charset);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	index = -1;
	i = 0;
	while (++index < words)
	{
		sizewords = ft_sizeof_word(&str[i], charset);
		array[index] = (char *)malloc(sizeof(char) * (sizewords + 1));
		array[index] = ft_filltab(str, charset, i, array[index]);
		i += sizewords;
	}
	array[index] = 0;
	return (array);
}

int		ft_count_space(char **array)
{
	int i;
	int words;

	i = -1;
	words = 0;
	while (array[++i])
	{
		if (array[i][0] == '\"')
		{
			i++;
			while(array[i][0] != '\"')
				i++;
			words++;
		}
		else if (array[i][0] == '\'')
		{
			i++;
			while(array[i][0] != '\'')
				i++;
			words++;
		}
		else if (array[i][0] != ' ' && array[i][0] != '\t')
			words++;
	}
	return (words);
}

int		ft_count_join(char **array, int pos)
{
	int i;

	i = 1;
	if (array[pos][0] == '\"')
	{
		pos++;
		while(array[pos][0] != '\"')
		{
			pos++;
			i++;
		}
		i++;
	}
	else if (array[pos][0] == '\'')
	{
		pos++;
		while(array[pos][0] != '\'')
		{
			pos++;
			i++;
		}
		i++;
	}
	return (i);
}

int 	find_pos(char **array, int pos)
{
	while ((array[pos][0] == ' ' || array[pos][0] == '\t') 
			&& array[pos])
		pos++;
	return (pos);
}

char  *join_fill_array(char *finalarray,char **array, int pos, int join)
{
	int size;

	size = ft_strlen(array[pos]);
	printf("len = %d\n",size);
	finalarray = malloc(sizeof(char) * (size + 1));
	ft_strlcpy(finalarray,array[pos], (size + 1));
	join--;
	while (join > 0)
	{
		finalarray = ft_strjoin(finalarray, array[pos]);
		pos++;
		join--;
	}
	return (finalarray);
}

void fill_finalarray(char **finalarray, char **array, int words)
{
	int i;
	int pos;
	int join;
	
	i = 0;
	pos = 0;
	while (i < words)
	{
		pos = find_pos(array, pos);
		join = ft_count_join(array, pos);
		printf("pos = %d join = %d\n", pos, join);
		finalarray[i] = join_fill_array(finalarray[i], array, pos, join);
		pos += join;
		i++;
	}
}

char 	**ft_split_space(char **array)
{
	char	**finalarray;
	int		words;

	words = ft_count_space(array);
	printf("words = %d\n",words);
	finalarray = (char **)malloc(sizeof(char *) * (words + 1));
	fill_finalarray(finalarray, array, words);
	return (finalarray);
}

char **split_all(char *line)
{
	char	**array;
	char 	*sep;
	char	**final_array;

	sep = " \t|><\"\'";
	array = split_line(line, sep);
	int i = 0;
	while (array[i])
	{
		printf("array[%d] = %s\n",i,array[i]);
		i++;
	}
	i = 0;
	final_array = ft_split_space(array);
	while (final_array[i])
	{
		printf("final_array[%d] = %s\n",i,final_array[i]);
		i++;
	}
	return (final_array);
}
