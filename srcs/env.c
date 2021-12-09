/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:04:13 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 10:28:06 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create a copy of an array of char * and put the value in a chained list
t_list	*put_env_in_a_list(char **array)
{
	t_list	*env;
	int		i;

	i = 0;
	while (array[i])
	{
		if (i == 0)
			env = ft_lstnew(array[i]);
		else
			ft_lstadd_back(&env, ft_lstnew(array[i]));
		i++;
	}
	return (env);
}

// if (already_in_list() == true)
//		change_value()
// else
//		add_value()

bool	already_in_list(t_list *env, char *value)
{
	if (env == NULL)
		return (FALSE);
	while (env)
	{
		if (ft_memcmp((char *)env->content, value, ft_strlen(value)) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

void	change_value(t_list *env, char *new_value)
{
	if (env->content)
		free(env->content);
	env->content = new_value;
}

void	add_value(t_list **env, char *content)
{
	ft_lstadd_back(env, ft_lstnew(content));
}
