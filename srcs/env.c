/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:04:13 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/11 20:04:40 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	else
		return (NULL);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (alst)
	{
		if (*alst == NULL)
			*alst = new;
		else
		{
			tmp = ft_lstlast_env(*(alst));
			tmp->next = new;
		}
	}
}

t_env	*ft_lstnew_env(void *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->next = NULL;
		return (new);
	}
	else
		return (NULL);
}

char	*get_name(char *env_line)
{
	char	*name;
	int		len;
	int		i;

	len = 0;
	while (env_line[len] != '=')
		len++;
	name = ft_calloc(len + 1, sizeof(char));
	if (name == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		name[i] = env_line[i];
		i++;
	}
	return (name);
}

char	*get_value(char *env_line)
{
	char	*value;
	int		len;
	int		equal_index;
	int		i;

	len = ft_strlen(env_line);
	equal_index = 0;
	while (env_line[equal_index] != '=')
		equal_index++;
	value = ft_calloc(len - equal_index, sizeof(char));
	if (value == NULL)
		return (NULL);
	i = 0;
	while (equal_index + 1 < len)
	{
		value[i] = env_line[equal_index + 1];
		equal_index++;
		i++;
	}
	return (value);
}

void	print_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->name != NULL && env->value != NULL)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

// Create a copy of an array of char * and put the value in a chained list
t_env	*save_env(char **env)
{
	t_env	*env_list;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (env[i])
	{
		name = get_name(env[i]);
		if (name == NULL)
			break ;
		value = get_value(env[i]);
		if (value == NULL)
			free(name);
		if (value == NULL)
			break ;
		if (i == 0)
			env_list = ft_lstnew_env(name, value);
		else
			ft_lstadd_back_env(&env_list, ft_lstnew_env(name, value));
		free(name);
		free(value);
		i++;
	}
	return (env_list);
}

void	ft_lstdelone_env(t_env *env, void (*del)(void *))
{
	(del)(env->name);
	(del)(env->value);
	free(env);
}

void	ft_lstclear_env(t_env **env, void (*del)(void *))
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		ft_lstdelone_env(*env, (del));
		*env = tmp;
	}
}

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

void	ft_unsetenv(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->name);
			free(env->value);
			env->name = NULL;
			env->value = NULL;
			break ;
		}
		env = env->next;
	}
}
