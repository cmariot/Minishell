/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ministruct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:52:50 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 14:04:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialize the value of the structure to default value
void	init_ministruct(t_shell *ministruct, char **env)
{
	ministruct->env = put_env_in_a_list(env);
	ministruct->prompt = NULL;
	ministruct->pwd = NULL;
	ministruct->line = NULL;
}

// If the values aren't NULL, free the structure variables,
// Update yhe values on each loop.
void	update_ministruct(char **env, t_shell *ministruct)
{
	if (ministruct->pwd != NULL)
		free(ministruct->pwd);
	ministruct->pwd = get_env_value("PWD=", env);
	if (ministruct->prompt != NULL)
		free(ministruct->prompt);
	ministruct->prompt = get_prompt(ministruct);
	if (ministruct->line != NULL)
		free(ministruct->line);
	ministruct->line = readline(ministruct->prompt);
	if (rl_on_new_line() == 0)
		add_history(ministruct->line);
}

// Free the structure elements before exit
void	free_ministruct(t_shell *ministruct)
{
	free(ministruct->line);
	free(ministruct->pwd);
	free(ministruct->prompt);
	ft_lstclear(&ministruct->env, free);
}
