/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:10:37 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/05 13:36:42 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Search the value of name in the env linked list,
 * - If not found, value == NULL
 *		- If there is no other caracter in str that $NAME,
 *		  str is removed from the array
 *		- else $NAME is removed from the str
 * - Else if there is a value, $NAME is replaced by its value */

int	search_value(char **str, size_t *i, char **name, char **value)
{
	if (*value == NULL)
	{
		if (ft_strlen(*str) - 1 == ft_strlen(*name))
		{
			free(*name);
			return (-1);
		}
		else
			remove_from_str(str, i, ft_strlen(*name));
	}
	else
	{
		if (ft_strlen(*str) - 1 == ft_strlen(*name))
		{
			free(*str);
			*str = ft_strdup(*value);
		}
		else
			add_value_to_str(str, *name, *value, i);
	}
	if (*name)
		free(*name);
	if (*value)
		free(*value);
	return (0);
}

void	remove_spaces(char **str)
{
	char	**array;

	if (*str == NULL)
		return ;
	array = ft_split(*str, ' ');
	if (!array)
		return ;
	free(*str);
	*str = join_array(array, " ");
	ft_free_array(array);
}

/* Get the name to expand (= the word after the $ caracter)
 * if the $ is imediately followed by a ' or a " -> remove the $
 * else count the len of the word and get it via substr.
 * if name = "?" expand the exit status
 * else we search the value of name in the env linked list */

int	get_name_to_expand(char **str, size_t *i, t_env *env, bool opt)
{
	int		len;
	char	*name;
	char	*value;

	if ((*str)[*i + 1] == '\'' || (*str)[*i + 1] == '"')
		return (remove_from_str(str, i, 0));
	len = 0;
	if (ft_isdigit((*str)[*i + len + 1]) == TRUE)
		while (ft_isdigit((*str)[*i + len + 1]) == TRUE)
			len++;
	else if ((*str)[*i + 1] == '?')
		return (expand_exit_status(str, i));
	else
		while (ft_isalnum((*str)[*i + len + 1]) == TRUE)
			len++;
	if (len == 0)
		return (0);
	name = ft_substr((*str), *i + 1, len);
	value = get_env_value(name, env);
	if (opt == TRUE)
		remove_spaces(&value);
	if (search_value(str, i, &name, &value) == -1)
		return (1);
	return (0);
}

/* In double quote the expansion is performed, but if "$" it will print the $ */

int	expand_in_double_quotes(size_t *i, char **str, t_env *env)
{
	(*i)++;
	while ((*str)[*i] != '"' && (*str)[*i])
	{
		if ((*str)[*i] == '$' && (*str)[*i + 1])
		{
			if ((*str)[*i + 1] == '"')
			{
				(*i) += 1;
				return (0);
			}
			else if ((*str)[*i + 1] == '\'')
			{
				(*i) += 1;
				while ((*str)[*i + 1] != '\'')
					(*i) += 1;
			}
		}
		if ((*str)[*i] == '$')
			if (get_name_to_expand(str, i, env, FALSE) == 1)
				return (-1);
		(*i)++;
	}
	return (0);
}

/* In str, the expansion is different if the $NAME is quoted or not 
 * and if it's quoted by " or ' :
 * - No expansion if quoted by '
 * - Expansion if quoted by " or not quoted */

int	search_dollar_in_str(char **str, t_env *env)
{
	size_t	i;
	int		ret;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] != '\'' && (*str)[i])
				i++;
		}
		else if ((*str)[i] == '"')
		{
			expand_in_double_quotes(&i, str, env);
		}
		else if ((*str)[i] == '$')
		{
			ret = get_name_to_expand(str, &i, env, TRUE);
			if (ret == 1)
				return (-1);
		}
		i++;
	}
	return (0);
}
