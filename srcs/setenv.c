/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:30:01 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 09:10:02 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If the element name is in the linked list env, change its value,
// else add name and value
void	ft_setenv(t_env *env, char *name, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	env = tmp;
	ft_lstadd_back_env(&env, ft_lstnew_env(name, value));
}
