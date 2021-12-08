/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/08 09:22:24 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The prompts is set as the name of the current directory.
// UNAME, 
char	*get_prompt(t_shell *ministruct)
{
	int		len;
	int		i;
	char	*current_directory;
	char	*prompt;

	i = ft_strlen(ministruct->pwd);
	if (i == 1 && ft_strcmp(ministruct->pwd, "/") == 0)
		return (ft_strdup("/ ➤ "));
	len = 0;
	while (ministruct->pwd[i--] != '/')
		len++;
	current_directory = malloc(sizeof(char) * len);
	if (!current_directory)
		return (ft_strdup("Default prompt: "));
	current_directory[len - 1] = '\0';
	i = ft_strlen(ministruct->pwd);
	while (len - 1 != 0)
	{
		current_directory[len - 2] = ministruct->pwd[i - 1];
		len--;
		i--;
	}
	prompt = ft_strjoin(current_directory, " ➤ ");
	free(current_directory);
	return (prompt);
}

// If the values aren't NULL, free the structure variables,
// Update yhe values on each loop.
void	update_ministruct(char **env, t_shell *ministruct)
{
	if (ministruct->pwd != NULL)
		free(ministruct->pwd);
	ministruct->pwd = get_env("PWD=", env);
	if (ministruct->prompt != NULL)
		free(ministruct->prompt);
	ministruct->prompt = get_prompt(ministruct);
}

// Initialize the initial values of the structure to NULL
void	init_ministruct(t_shell *ministruct)
{
	ministruct->prompt = NULL;
	ministruct->pwd = NULL;
}

void	free_ministruct(t_shell *ministruct)
{
	free(ministruct->line);
	free(ministruct->pwd);
	free(ministruct->prompt);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	ministruct;

	if (argc && *argv && *env)
	{
		init_ministruct(&ministruct);
		while (1)
		{
			update_ministruct(env, &ministruct);
			ministruct.line = readline(ministruct.prompt);
			add_history(ministruct.line);
			//parse
			//execute
			if (ft_strcmp(ministruct.line, "pwd") == 0)
				printf("%s\n", ministruct.pwd);
			else if (ft_strcmp(ministruct.line, "exit") == 0)
			{
				free_ministruct(&ministruct);
				break ;
			}
			free(ministruct.line);
		}
	}
	return (0);
}
