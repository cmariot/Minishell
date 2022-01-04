/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_comments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 13:26:57 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 14:05:33 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_array_without_comment_len(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
	{
		if (array[len][0] != '#')
			len++;
		else
			break ;
	}
	return (len);
}

char	**remove_comments(char **splitted_line)
{
	char	**new_array;
	size_t	array_len;
	size_t	i;

	array_len = get_array_without_comment_len(splitted_line);
	if (array_len == 0)
		return (NULL);
	if (array_len == ft_arraylen(splitted_line))
		return (splitted_line);
	new_array = ft_calloc(array_len + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array_len--)
	{
		new_array[i] = ft_strdup(splitted_line[i]);
		i++;
	}
	ft_free_array(splitted_line);
	return (new_array);
}
