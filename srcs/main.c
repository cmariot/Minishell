/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/28 12:56:07 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;
	struct	sigaction new_act;
	struct	sigaction act;

	new_act.sa_sigaction = ft_handler;
    new_act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &new_act, NULL);
	if (argc && *argv && *env)
	{
		init_minishell(&minishell, env);
		while (1)
		{
			sigaction(SIGINT, &new_act, NULL);
			get_command_line(&minishell, &minishell.command_line);
			if (parse(&minishell.command_line, &minishell) == -1)
			{
				reset_minishell(&minishell.command_line);
				continue ;
			}
			if (builtin(minishell.command_line.line, &minishell))
				break ;
			execute(&minishell, &minishell.command_line);
			reset_minishell(&minishell.command_line);
		}
	}
	return (0);
}
