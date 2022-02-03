/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/03 11:27:47 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*middle_strdup(char *str, size_t *k, size_t *i)
{
	char	*new;

	if (*k == 0)
		(*i)++;
	(*k)++;
	new = ft_strdup(str);
	return (new);
}

char	**create_new_array(t_simple *command, char **array, size_t i)
{
	char	**new;
	size_t	new_len;
	size_t	j;
	size_t	k;

	new_len = ft_array_len(command->command_and_args) + ft_array_len(array);
	print(1, "NEW_ARRAY_LEN = %d\n", new_len - 1);
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
			new[j] = middle_strdup(array[k], &k, &i);
		else
			new[j] = ft_strdup(command->command_and_args[i++]);
		if (new[j] == NULL)
			return (NULL);
		print(1, "NEW[%d] = [%s]\n", j, new[j]);
		j++;
	}
	return (new);
}

int	command_expansion(t_simple *command, t_env *env)
{
	size_t	i;
	char	**array;
	char	**new;

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
			new = create_new_array(command, array, i);
			ft_free_array(command->command_and_args);
			command->command_and_args = new;
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
