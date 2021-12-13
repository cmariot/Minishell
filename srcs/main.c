/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 08:35:31 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Seulement pour des tests,
// a implementer pour ajouter des arguments personnalisables
// env, setenv, unsetenv OK, fonctionnent avec une liste chainee
// pwd affiche la valeur de la variable d'environnement $PWD
// exit voir les codes d'exit a renvoyer
void	builtin(t_shell *ministruct)
{
	if (ft_strcmp(ministruct->line, "pwd") == 0)
		printf("%s\n", ministruct->pwd);
	else if (ft_strcmp(ministruct->line, "env") == 0)
		print_env(ministruct->env);
	else if (ft_strcmp(ministruct->line, "setenv") == 0)
		ft_setenv(ministruct->env, "PWD", "/test");
	else if (ft_strcmp(ministruct->line, "unsetenv") == 0)
		ft_unsetenv(ministruct->env, "PWD");
	else if (ft_strcmp(ministruct->line, "exit") == 0)
	{
		free_ministruct(ministruct);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	ministruct;

	if (argc && *argv && *env)
	{
		init_ministruct(&ministruct, env);
		while (1)
		{
			update_ministruct(&ministruct);
			builtin(&ministruct);
		}
	}
	return (0);
}
