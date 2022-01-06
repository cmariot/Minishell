/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:41:45 by flee              #+#    #+#             */
/*   Updated: 2022/01/04 12:41:47 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*new;
	size_t	i;

	new = malloc(size * count);
	if (!new)
		return (NULL);
	i = 0;
	while (i < count * size)
		new[i++] = 0;
	return (new);
}

//--------------------------------------------------------------------------------------------------------------------//

size_t size(char **array)
{
    int i;
    int len;
    int state;

    i = 0;
    len = 0;
    state = 1;
    while(array[i])
    {
        if (((ft_strcmp(array[i], " ") != 0)
                && (ft_strcmp(array[i], "\t") != 0)) 
                    && (state == 1))
        {
            len++;
            state = 0;
        }
        else if (ft_strcmp(array[i], " ") == 0
                || (ft_strcmp(array[i], "\t") == 0)) 
        {
            len++;
            state = 1;
        }
        i++;
    }
    return (len);
}

int     find_pos(int pos, char **array)
{
    while ((ft_strcmp(array[pos], " ") != 0) 
                && (ft_strcmp(array[pos], "\t") != 0)
                    && array[pos])
    {
        pos++;
    }
}

int     need_trim(char *array)
{
    int i;

    i = 0;
    while (array[i] == '\"' 
            || array[i] == '\'')
        i++;
    if (array[i] == 0)
        return (0);
    else
        return (1);
}

char    **trim_quote(char **array)
{
    int i;

    i = 0;

    while (array[i])
    {
        if (need_trim(array[i]))
            ft_strtrim(array[i], "\"\'");
        i++;
    }
}

char    **del_quote_command(char **array)
{
    char    **array_no_quote;
    int     i;
    int     pos;

    i = 0;
    pos = 0;
    array = trim_quote(array);
    array_no_quote = ft_calloc((size(array) + 1), sizeof(char *));
    while (i < size(array))
    {
        array_no_quote[i] = join_array_or_not(array, array_no_quote[i], pos);
        i++;
        pos = find_pos(pos, array);
    }
    return (array_no_quote);
}


int main (void)
{
    char **array;
    char **final_array;

    array[0] = " ";
    array[1] = "\"e\"";
    array[2] = "c";
    array[3] = "\"\"";
    array[4] = "ho";
    array[5] = "\"\"";
    array[6] = " ";
    array[7] = "boum";
    array[8] = " ";
    array[9] = "\"boum\"";
    array[10] = 0;
    final_array = del_quote_command(array);
}
