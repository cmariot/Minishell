/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:19 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/24 21:24:30 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_heredoc(char **array)
{
	size_t	size;
	size_t	join;

	size = 0;
	while (array[size] != NULL)
		size++;
	join = 0;
	while (*array != NULL)
	{
		if (ft_strcmp(*array, "<") == 0 && *array + 1
			&& ft_strcmp(*array + 1, "<") == 0)
		{
			array++;
			join++;
		}
		else if (ft_strcmp(*array, ">") == 0 && *array + 1
			&& ft_strcmp(*array + 1, ">") == 0)
		{
			array++;
			join++;
		}
		array++;
	}
	return (size - join);
}

char	**join_heredoc(char **array)
{
	char	**newarray;
	size_t	i;
	size_t	j;

	newarray = ft_calloc((ft_count_heredoc(array) + 1), sizeof(char *));
	if (!newarray)
		return (NULL);
	i = 0;
	j = 0;
	while (array[j] != NULL)
	{
		if (!ft_strcmp(array[j], "<") && array[j + 1]
			&& !ft_strcmp(array[j + 1], "<"))
		{
			newarray[i] = ft_strdup("<<");
			j++;
		}
		else if (!ft_strcmp(array[j], ">") && array[j + 1]
			&& !ft_strcmp(array[j + 1], ">"))
		{
			newarray[i] = ft_strdup(">>");
			j++;
		}
		else
			newarray[i] = ft_strdup(array[j]);
		j++;
		i++;
	}
	return (newarray);
}
