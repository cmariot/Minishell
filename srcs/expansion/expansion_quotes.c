/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:11:04 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/24 12:55:34 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(char *str, size_t j)
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
			remove_quote(str, i);
			while (str[i] != quote_type && str[i])
				i++;
			if (i == 0 && str[i + 1] == '\0')
				str[i] = 32;
			else
				remove_quote(str, i);
			i--;
		}
		i++;
	}
}

void	quotes_removal(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		remove_quotes_in_str(array[i]);
		i++;
	}
}
