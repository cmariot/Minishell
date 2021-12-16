/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:55:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 16:16:37 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	current_directory_len(char *pwd)
{
	int	pwd_last_index;
	int	cd_len;

	pwd_last_index = ft_strlen(pwd) - 1;
	cd_len = 0;
	while (pwd[pwd_last_index] != '/' && pwd_last_index >= 0)
	{
		cd_len++;
		pwd_last_index--;
	}
	return (cd_len);
}

// The prompts is set as the name of the current directory.
char	*get_prompt(t_shell *minishell)
{
	char	*pwd;
	int		pwd_last_index;
	char	*current_directory;
	int		cur_dir_len;
	char	*prompt;

	pwd = get_env_value("PWD", minishell->env);
	if (pwd == NULL)
		return (ft_strdup("Minishell ➤ "));
	cur_dir_len = current_directory_len(pwd);
	current_directory = ft_calloc(cur_dir_len + 1, sizeof(char));
	if (!current_directory)
		return (ft_strdup("Minishell ➤ "));
	pwd_last_index = ft_strlen(pwd) - 1;
	while (cur_dir_len - 1 >= 0)
	{
		current_directory[cur_dir_len-- - 1] = pwd[pwd_last_index--];
	}
	prompt = ft_strjoin(current_directory, " ➤ ");
	free(current_directory);
	free(pwd);
	return (prompt);
}
