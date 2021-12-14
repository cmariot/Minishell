/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 12:33:15 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Seulement pour des tests,
// a implementer pour ajouter des arguments personnalisables
// env, setenv, unsetenv OK, fonctionnent avec une liste chainee
// pwd affiche la valeur de la variable d'environnement $PWD
// exit voir les codes d'exit a renvoyer
void	builtin(char *command, t_shell *minishell)
{
	if (ft_strcmp(command, "pwd") == 0)
	{
		//pwd(minishell);
	}
	else if (ft_strcmp(command, "env") == 0)
	{
		//env(minishell);
	}
	else if (ft_strcmp(command, "setenv") == 0)
	{
		//setenv(ministruct->env, "PWD", "/test");
	}
	else if (ft_strcmp(command, "unsetenv") == 0)
	{
		//unsetenv(ministruct->env, "PWD");
	}
	else if (ft_strcmp(command, "exit") == 0)
	{
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;

	if (argc && *argv && *env)
	{
		init_minishell(&minishell, env);
		while (1)
		{
			get_command(&minishell, &minishell.command_line);
			// parse()
			// execute()
		}
	}
	return (0);
}
