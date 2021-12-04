/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/04 09:32:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	ministruct;
	char	*line;

	if (argc && *argv && *env)
	{
		while (1)
		{
			ministruct.pwd = get_pwd(env);
			if (ministruct.pwd == NULL)
				return (-1);
			line = ft_readline(ministruct.pwd);
			if (ft_strcmp(line, "pwd") == 0)
				printf("%s\n", ministruct.pwd);
			else if (ft_strcmp(line, "exit") == 0)
			{
				free(line);
				free(ministruct.pwd);
				break ;
			}
			free(line);
		}
	}
	return (0);
}
