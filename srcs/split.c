/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:14:11 by flee              #+#    #+#             */
/*   Updated: 2021/12/22 10:33:48 by cmariot          ###   ########.fr       */
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
	if (*str != 0 || sep)
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
			while(array[i][0] != '\"' && array[i])
				i++;
			words++;
		}
		else if (array[i][0] == '\'')
		{
			i++;
			while(array[i][0] != '\'' && array[i])
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
	char 	*tmp;
	int 	size;

	size = ft_strlen(array[pos]);
	finalarray = malloc(sizeof(char) * (size + 1));
	ft_strlcpy(finalarray,array[pos], (size + 1));
	join--;
	pos++;
	while (join > 0)
	{
		tmp = finalarray;
		finalarray = ft_strjoin(tmp, array[pos]);
		free(tmp);
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
		finalarray[i] = join_fill_array(finalarray[i], array, pos, join);
		pos += join;
		i++;
	}
	finalarray[i] = 0;
}

char 	**ft_split_space(char **array)
{
	char	**finalarray;
	int		words;

	words = ft_count_space(array);
	finalarray = (char **)malloc(sizeof(char *) * (words + 1));
	fill_finalarray(finalarray, array, words);
	return (finalarray);
}
//-------------------------------------HERDOC-----------------------------------------//

int		ft_count_herdoc(char **array)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (array[i])
	{
		if (array[i][0] == '>' && array[i + 1])
		{
			if (array[i + 1][0] == '>')
				i++;
		}
		if (array[i][0] == '<' && array[i + 1])
		{
			if (array[i + 1][0] == '<')
				i ++;
		}
		i++;
		size++;
	}
	return (size);
}

char 	**fill_newarray(char **newarray, char **array,int size)
{
	char *tmp;
	int i;
	int i_array;
	int len;

	i = 0;
	i_array = 0;
	while (i < size)
	{
		len = ft_strlen(array[i_array]);
		newarray[i] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strlcpy(newarray[i], array[i_array], (len + 1));
		if (array[i_array][0] == '>' && array[i_array + 1])
		{
			if (array[i_array + 1][0] == '>')
			{
				tmp = newarray[i];
				newarray[i] = ft_strjoin(tmp, array[i_array + 1]);
				free(tmp);
				i_array++;
			}
		}
		if (array[i_array][0] == '<' && array[i_array + 1])
		{
			if (array[i_array + 1][0] == '<')
			{
				tmp = newarray[i];
				newarray[i] = ft_strjoin(tmp, array[i_array + 1]);
				free(tmp);
				i_array++;
			}
		}
		i_array++;
		i++;
	}
	newarray[i] = 0;
	return(newarray);
}

char 	**join_herdoc(char **array)
{
	char	**newarray;
	int 	size;

	size = ft_count_herdoc(array);
	newarray = (char **)malloc(sizeof(char *) * (size +1));
	newarray = fill_newarray(newarray, array, size);
	ft_free_array(array);
	return (newarray);
}
//-------------------------------------------------------------------------------------//
char **split_all(char *line)
{
	char	**array;
	char 	*sep;
	char	**final_array;

	sep = " \t|><\"\'";
	array = split_line(line, sep);
	array = join_herdoc(array);
	final_array = ft_split_space(array);
	ft_free_array(array);
	return (final_array);
}
