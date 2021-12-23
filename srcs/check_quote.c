/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:52:28 by flee              #+#    #+#             */
/*   Updated: 2021/12/23 10:22:24 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Minishell should not interpret unclosed quotes
int	check_quote(char *line)
{
	int		i;
	char	c;
	int		ok;

	i = 0;
	ok = 1;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\''))
		{
			ok = 0;
			c = line[i];
			i++;
			while (line[i] != c && line[i] != '\0')
				i++;
			if (line[i] == c)
				ok = 1;
		}
		if (line[i] != 0)
			i++;
	}
	if (ok)
		return (1);
	return (0);
}

// Minishell should not interpret unspecified special characters like \ or ;
// j'suis pas sur de comprendre cette consigne, on ajoute cette fonction ??
// si on rencontre un ';' ou un '\' on arrete d'interpreter la commande ?
int	check_semicolon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
			return (0);
		else if (line[i] == '\\')
			return (0);
		i++;
	}
	return (1);
}
