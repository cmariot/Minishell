/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ministruct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:52:50 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 11:18:48 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialize the value of the structure to default value
void	init_ministruct(t_shell *ministruct, char **env)
{
	ministruct->env = save_env(env);
	ministruct->line = NULL;
	ministruct->prompt = NULL;
	ministruct->pwd = NULL;
	ministruct->command.line = NULL;
	ministruct->command.line_splitted = NULL;
	ministruct->command.command1 = NULL;
	ministruct->command.command2 = NULL;
	ministruct->command.args1 = NULL;
	ministruct->command.args2 = NULL;
	ministruct->command.filename = NULL;
}

/* In the env array, get the value of the line which begins by "name=",
 * for example, to get the value of PWD : get_env("PWD=", env),
   if a line is found, get the line without it's firsts characters.
   Else, return NULL. */
char	*get_env_value(char *name, t_env *env)
{
	char	*value;

	value = NULL;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			value = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (value);
}

// If the values aren't NULL, free the structure variables,
// Update yhe values on each loop.
void	update_ministruct(t_shell *ministruct)
{
	if (ministruct->pwd != NULL)
		free(ministruct->pwd);
	ministruct->pwd = get_env_value("PWD", ministruct->env);
	if (ministruct->prompt != NULL)
		free(ministruct->prompt);
	ministruct->prompt = get_prompt(ministruct);
	if (ministruct->line != NULL)
		free(ministruct->line);
	ministruct->line = readline(ministruct->prompt);
	if (rl_on_new_line() == 0)
	{
		add_history(ministruct->line);
		parse_line(&ministruct->command, ministruct->line);
	}
}

// Free the structure elements before exit
void	free_ministruct(t_shell *ministruct)
{
	free(ministruct->line);
	free(ministruct->pwd);
	free(ministruct->prompt);
	ft_lstclear_env(&ministruct->env, free);
	free(ministruct->command.line);
	ft_free_array(ministruct->command.line_splitted);
}

