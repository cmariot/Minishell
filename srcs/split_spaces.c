/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:30:38 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/28 17:07:30 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_fill_array(char *finalarray, char **array, int pos, int join)
{
	char	*tmp;

	if (join == 1)
		finalarray = ft_strdup(array[pos]);
	else
	{
		finalarray = ft_strdup(array[pos]);
		while (join-- -1)
		{
			pos++;
			tmp = ft_strjoin(finalarray, array[pos]);
			free(finalarray);
			finalarray = tmp;
		}
	}
	return (finalarray);
}

int	ft_count_join(char **array, int pos)
{
	int	i;

	i = 0;
	if (ft_strcmp(array[pos], "\"") == 0)
	{
		pos++;
		while (array[pos + 1] && ft_strcmp(array[pos], "\"") != 0)
		{
			pos++;
			i++;
		}
		i++;
	}
	else if (ft_strcmp(array[pos], "'") == 0)
	{
		pos++;
		while (array[pos + 1] && ft_strcmp(array[pos], "'") != 0)
		{
			pos++;
			i++;
		}
		i++;
	}
	return (i + 1);
}

// parse the " and the ' in the array
void	count_quotes_words(char ***array, int *words)
{
	if (ft_strcmp(**array, "\"") == 0)
	{
		(*array)++;
		while (ft_strcmp(**array, "\"") != 0 && (**array) != NULL)
			(*array)++;
		words++;
	}
	else if (ft_strcmp(**array, "'") == 0)
	{
		(*array)++;
		while (ft_strcmp(**array, "'") != 0 && (**array) != NULL)
			(*array)++;
		words++;
	}
}

//count the number of words for the finalarray
int	ft_count_space(char **array)
{
	int	words;

	words = 0;
	while (*array != NULL)
	{
		if (ft_strcmp(*array, "\"") == 0 || ft_strcmp(*array, "'") == 0)
			count_quotes_words(&array, &words);
		else if (ft_strcmp(*array, " ") == 0 || ft_strcmp(*array, "\t") == 0)
		{
			array++;
			continue ;
		}
		else if (*array != NULL)
			words++;
		else if (*array == NULL)
			break ;
		array++;
	}
	return (words);
}

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
	while (words-- && array[pos] != NULL)
	{
		while (ft_strcmp(array[pos], " ") == 0
			|| ft_strcmp(array[pos], "\t") == 0)
			pos++;
		join = ft_count_join(array, pos);
		finalarray[i] = join_fill_array(finalarray[i], array, pos, join);
		pos += join;
		i++;
	}
	return (finalarray);
}
