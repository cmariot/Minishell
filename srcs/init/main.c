/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/06 13:02:23 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	usage(void)
{
	print(1, "USAGE:\n");
	print(1, "./minishell (for interactive mode)\n");
	print(1, "./minishell -c [command] (for non-interactive mode)\n");
	return (1);
}

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
	if (parse(&minishell.command_line, &minishell))
	{
		free_minishell(&minishell);
		return ;
	}
	execute(&minishell, &minishell.command_line);
	free_minishell(&minishell);
}

/* En comportement interactif, un prompt est afiche et
 * on peut lancer des commandes */

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;

	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		non_interactive_mode(argv + 2, env);
	else if (argc == 1)
	{
		catch_signal(INTERACTIVE);
		init_minishell(&minishell, env);
		while (1)
		{
			get_command_line(&minishell, &minishell.command_line);
			if (parse(&minishell.command_line, &minishell))
			{
				reset_minishell(&minishell.command_line, &minishell);
				continue ;
			}
			catch_signal(COMMAND);
			execute(&minishell, &minishell.command_line);
			catch_signal(INTERACTIVE);
			reset_minishell(&minishell.command_line, &minishell);
		}
	}
	else
		return (usage());
	return (0);
}
