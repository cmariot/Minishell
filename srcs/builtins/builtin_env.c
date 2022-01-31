/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:03:11 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/31 21:38:59 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_error(char *first_arg)
{
	if (first_arg[0] == '-' && first_arg[1] != '\0')
	{
		print(2, "minishell: env: invalid option.\n");
		global_exit_status(125);
	}
	else
	{
		print(2, "minishell: env: invalid argument.\n");
		global_exit_status(127);
	}
	return (1);
}

// print "name=value" for all the values of the linked list t_env
int	builtin_env(t_env *env, char *first_arg)
{
	if (first_arg != NULL)
		return (env_error(first_arg));
	if (!env)
		return (global_exit_status(0));
	while (env)
	{
		if (env->name && env->value)
		{
			ft_putstr(env->name);
			write(1, "=", 1);
			ft_putstr(env->value);
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (global_exit_status(0));
}
