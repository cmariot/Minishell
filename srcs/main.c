/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/22 11:22:17 by cmariot          ###   ########.fr       */
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
				if (parse(&minishell.command_line) != -1)
				{
					expand_env_variable(&minishell.command_line.splitted_line,
						minishell.env);
					if (builtin(minishell.command_line.line, &minishell))
						break ;
					execute(&minishell, &minishell.command_line);
					//int	i;

					//i = 0;
					//while ( i < minishell.command_line.number_of_pipes)
					//{
					//	if (i == 0)
					//	{
					//		execute_pipelines(minishell.command_line.main.args, envlist_to_array(minishell.env));
					//	}
					//	else
					//	{
					//		execute_pipelines(minishell.command_line.pipe_command[i - 1].args, envlist_to_array(minishell.env));
					//	}
					//	i++;
					//}
				}
				reset_minishell(&minishell.command_line);
			}
		}
	}
	return (0);
}
