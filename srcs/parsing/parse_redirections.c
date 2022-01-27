/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:21 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/27 17:06:11 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return 1 if char *element is a redirection string
int	is_redirection(char *element)
{
	if (ft_strcmp(element, "<<") == 0)
		return (1);
	else if (ft_strcmp(element, ">>") == 0)
		return (1);
	else if (ft_strcmp(element, "<") == 0)
		return (1);
	else if (ft_strcmp(element, ">") == 0)
		return (1);
	else
		return (0);
}

char	*filename_expand(char *filename, t_env *env)
{
	char	*final;
	char	**array;

	final = ft_strdup(filename);
	search_dollar_in_str(&final, env);
	str_quotes_removal(&final);
	str_tilde_expansion(&final, env);
	array = ft_split(final, ' ');
	if (!array)
		return (NULL);
	else if (array && array[1] != NULL)
	{
		ft_free_array(array);
		if (final)
			free(final);
		print(2, "minishell: %s: ambiguous redirect\n", filename);
		return (NULL);
	}
	else if (array[0][0] == '$')
	{
		return (NULL);
	}
	ft_free_array(array);
	return (final);
}

// put the redirection values in the t_redir *redir structure
int	fill_redirections(t_redir *redir, int *array_index, char **array,
		t_env *env)
{
	if (array[(*array_index) + 1] == NULL)
		return (-1);
	while (array[(*array_index) + 1] != NULL
		&& is_redirection(array[*array_index]) != 1)
			(*array_index)++;
	if (array[(*array_index) + 1] == NULL)
		return (0);
	if (array[*array_index])
		redir->redir_type = ft_strdup(array[*array_index]);
	if (array[(*array_index) + 1])
	{
		if (ft_strcmp(redir->redir_type, "<<") == 0)
		{
			redir->filename = new_heredoc_name();
			if (create_heredoc(redir->filename,
					array[(*array_index) + 1]) == -1)
				return (-1);
		}
		else
		{
			redir->filename = filename_expand(array[(*array_index) + 1], env);
			if (redir->filename == NULL)
				return (1);
		}
		*array_index += 2;
	}
	else
		*array_index += 1;
	return (0);
}

//pour chaque redirection d'une commande simple, remplir la structure
int	fill_redirection_array(t_command_line *command_line, size_t i, t_env *env)
{
	int		array_index;
	size_t	j;

	j = 0;
	array_index = 0;
	while (j < command_line->command[i].number_of_redirections)
	{
		if (fill_redirections(&command_line->command[i].redir[j++],
				&array_index, command_line->command[i].command_array, env) != 0)
			return (-1);
	}
	return (0);
}

ssize_t	get_number_of_redir(char **command_array)
{
	ssize_t	number_of_redirections;
	ssize_t	j;

	number_of_redirections = 0;
	j = 0;
	while (command_array[j] != NULL)
	{
		if (is_redirection(command_array[j]) == 1)
		{
			if (is_redirection(command_array[j + 1]) == 1
				|| command_array[j + 1] == NULL)
			{
				print(2, "minishell: syntax error near redirection.\n");
				global_exit_status(1);
				return (-1);
			}
			else
				number_of_redirections++;
		}
		j++;
	}
	return (number_of_redirections);
}

//compte le nombre de redirection dans la commande simple
//cree un tableau pour chaque redirection
//remplir le tableau avec le type de redirection et le filename
int	parse_redirections(t_command_line *command_line, t_env *env)
{
	int	i;
	int	len;
	int	ret;

	i = 0;
	while (i < (int)command_line->number_of_simple_commands)
	{
		len = get_number_of_redir(command_line->command[i].command_array);
		if (len == -1)
			return (1);
		command_line->command[i].number_of_redirections = len;
		if (len == 0)
		{
			i++;
			continue ;
		}
		command_line->command[i].number_of_redirections = len;
		command_line->command[i].redir = ft_calloc(sizeof(t_redir), len + 1);
		if (!command_line->command[i].redir)
			return (1);
		ret = fill_redirection_array(command_line, i, env);
		if (ret == -1 || ret == 1)
			return (1);
		i++;
	}
	return (0);
}
