/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:03:11 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/10 16:50:20 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print "name=value" for all the values of the linked list t_env
int	builtin_env(t_env *env, char *first_arg)
{
	if (first_arg != NULL)
	{
		if (first_arg[0] == '-' && first_arg[1] != '\0')
			ft_putstr_fd("minishell: env: invalid option.\n", 2);
		else
			ft_putstr_fd("minishell: env: invalid argument.\n", 2);
		return (1);
	}
	if (!env)
		return (0);
	while (env)
	{
		if (env->name)
		{
			ft_putstr(env->name);
			write(1, "=", 1);
			if (env->value)
				ft_putstr(env->value);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}
