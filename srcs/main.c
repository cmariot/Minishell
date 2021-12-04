/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/04 16:22:42 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_promt(t_shell *ministruct)
{
	int		len;
	int		i;
	char	*current_directory;

	i = ft_strlen(ministruct->pwd);
	len = 0;
	while (ministruct->pwd[i--] != '/')
		len++;
	current_directory = malloc(sizeof(char) * len - 1);
	if (!current_directory)
		return (ft_strdup("Default prompt: "));
	printf("malloc de %d, cd[%d] = \\0\n", len - 1, len - 1);
	i = ft_strlen(ministruct->pwd);
	current_directory[len - 2] = '\0';
	while (len - 1 > 0)
	{
		current_directory[len - 2] = ministruct->pwd[i - 1];
		i--;
		len--;
	}
	return (current_directory);
}

void	init_ministruct(char **env, t_shell *ministruct)
{
	ministruct->pwd = get_env("PWD=", env);
	ministruct->prompt = get_promt(ministruct);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	ministruct;

	if (argc && *argv && *env)
	{
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
				break ;
			}
			free(ministruct.line);
		}
	}
	return (0);
}
