/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_t_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:32:45 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 08:56:09 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create the first element of a linked list t_env
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

// Add the element new at the end of the linked list 
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

// Apply the function del to the name and the value and free the element
void	ft_lstdelone_env(t_env *env, void (*del)(void *))
{
	(del)(env->name);
	(del)(env->value);
	free(env);
}

// Apply ft_lstdelone() to all the elements of the linked list t_env
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

// Return the last element of the linked list t_env
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
