/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:09:46 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 17:08:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	execute_simple_command(t_shell *minishell, t_simple command, int *fd,
	int fd_output)
{
	char	**env_array;

	if (command.command_and_args == NULL)
		return ;
	if (command_is_builtin(&minishell, command, fd, fd_output)
		!= 127)
		return ;
	env_array = envlist_to_array(minishell->env);
	if (command_with_path(command, env_array, fd_output) == 0)
	{
		ft_free_array(env_array);
		return ;
	}
	if (command_without_path(minishell, command, env_array, fd_output) == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command.command_and_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		global_exit_status(127);
	}
	ft_free_array(env_array);
}
