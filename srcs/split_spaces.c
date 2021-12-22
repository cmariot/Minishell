/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:30:38 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/22 15:09:09 by cmariot          ###   ########.fr       */
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
