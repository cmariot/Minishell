/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_join_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:02:19 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/24 20:10:18 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_heredoc(char **array)
{
	int	size;
	int	i;
	int	join;

	size = 0;
	while (array[size] != NULL)
		size++;
	i = 0;
	join = 0;
	while (array[i + 2] != NULL)
	{
		if (ft_strcmp(array[i], "<") == 0 && ft_strcmp(array[i + 1], "<") == 0)
		{
			i++;
			join++;
		}
		if (ft_strcmp(array[i], ">") == 0 && ft_strcmp(array[i + 1], ">") == 0)
		{
			i++;
			join++;
		}
		i++;
	}
	return (size - join);
}

char	**join_heredoc(char **array)
{
	char	**newarray;
	int		size;
	int		i;
	int		j;

	size = ft_count_heredoc(array);
	newarray = ft_calloc((size + 1), sizeof(char *));
	if (!newarray)
		return (NULL);
	i = 0;
	j = 0;
	while (size--)
	{
		if (!ft_strcmp(array[j], "<") && !ft_strcmp(array[j + 1], "<"))
		{
			newarray[i] = ft_strdup("<<");
			j++;
		}
		else if (!ft_strcmp(array[j], ">") && !ft_strcmp(array[j + 1], ">"))
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
