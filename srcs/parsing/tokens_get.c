/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:27:23 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/31 11:20:48 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * token =	A sequence of characters considered a single unit by shell.
 *			It is either a word or an operator.
 *
 * word =	A sequence of characters treated as a unit by the shell.
 *			Words may not include unquoted metacharacters.
 *
 * metacharacter = A character that, when unquoted, separates words.
 *			A metacharacter is a space, tab, newline, or one of the following
 *			characters:
 *			‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
 *
 * operator = A control operator or a redirection operator.
 *			See Redirections, for a list of redirection operators.
 *			Operators contain at least one unquoted metacharacter.
 *
 * control_operator = A token that performs a control function.
 *			It is a newline or one of the following:
 *			‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.
 */

/* Return an array of tokens
 * Count the number of tokens, allocate memory and fill the array */

int	get_tokens_array(char *line, char ***array)
{
	size_t	number_of_tokens;

	if (line == NULL)
		return (1);
	number_of_tokens = count_number_of_tokens(line);
	if (number_of_tokens == 0)
		return (1);
	*array = ft_calloc(number_of_tokens + 1, sizeof(char *));
	if (!(*array))
		return (1);
	if (fill_tokens_array(*array, line, number_of_tokens))
		return (1);
	return (0);
}
