/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:28:49 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/31 08:38:22 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* count the len of the word, like in parse_word() */

size_t	len_of_word(char *line, size_t *i)
{
	size_t	len;
	size_t	i_backup;

	i_backup = *i;
	parse_word(line, i);
	len = (*i) - i_backup;
	return (len);
}

/* return the len of the metacharacter which begings at line[i] */

size_t	len_of_metacharacter(char *line, size_t *i)
{
	if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
	{
		(*i) += 2;
		return (2);
	}
	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
	{
		(*i) += 2;
		return (2);
	}
	else if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
		(*i) += 1;
	return (1);
}

/* skip the blank character, get the len of the tokens and substr */

char	*get_token_value(char *line, size_t *index)
{
	char	*token;
	size_t	token_len;
	size_t	first_index;

	if (is_blank(line, *index) == TRUE)
		while (is_blank(line, *index) == TRUE)
			(*index)++;
	first_index = *index;
	if (is_a_metacharacter(line, index, FALSE) == TRUE)
		token_len = len_of_metacharacter(line, index);
	else
		token_len = len_of_word(line, index);
	token = ft_substr(line, first_index, token_len);
	return (token);
}

/* a loop used to fill the array of tokens */

int	fill_tokens_array(char **array, char *line, size_t number_of_tokens)
{
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (i < number_of_tokens)
	{
		array[i] = get_token_value(line, &index);
		if (array[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}
