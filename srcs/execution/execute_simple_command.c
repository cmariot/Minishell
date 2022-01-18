/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:09:46 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 15:21:03 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	execute_simple_command(t_shell *minishell, t_simple command, int *backup_fd)
{
	char	**env_array;

	if (command.command_and_args == NULL)
		return ;
	if (command_is_builtin(&minishell, command)
		!= 127)
		return ;
	env_array = envlist_to_array(minishell->env);
	if (command_with_absolute_path(command, env_array, backup_fd) == 0)
	{
		ft_free_array(env_array);
		return ;
	}
	if (command_without_path(minishell, command, env_array, backup_fd) == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command.command_and_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		global_exit_status(127);
	}
	ft_free_array(env_array);
	return ;
}
