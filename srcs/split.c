/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 12:14:11 by flee              #+#    #+#             */
/*   Updated: 2021/12/21 09:41:41 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"

int		ft_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			return (1);
	return (0);
}

int		ft_sizeof_word(char *str, char *charset)
{
	int	size;
	int sep;

	size = 0;
	sep = ft_charset(*str, charset);
	if (sep)
		return (1);
	while (*str && !sep)
	{
		sep = ft_charset(*str, charset);
		++size;
		++str;
	}
	if (*str != 0)
		size--;
	return (size);
}

int		ft_count_word(char *str, char *charset)
{
	int words;
	int state;

	words = 0;
	state = 1;
	while (*str)
	{
		if (ft_charset(*str, charset))
        {
			state = 1;
            words++;
        }
		else
		{
			if (state == 1)
				++words;
			state = 0;
		}
		++str;
	}
	return (words);
}

char	*ft_filltab(char *str, char *charset, int i, char *tab)
{
	int size;
	int index;
	int	a;

	size = ft_sizeof_word(&str[i], charset);
	index = 0;
	a = 0;
	while (a < size)
	{
		tab[index] = str[i];
		index++;
		i++;
		a++;
	}
	tab[size] = 0;
	return(tab);
}

char	**ft_split_piscine(char *str, char *charset)
{
	char	**tab;
	int		words;
	int 	index;
	int 	i;

	words = ft_count_word(str, charset);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	index = -1;
	i = 0;
	while (++index < words)
	{
		int sizewords = ft_sizeof_word(&str[i], charset);
		tab[index] = (char *)malloc(sizeof(char) * (sizewords + 1));
		tab[index] = ft_filltab(str, charset, i, tab[index]);
		i += sizewords;
	}
	tab[index] = 0;
	return (tab);
}
//------------------------------------------------------------------------------------------//
int		ft_count_space(char **array)
{
	int i;
	int words;

	i = -1;
	words = 0;
	while (array[++i])
	{
		if (array[i][0] == '\"')
		{
			i++;
			while(array[i][0] != '\"')
				i++;
			words++;
		}
		else if (array[i][0] == '\'')
		{
			i++;
			while(array[i][0] != '\'')
				i++;
			words++;
		}
		else if (array[i][0] != ' ' && array[i][0] != '\t')
			words++;
	}
	return (words);
}

int		ft_count_join(char **array, int pos)
{
	int i;

	i = 1;
	if (array[pos][0] == '\"')
	{
		pos++;
		while(array[pos][0] != '\"')
		{
			pos++;
			i++;
		}
		i++;
	}
	else if (array[pos][0] == '\'')
	{
		pos++;
		while(array[pos][0] != '\'')
		{
			pos++;
			i++;
		}
		i++;
	}
	return (i);
}

int 	find_pos(char **array, int pos)
{
	while ((array[pos][0] == ' ' || array[pos][0] == '\t')
			&& array[pos])
		pos++;
	return (pos);
}

//--------------------------------LIBFT---------------------------------//

size_t	ft_strlen (const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	index;

	destlen = 0;
	srclen = ft_strlen(src);
	index = 0;
	while (dst[destlen] && destlen < size)
		destlen++;
	while ((src[index]) && ((destlen + index + 1) < size))
	{
		dst[destlen + index] = src[index];
		index++;
	}
	if (destlen != size)
		dst[destlen + index] = '\0';
	return (destlen + srclen);
}

size_t	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	int				src_len;

	i = 0;
	src_len = 0;
	if (src)
	{
		while (src[src_len])
			src_len++;
		if (size > 0)
		{
			while (src[i] && (i < (size - 1)))
			{
				dest[i] = src[i];
				i++;
			}
			dest[i] = '\0';
		}
	}
	return (src_len);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		cmpt1;
	int		cmpt2;
	char	*str;

	cmpt1 = ft_strlen((char *)s1);
	cmpt2 = cmpt1 + ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (cmpt2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, cmpt1 + 1);
	ft_strlcat(str, (char *)s2, cmpt2 + 1);
		return (str);

	return (NULL);
}

//--------------------------------LIBFT---------------------------------//

char  *join_fill_array(char *finalarray,char **array, int pos, int join)
{
	while (join > 0)
	{
		finalarray = ft_strjoin(finalarray, array[pos]);
		pos++;
		join--;
	}
	return (finalarray);
}

void fill_finalarray(char **finalarray, char **array, int words)
{
	int i;
	int pos;
	int join;

	i = 0;
	pos = 0;
	while (i < words)
	{
		pos = find_pos(array, pos);
		join = ft_count_join(array, pos);
		finalarray[i] = join_fill_array(finalarray[i], array, pos, join);
		printf("final = %s\n",finalarray[i]);
		pos += join;
		i++;
	}
}

char 	**ft_split_space(char **array)
{
	char	**finalarray;
	int		words;

	words = ft_count_space(array);
	printf("words = %d\n", words);
	finalarray = (char **)malloc(sizeof(char *) * (words + 1));
	fill_finalarray(finalarray, array, words);
	return (finalarray);
}
