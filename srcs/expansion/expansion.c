/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:22:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/27 16:36:28 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_quotes_removal(char **str)
{
	size_t	i;
	char	quote_type;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			quote_type = (*str)[i];
			remove_quote(*str, i);
			while ((*str)[i] != quote_type && (*str)[i])
				i++;
			if (i == 0 && (*str)[i + 1] == '\0')
				(*str)[i] = 32;
			else
				remove_quote(*str, i);
			i--;
		}
		i++;
	}
	return (0);
}

int	str_tilde_expansion(char **str, t_env *env)
{
	char	*home;

	if (*str[0] == '~')
	{
		home = get_env_value("HOME", env);
		if (!home)
			return (1);
		if (replace_tilde(str, &home))
			return (1);
	}
	return (0);
}

int	redir_expansion(t_redir *redir, t_env *env)
{
	search_dollar_in_str(&(redir->redir_type), env);
	str_quotes_removal(&redir->redir_type);
	str_tilde_expansion(&redir->redir_type, env);
	search_dollar_in_str(&(redir->filename), env);
	str_quotes_removal(&redir->filename);
	str_tilde_expansion(&redir->filename, env);
	return (0);
}

int	array_expansion(char **array, t_env *env)
{
	if (expand_tilde(array, env))
		return (1);
	if (expand_env_variable(array, env))
		return (1);
	quotes_removal(array);
	return (0);
}

int	expansion(t_command_line *command_line, t_env *env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < command_line->number_of_simple_commands)
	{
		if (command_line->command[i].command_and_args == NULL
			|| command_line->command[i].command_and_args[0] == NULL)
		{
			i++;
			continue ;
		}
		array_expansion(command_line->command[i].command_and_args, env);
		j = 0;
		while (j < command_line->command[i].number_of_redirections)
		{
			redir_expansion(&(command_line->command[i].redir[j]), env);
			j++;
		}
		i++;
	}
	return (0);
}
