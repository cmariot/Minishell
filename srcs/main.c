/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/01 13:02:39 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell				minishell;

	if (argc && *argv && *env)
	{
		init_minishell(&minishell, env);
		while (1)
		{
			signal_catcher();
			get_command_line(&minishell, &minishell.command_line);
			if (parse(&minishell.command_line, &minishell) == -1)
			{
				reset_minishell(&minishell.command_line);
				continue ;
			}
			execute(&minishell, &minishell.command_line);
			reset_minishell(&minishell.command_line);
		}
	}
	return (0);
}
