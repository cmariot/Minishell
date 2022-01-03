/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:48:19 by flee              #+#    #+#             */
/*   Updated: 2022/01/03 14:15:09 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gestion d'erreur a voir ?
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

//valeur de retour ?
int	go_home(t_shell *minishell)
{
	char		*home;

	home = get_env_value("HOME", minishell->env);
	if (home == NULL)
		return (1);
	if (access(home, F_OK) != 0)
		printf("minishell: cd: %s: No such file or directory\n", home);
	else if (ft_isadirectory(home) == FALSE)
		printf("minishell: cd: not a directory: %s\n", home);
	else if (access(home, X_OK) != 0)
		printf("minishell: cd: %s: Permission denied\n", home);
	else if (chdir(home) == 0)
	{
		free(home);
		return (0);
	}
	free(home);
	return (1);
}

int	go_to_dir(char *directory_path, t_shell *minishell)
{
	if (directory_path[0] == '~')
		directory_path = expand_tilde(minishell, directory_path);
	else if (access(directory_path, F_OK) != 0)
		printf("minishell: cd: %s: No such file or directory\n",
			minishell->command_line.command->command_and_args[1]);
	else if (ft_isadirectory(directory_path) == FALSE)
		printf("minishell: cd: not a directory: %s\n", directory_path);
	else if (access(directory_path, X_OK) != 0)
		printf("minishell: cd: %s: Permission denied\n",
			minishell->command_line.command->command_and_args[1]);
	else if (chdir(directory_path) == 0)
		return (0);
	return (1);
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
int	builtin_cd(t_shell *minishell)
{
	char		*cwd;
	int			cd_return;

	if (minishell->command_line.command->command_and_args[1] != NULL)
		cd_return
			= go_to_dir(minishell->command_line.command->command_and_args[1],
				minishell);
	else
		cd_return = go_home(minishell);
	cwd = getcwd(NULL, 255);
	add_to_env(minishell->env, "PWD", cwd);
	free(cwd);
	return (cd_return);
}
