/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_str_from_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 08:38:12 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/18 09:25:38 by cmariot          ###   ########.fr       */
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

// This fuction return an array with 2 cases joined if they are == str
// for example, if in the array old we have 2 '<' that follows each other,
// the new array will hale them joined.
char	**join_array_that_follow(char **old, char *str)
{
	char	**new;
	int		occurence;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = 0;
	occurence = 0;
	while (old[i + 1])
	{
		if (ft_strcmp(old[i], str) == 0 && ft_strcmp(old[i], str) == 0)
		{
			printf("deux str se suivent\n");
			len++;
			occurence++;
		}
		i++;
		len++;
	}
	printf("taille nouveau tableau = %d\n", len - occurence);
	new = ft_calloc((len + 1 - occurence), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < (len - occurence))
	{
		if (ft_strcmp(old[i], str) == 0 && ft_strcmp(old[i + 1], str) == 0)
		{
			printf("join %s & %s\n", old[j], old[j + 1]);
			new[i] = ft_strjoin(old[j], old[j + 1]);
			j += 2;
		}
		else
		{
			printf("dup %s\n", old[i]);
			new[i] = ft_strdup(old[i]);
		}
		i++;
	}
	return (new);
}

int	main(int argc, char **argv, char **env)
{
	char	**old;
	int		len;
	int		i;

	if (argc && *argv && *env)
	{
		len = 5;
		old = ft_calloc(len + 1, sizeof(char *));
		old[0] = ft_strdup("1");
		old[1] = ft_strdup("2");
		old[2] = ft_strdup("3");
		old[3] = ft_strdup("<");
		old[4] = ft_strdup("<");
//		i = 0;
//		while (old[i])
//		{
//			printf("old[%d] = [%s]\n", i, old[i]);
//			i++;
//		}
//		old = remove_str_from_array(old, "3");
//		printf("AFTER\n");
//		i = 0;
//		while (old[i])
//		{
//			printf("old[%d] = [%s]\n", i, old[i]);
//			i++;
//		}
		old = join_array_that_follow(old, "<");
		printf("AFTER 2\n");
		i = 0;
		while (old[i])
		{
			printf("old[%d] = [%s]\n", i, old[i]);
			i++;
		}
	}
	return (0);
}
