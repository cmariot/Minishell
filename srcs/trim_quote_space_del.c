/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_in_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:16:10 by flee              #+#    #+#             */
/*   Updated: 2021/12/31 11:16:12 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_space(char **array)
{
	int	words;

	words = 0;
	while (*array != NULL)
	{
		if (ft_strcmp(*array, " ") == 0 || ft_strcmp(*array, "\t") == 0)
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


char    **trim_quote_space_del(char **third_array)
{
    char    **final_array;
    int     size;
    int     i;
    int     len;

    size = count_space(third_array);
    i = 0;
    final_array = ft_calloc(size + 1,sizeof(char *));
    while (i < size && *third_array)
    {
        while((ft_strcmp(*third_array, " ") == 0)
            || (ft_strcmp(*third_array, "\t") == 0))
            (*third_array)++;
        if (*third_array[0] == '\'' || *third_array[0] == '\"')
        {
            len = ft_strlen(*third_array);
            final_array[i] = ft_substr(*third_array, 1, (len - 3));
        }
        else
            final_array[i] = ft_strdup(*third_array);
        (*third_array)++;
        i++;
    }
    return (final_array);
}
