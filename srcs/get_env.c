/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:03:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/04 13:08:15 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* In the env array, get the value of the line which begins by "name=",
 * for example, to get the value of PWD : get_env("PWD=", env),
   if a line is found, get the line without it's firsts characters.
   Else, return NULL. */
char	*get_env(char *name, char **env)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	if (name && *env)
	{
		while (env[i])
		{
			if (ft_memcmp(env[i], name, ft_strlen(name)) == 0)
			{
				value = ft_strdup(env[i] + ft_strlen(name));
				break ;
			}
			i++;
		}
	}
	return (value);
}
