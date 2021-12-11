/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:55:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/11 19:54:38 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// The prompts is set as the name of the current directory.
char	*get_prompt(t_shell *ministruct)
{
	char	*prompt;
	char	*current_directory;
	int		len;
	int		i;

	if (!ministruct->pwd)
		return (ft_strdup("/ ➤ "));
	i = ft_strlen(ministruct->pwd);
	if (i == 1 && ft_strcmp(ministruct->pwd, "/") == 0)
		return (ft_strdup("/ ➤ "));
	len = 0;
	while (ministruct->pwd[i] != '/' && i-- != -1)
		len++;
	current_directory = malloc(sizeof(char) * len);
	if (!current_directory)
		return (ft_strdup("Minishell ➤ "));
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
