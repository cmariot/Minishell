/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/22 14:27:38 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Pour lancer minishell en mode non interactif :
 * ./minishell -c "commande a executer" */

void	non_interactive_mode(char **array, char **env)
{
	t_shell	minishell;

	init_minishell(&minishell, env);
	minishell.command_line.line = join_array(array, " ");
	if (minishell.command_line.line == NULL)
	{
		free_minishell(&minishell);
		return ;
	}
	if (parse(&minishell.command_line, &minishell) == -1)
	{
		free_minishell(&minishell);
		return ;
	}
	execute(&minishell, &minishell.command_line);
	free_minishell(&minishell);
	return ;
}

/* En comportement interactif, un prompt est afiche et
 * on peut lancer des commandes */

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;

	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		non_interactive_mode(argv + 2, env);
	else
	{
		//signal_catcher(0);
		catch_signal(INTERACTIVE);
		init_minishell(&minishell, env);
		while (1)
		{
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
