/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:04:13 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 14:05:32 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* In the env array, get the value of the line which begins by "name=",
 * for example, to get the value of PWD : get_env("PWD=", env),
   if a line is found, get the line without it's firsts characters.
   Else, return NULL. */
char	*get_env_value(char *name, char **env)
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

// Create a copy of an array of char * and put the value in a chained list
t_list	*put_env_in_a_list(char **array)
{
	t_list	*env;
	int		i;

	i = 0;
	while (array[i])
	{
		if (i == 0)
			env = ft_lstnew(ft_strdup(array[i]));
		else
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(array[i])));
		i++;
	}
	return (env);
}

// if (already_in_list() == true)
//		change_value()
// else
//		add_value()

/* already_in_list() returns true if name is in the env list,
 * else, it returns FALSE.
 * name is for example "PATH=", "PWD=" ...*/
bool	already_in_list(t_list *env, char *name)
{
	if (env == NULL)
		return (FALSE);
	while (env)
	{
		if (ft_memcmp((char *)env->content, name, ft_strlen(name)) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

/* To change the value of path variable in env list :
 * change_value(env, "PATH=", "/bin:/usr/bin")*/
void	change_value(t_list *env, char *name, char *value)
{
	char	*new;

	if (env->content)
		free(env->content);
	new = ft_strjoin(name, value);
	env->content = new;
}

void	add_value(t_list **env, char *name, char *value)
{
	char	*new;

	new = ft_strjoin(name, value);
	ft_lstadd_back(env, ft_lstnew(new));
}
