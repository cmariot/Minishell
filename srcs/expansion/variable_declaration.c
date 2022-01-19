/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_declaration.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:48:44 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/19 09:20:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unauthorized_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == FALSE && str[i] != '=')
			return (1);
		i++;
	}
	return (0);
}

size_t	get_name_len2(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

int	env_var_declaration(char *str, char *value, t_env *env)
{
	char	*name;
	size_t	name_len;

	name_len = get_name_len2(str);
	name = ft_substr(str, 0, name_len);
	if (name == NULL)
		return (1);
	//add to env
	free(name);
	return (0);
}

void	variable_declaration(char **command_array, t_env *env)
{
	size_t	i;
	char	*value;

	i = 0;
	while (command_array[i] != NULL)
	{
		if (unauthorized_char(command_array[i]))
			break ;
		else
		{
			value = ft_strchr(command_array[i], '=');
			if (value != NULL)
			{
				value = ft_strdup(value + 1);
				if (env_var_declaration(command_array[i], value, env))
				{
					ft_putstr_fd("Error ?\n", 2);
				}
			}
		}
		i++;
	}
}
