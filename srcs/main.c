/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 17:28:57 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;

	if (argc && *argv && *env)
	{
		init_minishell(&minishell, env);
		while (1)
		{
			get_command_line(&minishell, &minishell.command_line);
			if (minishell.command_line.line != NULL)
			{
				parse(&minishell.command_line);
				if (builtin(minishell.command_line.line, &minishell))
					break ;
				reset_minishell(&minishell.command_line);
			}
		}
	}
	return (0);
}
