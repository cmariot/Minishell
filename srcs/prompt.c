/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:55:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 09:16:54 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	current_directory_len(char *pwd)
{
	int	len;
	int	i;

	i = ft_strlen(pwd);
	len = 0;
	while (pwd[i - 1] != '/' && i < 1)
	{
		len++;
		i--;
	}
	return (len);
}

// The prompts is set as the name of the current directory.
char	*get_prompt(t_shell *minishell)
{
	char	*pwd;
	char	*current_directory;
	char	*prompt;
	int		len;
	int		i;

	if (minishell->prompt != NULL)
		free(minishell->prompt);
	pwd = get_env_value("PWD", minishell->env);
	if (pwd == NULL)
		return (ft_strdup("Minishell ➤ "));
	len = current_directory_len(pwd);
	current_directory = ft_calloc(len + 1, sizeof(char));
	if (!current_directory)
		return (ft_strdup("Minishell ➤ "));
	i = ft_strlen(pwd);
	while (len - 1 != 0)
	{
		current_directory[len-- - 1] = pwd[i-- - 1];
	}
	prompt = ft_strjoin(current_directory, " ➤ ");
	free(current_directory);
	free(pwd);
	return (prompt);
}
