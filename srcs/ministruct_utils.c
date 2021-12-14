/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ministruct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:52:50 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 12:27:40 by cmariot          ###   ########.fr       */
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
void	init_minishell(t_shell *minishell, char **env)
{
	minishell->env = save_env(env);
	minishell->prompt = NULL;
	minishell->command_line.line = NULL;
	minishell->command_line.splitted_line = NULL;
	minishell->command_line.command.command = NULL;
	minishell->command_line.command.args = NULL;
	minishell->command_line.number_of_pipes = 0;
	minishell->command_line.pipe_command = NULL;
	minishell->command_line.number_of_redirections = 0;
	minishell->command_line.redirection = NULL;
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
void	get_command(t_shell *minishell, t_command_line *command_line)
{
	//reset_cmd_line(ministruct);
	minishell->prompt = get_prompt(minishell);
	if (command_line->line != NULL)
		free(command_line->line);
	command_line->line = readline(minishell->prompt);
	if (rl_on_new_line() == 0)
		add_history(command_line->line);
}

//// Free the structure elements before exit
void	free_ministruct(t_shell *minishell)
{
	ft_lstclear_env(&minishell->env, free);
	free(minishell->prompt);
	free(minishell->command_line.line);
}
