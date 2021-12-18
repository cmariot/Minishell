/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 08:38:12 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/18 11:39:07 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Use this function to remove all the casess that are == str in
// the array old, returns a new array without them.
char	**remove_str_from_array(char **old, char *str)
{
	char	**new;
	int		i;
	int		len;
	int		j;

	i = 0;
	len = 0;
	while (old[i])
		if (ft_strcmp(old[i++], str) != 0)
			len++;
	new = ft_calloc((len + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strcmp(old[j], str) == 0)
			j++;
		else
			new[i++] = ft_strdup(old[j++]);
	}
	ft_free_array(old);
	return (new);
}

int	get_new_len(char **old, char *str)
{
	int	len;
	int	occurence;
	int	i;

	i = 0;
	len = 0;
	occurence = 0;
	while (old[i + 1])
	{
		if (ft_strcmp(old[i], str) == 0 && ft_strcmp(old[i], str) == 0)
		{
			len++;
			occurence++;
		}
		i++;
		len++;
	}
	return (len - occurence);
}

// This fuction return an array with 2 cases joined if they are == str
// for example, if in the array old we have 2 '<' that follows each other,
// the new array will have them joined.
char	**join_array_that_follow(char **old, char *str)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	len = get_new_len(old, str);
	new = ft_calloc((len + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strcmp(old[i], str) == 0 && ft_strcmp(old[i + 1], str) == 0)
		{
			new[i] = ft_strjoin(old[j], old[j + 1]);
			j += 2;
		}
		else
			new[i] = ft_strdup(old[j]);
		i++;
	}
	ft_free_array(old);
	return (new);
}

int	nb_of_str2_in_str1(char *str1, char *str2)
{
	int	nb;
	int	i;
	int	len_str2;

	nb = 0;
	len_str2 = ft_strlen(str2);
	i = 0;
	while (str1[i])
	{
		if (ft_memcmp(str1 + i, str2, len_str2) == 0)
		{
			i += len_str2;
			nb++;
		}
		else
			i++;
	}
	return (nb);
}
