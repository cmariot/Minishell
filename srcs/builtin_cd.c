/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:48:19 by flee              #+#    #+#             */
/*   Updated: 2022/01/12 13:46:18 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_SUCH_FILE 0
#define NOT_A_DIR 1 
#define PERMISSION 2
#define INVALID_OPTION 3

int	cd_error(int error_id, char *directory)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (error_id == NO_SUCH_FILE)
	{
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error_id == NOT_A_DIR)
	{
		ft_putstr_fd("Not a directory: ", 2);
		ft_putstr_fd(directory, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_id == PERMISSION)
	{
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (error_id == INVALID_OPTION)
	{
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
	return (1);
}

int	go_home(t_shell *minishell)
{
	char		*home;

	home = get_env_value("HOME", minishell->env);
	if (home == NULL)
		return (1);
	if (access(home, F_OK) != 0)
		cd_error(NO_SUCH_FILE, home);
	else if (ft_isadirectory(home) == FALSE)
		cd_error(NOT_A_DIR, home);
	else if (access(home, X_OK) != 0)
		cd_error(PERMISSION, home);
	else if (chdir(home) == 0)
	{
		free(home);
		return (0);
	}
	free(home);
	return (1);
}

int	go_to_oldpwd(t_shell *minishell)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", minishell->env);
	if (oldpwd)
	{
		if (access(oldpwd, F_OK) != 0)
			cd_error(NO_SUCH_FILE, oldpwd);
		else if (ft_isadirectory(oldpwd) == FALSE)
			cd_error(NOT_A_DIR, oldpwd);
		else if (access(oldpwd, X_OK) != 0)
			cd_error(PERMISSION, oldpwd);
		else if (chdir(oldpwd) == 0)
		{
			ft_putstr_fd(oldpwd, 1);
			ft_putchar('\n');
			free(oldpwd);
			return (0);
		}
		free(oldpwd);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
}

int	go_to_dir(char *directory_path, t_shell *minishell)
{
	if (directory_path[0] == '-')
	{
		if (ft_strcmp(directory_path, "-") == 0)
			return (go_to_oldpwd(minishell));
		else
			return (cd_error(INVALID_OPTION, directory_path));
	}
	else if (ft_strcmp("#", directory_path) == 0)
		go_home(minishell);
	if (access(directory_path, F_OK) != 0)
		cd_error(NO_SUCH_FILE, directory_path);
	else if (ft_isadirectory(directory_path) == FALSE)
		cd_error(NOT_A_DIR, directory_path);
	else if (access(directory_path, X_OK) != 0)
		cd_error(PERMISSION, directory_path);
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
	char		*pwd;
	char		*oldpwd;
	int			cd_return;

	oldpwd = getcwd(NULL, 255);
	if (minishell->command_line.command->command_and_args[1] != NULL)
		cd_return
			= go_to_dir(minishell->command_line.command->command_and_args[1],
				minishell);
	else
		cd_return = go_home(minishell);
	add_to_env(minishell->env, "OLDPWD", oldpwd);
	if (oldpwd)
		free(oldpwd);
	pwd = getcwd(NULL, 255);
	add_to_env(minishell->env, "PWD", pwd);
	if (pwd)
		free(pwd);
	return (cd_return);
}
