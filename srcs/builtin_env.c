/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:03:11 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/05 13:40:59 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print "name=value" for all the values of the linked list t_env
int	builtin_env(t_env *env)
{
	while (env)
	{
		ft_putstr(env->name);
		write(1, "=", 1);
		ft_putstr(env->value);
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}
