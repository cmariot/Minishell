/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:11:04 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/12 12:53:16 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_closing_quote(char *str, size_t j)
{
	while (str[j + 1] != '\0')
	{
		str[j] = str[j + 1];
		j++;
	}
	str[j] = '\0';
}

void	remove_opening_quote(char *str, size_t j)
{
	while (str[j + 1] != '\0')
	{
		str[j] = str[j + 1];
		j++;
	}
	str[j] = '\0';
}

void	remove_quotes_in_str(char *str)
{
	size_t	i;
	char	quote_type;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote_type = str[i];
			remove_opening_quote(str, i);
			while (str[i] != quote_type && str[i])
				i++;
			//printf("I = %ld\n", i);
			if (i == 0 && str[i + 1] == '\0')
			{
				str[i] = 32;
			}
			else
				remove_closing_quote(str, i);
			i--;
		}
		i++;
	}
}

void	quotes_removal(char **array)
{
	size_t	i;
//	size_t	j;

	i = 0;
	while (array[i] != NULL)
	{
		remove_quotes_in_str(array[i]);
/*		j = 0;
		while (array[i][j] != '\0')
		{
			printf("ARRAY[%ld][%ld] = %c\n", i, j, array[i][j]);
			j++;
		}*/
		if (array[i][0] == '\0')
		{
			//if (array[i + 1][0] == '\0')
			//{
			//	free(array[i]);
		//		array[i] = ft_calloc(2, sizeof(char));
		//		array[i][0] = 32;
		//	}
		}
		i++;
	}
}
