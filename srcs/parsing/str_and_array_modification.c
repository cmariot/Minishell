/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_and_array_modification.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:02:13 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/24 13:19:41 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_name_from_str(char *name, char *str, size_t *i)
{
	size_t	name_len;
	size_t	j;

	name_len = ft_strlen(name);
	j = *i;
	while (str[name_len + j + 1] != '\0')
	{
		str[j] = str[name_len + j + 1];
		str[name_len + j] = '\0';
		j++;
	}
	return (0);
}

int	add_value_to_str(char **str, char *name, char *value, size_t *i)
{
	size_t	new_len;
	char	*new_str;
	size_t	j;
	size_t	k;

	new_len = ft_strlen(*str) - (ft_strlen(name) + 1) + ft_strlen(value) + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	if (!new_str)
		return (1);
	j = 0;
	while (j < *i)
	{
		new_str[j] = (*str)[j];
		j++;
	}
	k = 0;
	while (k < ft_strlen(value))
		new_str[j++] = value[k++];
	k = 0;
	while (j < new_len)
		new_str[j++] = (*str)[(*i) + 1 + ft_strlen(name) + k++];
	free(*str);
	*str = new_str;
	*i = ft_strlen(value) + *i - 1;
	return (0);
}

int	remove_from_str(char **str, size_t *i, size_t name_len)
{
	size_t	j;
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(*str) - name_len;
	new_str = ft_calloc(new_len, sizeof(char));
	if (!new_str)
		return (1);
	j = 0;
	if (*i > 0)
	{
		while (j < *i)
		{
			new_str[j] = (*str)[j];
			j++;
		}
	}
	if (new_len > j)
		while (j < new_len)
			new_str[j++] = (*str)[*i + name_len++ + 1];
	free(*str);
	*str = new_str;
	(*i)--;
	return (0);
}

int	remove_from_array(char **splitted_line, int i)
{
	int	j;

	if (splitted_line[i + 1] == NULL)
	{
		free(splitted_line[i]);
		splitted_line[i] = NULL;
		return (0);
	}
	j = i;
	while (splitted_line[j + 1] != NULL)
	{
		free(splitted_line[j]);
		splitted_line[j] = ft_strdup(splitted_line[j + 1]);
		if (!splitted_line[j])
			return (1);
		j++;
	}
	free(splitted_line[j]);
	splitted_line[j] = NULL;
	return (0);
}
