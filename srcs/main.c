/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/06 08:59:14 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_ministruct(char **env, t_shell *ministruct)
{
	ministruct->pwd = get_env("PWD=", env);
	if (ministruct->prompt != NULL)
		free(ministruct->prompt);
	ministruct->prompt = get_prompt(ministruct);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	ministruct;

	if (argc && *argv && *env)
	{
		ministruct.prompt = NULL;
		while (1)
		{
			init_ministruct(env, &ministruct);
			ministruct.line = readline(ministruct.prompt);
			if (ft_strcmp(ministruct.line, "pwd") == 0)
				printf("%s\n", ministruct.pwd);
			else if (ft_strcmp(ministruct.line, "exit") == 0)
			{
				free(ministruct.line);
				free(ministruct.pwd);
				free(ministruct.prompt);
				break ;
			}
			free(ministruct.line);
		}
	}
	return (0);
}
