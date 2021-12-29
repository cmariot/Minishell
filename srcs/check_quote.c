/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 09:52:28 by flee              #+#    #+#             */
/*   Updated: 2021/12/29 12:40:54 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Minishell should not interpret unclosed quotes
int	check_quote(char *line)
{
	int		i;
	char	c;
	bool	ok;

	i = 0;
	ok = TRUE;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\''))
		{
			ok = FALSE;
			c = line[i];
			i++;
			while (line[i] != c && line[i] != '\0')
				i++;
			if (line[i] == c)
				ok = TRUE;
		}
		i++;
	}
	if (ok == TRUE)
		return (1);
	else
		printf("minishell does not interpret unclosed quotes.\n");
	return (0);
}
