/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:03:46 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/04 09:13:08 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* In the env array, check if the line begins by "PWD=",
   if a line is found, get the line without it's 4 first characters.
   Else, error. */
char	*get_pwd(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = NULL;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PWD=", 4) == 0)
		{
			pwd = ft_strdup(env[i] + 4);
			break ;
		}
		i++;
	}
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}
