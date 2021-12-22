/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:30:38 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/22 13:30:58 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_fill_array(char *finalarray, char **array, int pos, int join)
{
	char	*tmp;
	int		size;

	size = ft_strlen(array[pos]);
	finalarray = ft_calloc((size + 1), sizeof(char));
	if (!finalarray)
		return (NULL);
	ft_strlcpy(finalarray, array[pos], (size + 1));
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

int	ft_count_join(char **array, int pos)
{
	int	i;

	i = 1;
	if (array[pos][0] == '\"')
	{
		pos++;
		while (array[pos][0] != '\"')
		{
			pos++;
			i++;
		}
		i++;
	}
	else if (array[pos][0] == '\'')
	{
		pos++;
		while (array[pos][0] != '\'')
		{
			pos++;
			i++;
		}
		i++;
	}
	return (i);
}

void	fill_finalarray(char **finalarray, char **array, int words)
{
	int	i;
	int	pos;
	int	join;

	i = 0;
	pos = 0;
	while (i < words)
	{
		while ((array[pos][0] == ' ' || array[pos][0] == '\t')
				&& array[pos])
			pos++;
		join = ft_count_join(array, pos);
		finalarray[i] = join_fill_array(finalarray[i], array, pos, join);
		pos += join;
		i++;
	}
}

int	ft_count_space(char **array)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (array[++i])
	{
		if (array[i][0] == '\"')
		{
			i++;
			while (array[i][0] != '\"' && array[i])
				i++;
			words++;
		}
		else if (array[i][0] == '\'')
		{
			i++;
			while (array[i][0] != '\'' && array[i])
				i++;
			words++;
		}
		else if (array[i][0] != ' ' && array[i][0] != '\t')
			words++;
	}
	return (words);
}

char	**ft_split_space(char **array)
{
	char	**finalarray;
	int		words;

	words = ft_count_space(array);
	finalarray = ft_calloc((words + 1), sizeof(char *));
	if (!finalarray)
		return (NULL);
	fill_finalarray(finalarray, array, words);
	return (finalarray);
}

//join_heredoc

char	**fill_newarray(char **newarray, char **array, int size)
{
	char	*tmp;
	int		i;
	int		i_array;
	int		len;

	i = 0;
	i_array = 0;
	while (i < size)
	{
		len = ft_strlen(array[i_array]);
		newarray[i] = ft_calloc((len + 1), sizeof(char));
		if (!newarray[i])
			return (NULL);
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
	return (newarray);
}

int	ft_count_heredoc(char **array)
{
	int	i;
	int	size;

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

char	**join_heredoc(char **array)
{
	char	**newarray;
	int		size;

	size = ft_count_heredoc(array);
	newarray = ft_calloc((size + 1), sizeof(char *));
	if (!newarray)
		return (NULL);
	newarray = fill_newarray(newarray, array, size);
	return (newarray);
}

//split_line

int	ft_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

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
	if (*str != 0 || sep)
		size--;
	return (size);
}

char	*ft_filltab(char *str, char *charset, int i, char *array)
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
	return (array);
}

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

char	**split_line(char *str, char *charset)
{
	char	**array;
	int		words;
	int		index;
	int		i;
	int		sizewords;

	words = ft_count_word(str, charset);
	array = ft_calloc((words + 1), sizeof(char *));
	if (!array)
		return (NULL);
	index = -1;
	i = 0;
	while (++index < words)
	{
		sizewords = ft_sizeof_word(&str[i], charset);
		array[index] = ft_calloc((sizewords + 1), sizeof(char));
		if (!array[index])
			return (NULL);
		array[index] = ft_filltab(str, charset, i, array[index]);
		i += sizewords;
	}
	return (array);
}

char	**split_command_line(char *line)
{
	char	**first_array;
	char	**second_array;
	char	**final_array;

	first_array = split_line(line, " \t|><\"\'");
	if (!first_array)
		return (NULL);
	second_array = join_heredoc(first_array);
	ft_free_array(first_array);
	if (!second_array)
		return (NULL);
	final_array = ft_split_space(second_array);
	ft_free_array(second_array);
	return (final_array);
}
