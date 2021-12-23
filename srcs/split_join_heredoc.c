/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:19 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/23 19:20:06 by cmariot          ###   ########.fr       */
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

void	fill(char **array, int *i_array, char **newarray, int *i)
{
	if (array[*i_array][0] == '>' && array[*i_array + 1]
		&& array[*i_array + 1][0] == '>')
	{
		free(newarray[*i]);
		newarray[*i] = ft_strdup(">>");
		//realloc array pour supprimer case + 1 ?
		i_array++;
	}
	if (array[*i_array][0] == '<' && array[*i_array + 1]
		&& array[*i_array + 1][0] == '<')
	{
		free(newarray[*i]);
		newarray[*i] = ft_strdup("<<");
		//realloc array pour supprimer case + 1
		i_array++;
	}
}

char	**fill_newarray(char **newarray, char **array, int size)
{
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
		fill(array, &i_array, newarray, &i);
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
			if (array[i + 1][0] == '>')
				i++;
		if (array[i][0] == '<' && array[i + 1])
			if (array[i + 1][0] == '<')
				i ++;
		size++;
		i++;
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
