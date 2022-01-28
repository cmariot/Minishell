/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:48:19 by flee              #+#    #+#             */
/*   Updated: 2022/01/28 15:16:16 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(int error_id, char *directory)
{
	print(2, "minishell: cd: ");
	if (error_id == NO_SUCH_FILE)
		print(2, "%s : No such file or directory\n", directory);
	else if (error_id == NOT_A_DIR)
		print(2, "Not a directory: %s\n", directory);
	else if (error_id == PERMISSION)
		print(2, "%s: Permission denied\n", directory);
	else if (error_id == INVALID_OPTION)
		print(2, "%s: invalid option\n", directory);
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
		print(2, "minishell: cd: OLDPWD not set\n");
	return (1);
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
	if (access(directory_path, F_OK) == 0)
		if (ft_isadirectory(directory_path) == TRUE)
			if (access(directory_path, X_OK) == 0)
				if (chdir(directory_path) == 0)
					return (0);
	if (cdpath(minishell->env, directory_path) == 0)
		return (0);
	return (1);
}

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
	if (oldpwd)
	{
		add_to_env(minishell, minishell->env, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	pwd = getcwd(NULL, 255);
	if (pwd)
	{
		add_to_env(minishell, minishell->env, "PWD", pwd);
		free(pwd);
	}
	return (global_exit_status(cd_return));
}
