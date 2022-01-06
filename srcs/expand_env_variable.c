/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/06 19:37:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_in_env(char *str, size_t i, t_env *env)
{
	char	*name;
	char	*value;

	name = ft_substr(str, 0, i);
	value = ft_strdup(str + i + 1);
	add_to_env(env, name, value);
	free(name);
	free(value);
}

/* During the parsing, if an argument conains an equal -> save in env */
bool	contains_equal(char *str, t_env *env)
{
	int	i;
	int	min_len;

	min_len = ft_strlen(str) - 2;
	if (min_len <= 0)
		return (FALSE);
	i = 1;
	while (i <= min_len)
	{
		if (str[i] == '=')
		{
			save_in_env(str, i, env);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

size_t	get_env_name_len(char *name, size_t index)
{
	size_t	len;

	len = 0;
	while (name[index] != '\0' && name[index] != '$'
		&& name[index] != '\'' && name[index] != '\"')
	{
		len++;
		index++;
	}
	return (len);
}

void	remove_name_from_str(char *name, char *str, size_t *i)
{
	size_t	name_len;
	size_t	j;

	name_len = ft_strlen(name);
	j = *i;
	while (str[name_len + j + 1] != '\0')
	{
		str[j] = str[name_len + j + 1];
		str[name_len + j] = '\0';
		j++;
	}
}

void	add_value_to_str(char **str, char *name, char *value, size_t *i)
{
	size_t	str_len;
	size_t	value_len;
	size_t	name_len;
	size_t	new_len;
	char	*new_str;
	size_t	j;
	size_t	k;

	str_len = ft_strlen(*str);
	value_len = ft_strlen(value);
	name_len = ft_strlen(name);
	new_len = str_len - (name_len + 1) + value_len + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	if (!new_str)
		return ;
	j = 0;
	if (*i > 0)
	{
		while (j < *i)
		{
			new_str[j] = (*str)[j];
			j++;
		}
	}
	k = 0;
	while (k < value_len)
		new_str[j++] = value[k++];
	k = 0;
	while (j < new_len)
		new_str[j++] = (*str)[(*i) + 1 + name_len + k++];
	free(*str);
	*str = new_str;
	*i = value_len + *i;
}

void	search_value(char **str, size_t *i, char *name, t_env *env)
{
	char	*value;
	size_t	len;

	value = get_env_value(name, env);
	if (value == NULL)
	{
		len = *i + ft_strlen(name) + 1;
		while (*i < len)
		{
			(*str)[*i] = 31;
			(*i)++;
		}
	}
	else
	{
		if (ft_strlen(*str) - 1 == ft_strlen(name))
		{
			free(*str);
			*str = ft_strdup(value);
		}
		else
			add_value_to_str(str, name, value, i);
	}
}

void	expand_name(char **str, size_t *i, t_env *env)
{
	size_t	len;
	char	*name;

	len = get_env_name_len((*str), *i + 1);
	if (len == 0)
		return ;
	name = ft_substr((*str), *i + 1, len);
	if (ft_strcmp(name, "?") == 0)
		printf("expansion exit status\n");
	else
	{
		search_value(str, i, name, env);
	}
}

int	search_name(char **str, t_env *env)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] != '\'')
				i++;
			i++;
		}
		if ((*str)[i] == '$')
		{
			expand_name(str, &i, env);
		}
		i++;
	}
	return (0);
}

void	expand_env_variable(char **command_array, t_env *env)
{
	size_t	i;

	i = 0;
	while (command_array[i] != NULL)
	{
		search_name(&command_array[i], env);
		i++;
	}
}
