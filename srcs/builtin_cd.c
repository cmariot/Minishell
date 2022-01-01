/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:48:19 by flee              #+#    #+#             */
/*   Updated: 2022/01/01 14:58:46 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(t_shell *minishell, char *path)
{
	char	*home;
	char	*new_path;
	size_t	size;

	size = ft_strlen(path) - 1;
	home = get_env_value("HOME", minishell->env);
	path = ft_substr((const char *)path, 1, size);
	new_path = ft_strjoin(home, path);
	free(path);
	return (new_path);
}

void	go_home(t_shell *minishell)
{
	char		*home;

	home = get_env_value("HOME", minishell->env);
	if (home == NULL)
		return ;
	if (access(home, F_OK) == 0)
	{
		//verif is a directory a faire
		if (access(home, X_OK) == 0)
			chdir(home);
		else
			printf("minishell: cd: %s: Permission denied\n", home);
	}
	else
		printf("minishell: cd: %s: No such file or directory\n", home);
}

/* Dans le man cd :
 *	1- OK
 *	2- OK
 *	3- OK
 *	4-
 *	5-
 *	6-
 *	7-
 *	8-
 *	9-
 *	10-
 */
void	do_cd(t_shell *minishell)
{
	char		*directory_path;
	char		*cwd;

	if (minishell->command_line.command->command_and_args[1] != NULL)
	{
		directory_path = minishell->command_line.command->command_and_args[1];
		if (directory_path[0] == '~')
			directory_path = expand_tilde(minishell, directory_path);
		if (access(directory_path, F_OK) == 0)
		{
			if (access(directory_path, X_OK) == 0)
				chdir(directory_path);
			else
				printf("minishell: cd: %s: Permission denied\n",
					minishell->command_line.command->command_and_args[1]);
		}
		else
			printf("minishell: cd: %s: No such file or directory\n",
				minishell->command_line.command->command_and_args[1]);
	}
	else
		go_home(minishell);
	cwd = getcwd(NULL, 255);
	setenv_builtin(minishell->env, "PWD", cwd);
	free(cwd);
}
