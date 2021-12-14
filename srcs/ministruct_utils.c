/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ministruct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:52:50 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 09:19:07 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	reset_next_cmd(t_shell *ministruct)
//{
//	ministruct->command.next_command->pipe = 0;
//	ministruct->command.next_command->input_redir = 0;
//	ministruct->command.next_command->output_redir = 0;
//	ministruct->command.next_command->heredoc = 0;
//	ministruct->command.next_command->output_redir_append = 0;
//}

// Initialize the value of the structure to default value
void	init_ministruct(t_shell *minishell, char **env)
{
	minishell->env = save_env(env);
	minishell->prompt = NULL;
	minishell->line = NULL;
	minishell->number_of_command_lines = 0;
	minishell->command_line = NULL;
}

// In the env linked list, get a copy of the value
// of the ele;emt which have name = "name",
// if not found, return NULL. */
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
void	update_ministruct(t_shell *minishell)
{
	minishell->prompt = get_prompt(minishell);
	//if (ministruct->line != NULL)
	//	free(ministruct->line);
	//reset_next_cmd(ministruct);
	minishell->line = readline(minishell->prompt);
	//if (rl_on_new_line() == 0)
	//{
	//	add_history(ministruct->line);
	//	parse_line(&ministruct->command, ministruct->line);
	//}
}

//// Free the structure elements before exit
//void	free_ministruct(t_shell *ministruct)
//{
//	free(ministruct->line);
//	free(ministruct->pwd);
//	free(ministruct->prompt);
//	ft_lstclear_env(&ministruct->env, free);
//	free(ministruct->command.line);
//	ft_free_array(ministruct->command.line_splitted);
//}
