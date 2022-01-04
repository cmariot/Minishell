/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:00:15 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 14:02:22 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;
	int		index;
	int		sizewords;

	words = ft_count_word(str, charset);
	array = ft_calloc((words + 1), sizeof(char *));
	if (!array)
		return (NULL);
	index = 0;
	i = 0;
	while (index < words)
	{
		sizewords = ft_sizeof_word(&str[i], charset);
		array[index] = ft_substr(str, i, sizewords);
		i += sizewords;
		index++;
	}
	return (array);
}

char	**split_command_line(char *line)
{
	char	**first_array;
	char	**second_array;
	char	**third_array;
	char	**fourth_array;
	char	**final_array;

	first_array = split_line(line, " \t|><\"\';");
	ft_putarray("first", first_array);
	if (!first_array)
		return (NULL);
	second_array = join_heredoc(first_array);
	ft_putarray("second", second_array);
	ft_free_array(first_array);
	if (!second_array)
		return (NULL);
	third_array = join_quote(second_array);
	ft_putarray("third", third_array);
	ft_free_array(second_array);
	if (!second_array)
		return (NULL);
	fourth_array = trim_quote_space_del(third_array);
	ft_free_array(third_array);
	if (!third_array)
		return (NULL);
	final_array = remove_comments(fourth_array);
	ft_putarray("final", final_array);
	return (final_array);
}
