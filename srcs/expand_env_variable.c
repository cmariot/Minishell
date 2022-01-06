/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:41 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/06 23:51:42 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_name_len(char *name, size_t index)
{
	size_t	len;

	if (name[index] == '\'' || name[index] == '"')
		return (-1);
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
	size_t	new_len;
	char	*new_str;
	size_t	j;
	size_t	k;

	new_len = ft_strlen(*str) - (ft_strlen(name) + 1) + ft_strlen(value) + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	if (!new_str)
		return ;
	j = 0;
	while (j < *i)
	{
		new_str[j] = (*str)[j];
		j++;
	}
	k = 0;
	while (k < ft_strlen(value))
		new_str[j++] = value[k++];
	k = 0;
	while (j < new_len)
		new_str[j++] = (*str)[(*i) + 1 + ft_strlen(name) + k++];
	free(*str);
	*str = new_str;
	*i = ft_strlen(value) + *i - 1;
}

void	remove_from_str(char **str, size_t *i, size_t name_len)
{
	size_t	j;
	char	*new_str;
	size_t	new_len;

	new_len = ft_strlen(*str) - name_len;
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
	if (new_len > j)
		while (j < new_len)
			new_str[j++] = (*str)[*i + name_len++ + 1];
	free(*str);
	*str = new_str;
	(*i)--;
}

int	search_value(char **str, size_t *i, char *name, t_env *env)
{
	char	*value;

	value = get_env_value(name, env);
	if (value == NULL)
	{
		if (ft_strlen(*str) - 1 == ft_strlen(name))
			return (-1);
		else
			remove_from_str(str, i, ft_strlen(name));
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
	return (0);
}

void	expand_exit_status(char **str, size_t *i, char *name)
{
	int		exit_status;
	char	*value;

	exit_status = return_global_exit_status();
	value = ft_itoa(exit_status);
	if (ft_strlen(*str) - 1 == ft_strlen(name))
	{
		free(*str);
		*str = ft_strdup(value);
	}
	else
		add_value_to_str(str, name, value, i);
}

int	expand_name(char **str, size_t *i, t_env *env)
{
	int		len;
	char	*name;

	len = get_env_name_len((*str), *i + 1);
	printf("LEN USER = %d\n", len);
	if (len == 0)
		return (0);
	else if (len == -1)
	{
		remove_from_str(str, i, 0);
		return (0);
	}
	name = ft_substr((*str), *i + 1, len);
	if (ft_strcmp(name, "?") == 0)
	{
		expand_exit_status(str, i, name);
	}
	else
	{
		if (search_value(str, i, name, env) == -1)
			return (-1);
	}
	return (0);
}

int	expand_in_double_quotes(size_t *i, char **str, t_env *env)
{
	(*i)++;
	while ((*str)[*i] != '"' && (*str)[*i])
	{
		if ((*str)[*i] == '$')
			if (expand_name(str, i, env) == -1)
				return (-1);
		(*i)++;
	}
	return (0);
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
			while ((*str)[i] != '\'' && (*str)[i])
				i++;
		}
		else if ((*str)[i] == '"')
		{
			expand_in_double_quotes(&i, str, env);
		}
		else if ((*str)[i] == '$')
			if (expand_name(str, &i, env) == -1)
				return (-1);
		i++;
	}
	return (0);
}

void	remove_from_array(char **splitted_line, int i)
{
	int	j;

	if (splitted_line[i + 1] == NULL)
	{
		free(splitted_line[i]);
		splitted_line[i] = NULL;
		return ;
	}
	j = i;
	while (splitted_line[j + 1] != NULL)
	{
		free(splitted_line[j]);
		splitted_line[j] = ft_strdup(splitted_line[j + 1]);
		j++;
	}
	free(splitted_line[j]);
	splitted_line[j] = NULL;
}

void	expand_env_variable(char **command_array, t_env *env)
{
	size_t	i;

	i = 0;
	while (command_array[i] != NULL)
	{
		if (search_name(&command_array[i], env) == -1)
			remove_from_array(command_array, i);
		i++;
	}
}
