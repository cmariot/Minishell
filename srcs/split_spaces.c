/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:30:38 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/24 14:56:48 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_fill_array(char *finalarray, char **array, int pos, int join)
{
	char	*tmp;

	finalarray = ft_strdup(array[pos]);
	join--;
	pos++;
	while (join > 0)
	{
		tmp = ft_strjoin(finalarray, array[pos]);
		finalarray = tmp;
		free(tmp);
		pos++;
		join--;
	}
	return (finalarray);
}

int	ft_count_join(char **array, int pos)
{
	int	i;

	i = 0;
	if (ft_strcmp(array[i], "\"") == 0)
	{
		pos++;
		while (ft_strcmp(array[i], "\"") != 0)
		{
			pos++;
			i++;
		}
		i++;
	}
	else if (ft_strcmp(array[i], "'") == 0)
	{
		pos++;
		while (ft_strcmp(array[i], "'") != 0)
		{
			pos++;
			i++;
		}
		i++;
	}
	return (i);
}

// parse the " and the ' in the array
char	**count_quotes_words(char **array, int *words)
{
	if (ft_strcmp(*array, "\"") == 0)
	{
		array++;
		while (ft_strcmp(*array, "\"") != 0)
			array++;
		words++;
	}
	else if (ft_strcmp(*array, "'") == 0)
	{
		array++;
		while (ft_strcmp(*array, "'") != 0)
			array++;
		words++;
	}
	return (array);
}

//count the number of words for the finalarray
int	ft_count_space(char **array)
{
	int	words;

	words = 1;
	while (*array != NULL)
	{
		if (ft_strcmp(*array, "\"") == 0 || ft_strcmp(*array, "'") == 0)
			array = count_quotes_words(array, &words);
		else if (ft_strcmp(*array, " ") == 0 || ft_strcmp(*array, "\t") == 0)
		{
			while (ft_strcmp(*array, " ") == 0 || ft_strcmp(*array, "\t") == 0)
				array++;
			if (*array != NULL)
				words++;
		}
		array++;
	}
	return (words);
}

//erreur : '>> test' -> SEGFAULT
char	**ft_split_space(char **array)
{
	char	**finalarray;
	int		words;
	int		i;
	int		pos;
	int		join;

	words = ft_count_space(array);
	finalarray = ft_calloc((words + 1), sizeof(char *));
	if (!finalarray)
		return (NULL);
	i = 0;
	pos = 0;
	while (words--)
	{
		while (ft_strcmp(array[pos], " ") == 0
			|| ft_strcmp(array[pos], "\t") == 0)
			pos++;
		join = ft_count_join(array, pos);
		finalarray[i] = join_fill_array(finalarray[i], array, pos, join);
		pos += join + 1;
		i++;
	}
	return (finalarray);
}
