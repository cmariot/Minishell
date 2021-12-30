/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:13:52 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/23 11:16:16 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Seulement pour des tests,
// a implementer pour ajouter des arguments personnalisables
// env, setenv, unsetenv OK, fonctionnent avec une liste chainee
// pwd affiche la valeur de la variable d'environnement $PWD
// exit voir les codes d'exit a renvoyer
int	builtin(char *command, t_shell *minishell)
{
	if (ft_strcmp(command, "pwd") == 0)
		pwd_builtin(minishell);
	else if (ft_strcmp(command, "env") == 0)
		env_builtin(minishell->env);
	else if (ft_strcmp(command, "setenv") == 0)
		setenv_builtin(minishell->env, "PWD", "/test");
	else if (ft_strcmp(command, "unsetenv") == 0)
		unsetenv_builtin(minishell->env, "PWD");
	else if (ft_strcmp(command, "cd") == 0)
		do_cd(minishell);
	else if (ft_strcmp(command, "exit") == 0)
	{
		free_minishell(minishell);
		return (1);
	}
	return (0);
}
