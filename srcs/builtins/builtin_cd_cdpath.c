/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_cdpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:15:06 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/28 18:42:16 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_cdpath(char *cdpath, char *dir)
{
	char	*cdpath_slash;
	char	*final_dir;

	cdpath_slash = ft_strjoin(cdpath, "/");
	final_dir = ft_strjoin(cdpath_slash, dir);
	if (access(final_dir, F_OK) != 0)
		;
	else if (ft_isadirectory(final_dir) == FALSE)
		;
	else if (access(final_dir, X_OK) != 0)
		;
	else if (chdir(final_dir) == 0)
	{
		free(cdpath_slash);
		free(final_dir);
		return (0);
	}
	free(cdpath_slash);
	free(final_dir);
	return (1);
}

int	cd_final_error(char *directory_path)
{
	if (access(directory_path, F_OK) != 0)
	{
		cd_error(NO_SUCH_FILE, directory_path);
	}
	else if (ft_isadirectory(directory_path) == FALSE)
	{
		cd_error(NOT_A_DIR, directory_path);
	}
	else if (access(directory_path, X_OK) != 0)
	{
		cd_error(PERMISSION, directory_path);
	}
	return (1);
}

int	cdpath(t_env *env, char *dir)
{
	char	*cdpath;
	char	**cdpath_array;
	size_t	i;

	cdpath = get_env_value("CDPATH", env);
	if (cdpath)
	{
		cdpath_array = ft_split(cdpath, ':');
		if (cdpath_array)
		{
			i = 0;
			while (cdpath_array[i] != NULL)
			{
				if (go_to_cdpath(cdpath_array[i++], dir) != 0)
					continue ;
				print(1, "%s/%s\n", cdpath_array[i - 1], dir);
				ft_free_array(cdpath_array);
				free(cdpath);
				return (0);
			}
			ft_free_array(cdpath_array);
		}
		free(cdpath);
	}
	return (cd_final_error(dir));
}
