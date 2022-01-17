/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:58:50 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/30 13:59:43 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the size of the linked list env
int	ft_envlstsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

char	*fill_env_array(t_env *envlist)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(envlist->name, "=");
	if (tmp1 == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, envlist->value);
	if (tmp2 == NULL)
		return (tmp1);
	free(tmp1);
	return (tmp2);
}

// Get a char **env copy from the t_env *env linked list
char	**envlist_to_array(t_env *envlist)
{
	char	**env;
	char	*str;
	size_t	i;

	i = ft_envlstsize(envlist);
	if (i == 0)
		return (NULL);
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envlist->next != NULL)
	{
		str = fill_env_array(envlist);
		if (str != NULL)
			env[i] = str;
		i++;
		envlist = envlist->next;
	}
	return (env);
}
