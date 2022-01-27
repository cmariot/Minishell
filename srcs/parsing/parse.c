/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:11:59 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/27 23:45:34 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	skip_verif_inside_quotes(char *line, int *i)
{
	bool	ok;
	char	c;

	ok = FALSE;
	c = line[*i];
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
		(*i)++;
	if (line[*i] == c)
		ok = TRUE;
	return (ok);
}

// Minishell should not interpret unclosed quotes
int	check_quotes(char *line)
{
	int		i;
	bool	ok;

	i = 0;
	ok = TRUE;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\''))
			ok = skip_verif_inside_quotes(line, &i);
		if (line[i] == '\0' || line[i] == '#')
			break ;
		i++;
	}
	if (ok == TRUE)
		return (0);
	else
	{
		print(2, "minishell does not interpret unclosed quotes\n");
		return (global_exit_status(1));
	}
}

int	check_empty_redir(t_command_line *command_line,
		size_t number_of_simple_commands)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < number_of_simple_commands)
	{
		j = 0;
		if (command_line->command[i].number_of_redirections)
		{
			while (j < command_line->command[i].number_of_redirections)
			{
				if (!(command_line->command[i].redir[j].filename))
				{
					print(2, "minishell: syntax error ");
					print(2, "near redirection\n");
					return (global_exit_status(1));
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	check_empty_pipe(t_command_line *command_line,
		size_t number_of_simple_commands)
{
	size_t	i;

	if (number_of_simple_commands == 1)
		return (0);
	i = 0;
	while (i < number_of_simple_commands)
	{
		if (!command_line->command[i].command_and_args
			&& command_line->command[i].number_of_redirections == 0)
		{
			print(2, "minishell: syntax error ");
			print(2, "near unexpected token '|'\n");
			return (global_exit_status(1));
		}
		i++;
	}
	return (0);
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;
	char	quote_type;

	i = 0;
	words = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			quote_type = *s;
			s++;
			while (*s && *s != quote_type)
				s++;
		}
		if (*s == c)
			i = 0;
		else if (i == 0)
		{
			i = 1;
			words++;
		}
		s++;
	}
	return (words);
}

static void	get_next_len_command(char **strs, unsigned int *str_len, char c)
{
	unsigned int	i;
	char			quote_type;

	*strs = *strs + *str_len;
	*str_len = 0;
	i = 0;
	while (**strs && **strs == c)
		(*strs)++;
	if (**strs == '"' || **strs == '\'')
	{
		quote_type = **strs;
		(*strs)++;
		while ((**strs) && **strs != quote_type)
			(*strs)++;
	}
	while ((*strs)[i])
	{
		if ((*strs)[i] == c)
			return ;
		(*str_len)++;
		i++;
	}
}

char	**command_split(char const *s, char c)
{
	char			**strs;
	int				words;
	int				i;
	char			*str;
	unsigned int	str_len;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (strs == NULL)
		return (NULL);
	i = 0;
	str = (char *)s;
	str_len = 0;
	while (i < words)
	{
		get_next_len_command(&str, &str_len, c);
		strs[i] = (char *)malloc(sizeof(char) * (str_len + 1));
		if (strs[i] == NULL)
			return (NULL);
		ft_strlcpy(strs[i++], str, str_len + 1);
	}
	strs[i] = NULL;
	return (strs);
}

int	ft_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len] != NULL)
	{
		len++;
	}
	return (len);
}

char	**create_new_array(t_simple *command, char **array, size_t i)
{
	char	**new;
	size_t	new_len;
	size_t	j;
	size_t	k;

	new_len = ft_array_len(command->command_and_args) - 1 + ft_array_len(array) + 1;
	new = ft_calloc(new_len, sizeof(char *));
	if (!new)
		return (NULL);
	j = 0;
	k = 0;
	while (j < new_len - 1)
	{
		if (j < i)
			new[j] = ft_strdup(command->command_and_args[j]);
		else if ((int)k < ft_array_len(array))
		{
			if (k == 0)
				i++;
			new[j] = ft_strdup(array[k]);
			k++;
		}
		else
		{
			new[j] = ft_strdup(command->command_and_args[i]);
			i++;
		}
		j++;
	}
	return (new);
}

int	command_expansion(t_simple *command, t_env *env)
{
	size_t	i;
	char	**array;
	char	**tmp;

	i = 0;
	if (!command->command_and_args)
		return (0);
	while (command->command_and_args[i] != NULL)
	{
		search_dollar_in_str(&command->command_and_args[i], env);
		array = command_split(command->command_and_args[i], ' ');
		if (!array)
			return (1);
		else if (array[1] != NULL)
		{
			tmp = create_new_array(command, array, i);
			ft_free_array(command->command_and_args);
			command->command_and_args = tmp;
		}
		ft_free_array(array);
		i++;
	}
	return (0);
}

int	command_and_args_expansion(t_command_line *command, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < command->number_of_simple_commands)
	{
		command_expansion(&(command->command[i]), env);
		i++;
	}
	return (0);
}

int	parse(t_command_line *command_line, t_shell *minishell)
{
	if (command_line->line[0] == '\0')
		return (1);
	if (check_quotes(command_line->line))
		return (1);
	if (get_tokens_array(command_line->line, &command_line->splitted_line))
		return (1);
	if (get_simple_commands(command_line, command_line->splitted_line))
		return (1);
	if (get_command_and_args(command_line))
		return (1);
	if (command_and_args_expansion(command_line, minishell->env))
		return (1);
	if (parse_redirections(command_line, minishell->env))
		return (1);
	if (check_empty_pipe(command_line,
			command_line->number_of_simple_commands))
		return (1);
	if (check_empty_redir(command_line,
			command_line->number_of_simple_commands))
		return (1);
	if (expansion(command_line, minishell->env))
		return (1);
//	print_command_line(command_line);
	return (0);
}
