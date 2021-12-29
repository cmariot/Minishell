/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 18:08:31 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	minishell;

int	main(int argc, char **argv, char **env)
{
	struct	sigaction new_act;
	struct	sigaction act;
	int 	sig;

	new_act.sa_sigaction = ft_handler;
    new_act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sig = sigaction(SIGQUIT, &act, NULL);
	sig = sigaction(SIGINT, &new_act, NULL);
	if (sig == -1)
		return (EXIT_FAILURE);
	if (argc && *argv && *env)
	{
		init_minishell(&minishell, env);
		while (1)
		{
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
