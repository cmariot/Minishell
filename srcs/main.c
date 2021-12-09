/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 15:07:10 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	ministruct;

	if (argc && *argv && *env)
	{
		init_ministruct(&ministruct, env);
		while (1)
		{
			update_ministruct(env, &ministruct);
			if (ft_strcmp(ministruct.line, "pwd") == 0)
				printf("%s\n", ministruct.pwd);
			else if (ft_strcmp(ministruct.line, "exit") == 0)
			{
				free_ministruct(&ministruct);
				break ;
			}
		}
	}
	return (0);
}
