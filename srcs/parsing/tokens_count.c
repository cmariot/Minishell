/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:28:13 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/31 11:34:20 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return true if line[i] is a metacharacter,
 * if the option opt is TRUE the value of i is increased by
 * the len of the metacharacter */

bool	is_a_metacharacter(char *line, size_t *i, bool opt)
{
	if (line[*i] == '<' && line[*i + 1] && line[*i + 1] == '<')
	{
		if (opt == TRUE)
			(*i) += 2;
		return (TRUE);
	}
	else if (line[*i] == '>' && line[*i + 1] && line[*i + 1] == '>')
	{
		if (opt == TRUE)
			(*i) += 2;
		return (TRUE);
	}
	else if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
		;
	else
		return (FALSE);
	if (opt == TRUE)
		(*i)++;
	return (TRUE);
}

/* i++ until the end of the quote which ends the word */

void	parse_quotes(char *line, size_t *i)
{
	char	quote_type;
	size_t	i_plus_un;

	quote_type = line[*i];
	(*i)++;
	while (line[*i] != '\0')
	{
		i_plus_un = *i + 1;
		if (line[*i] == quote_type)
		{
			if (line[(*i)++ + 1]
				&& is_a_metacharacter(line, &i_plus_un, FALSE) == TRUE)
				break ;
			while (line[*i] != '\0' && is_blank(line, (*i)) == FALSE)
				(*i)++;
			break ;
		}
		if (line[*i] == quote_type
			&& is_a_metacharacter(line, &i_plus_un, FALSE) == TRUE)
		{
			*i = i_plus_un;
			break ;
		}
		(*i)++;
	}
}

/* while the word isn't finished, i++ 
 * a word is finished when word[i] == blank or word[i] == metacharacter
 * if there is an opening quote in the word, the closing quote 
 * must be followed by ('\0', blank, metacharacter) */

void	parse_word(char *line, size_t *i)
{
	while (line[*i] != '\0')
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			parse_quotes(line, i);
			break ;
		}
		if (is_a_metacharacter(line, i, FALSE) == TRUE)
			break ;
		if (is_blank(line, *i) == TRUE)
			break ;
		(*i)++;
	}
}

/* return true if line[i] == space or tab */

bool	is_blank(char *line, size_t i)
{
	if (line[i] == ' ')
		return (TRUE);
	else if (line[i] == '\t')
		return (TRUE);
	else
		return (FALSE);
}

/* Count the number of tokens (= words + metacharacters),
 * skip blank characters */

size_t	count_number_of_tokens(char *line)
{
	size_t	number_of_tokens;
	size_t	i;

	number_of_tokens = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (is_blank(line, i) == TRUE)
			while (is_blank(line, i) == TRUE)
				i++;
		else
		{
			if (line[i] == '#')
				break ;
			else if (is_a_metacharacter(line, &i, TRUE) == TRUE)
				number_of_tokens++;
			else
			{
				parse_word(line, &i);
				number_of_tokens++;
			}
		}
	}
	return (number_of_tokens);
}
