/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:31:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/18 15:58:38 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*put_in_redir(t_command_line *command_line,
		char **splitted_line)
{
	t_redir	*redirs;
	int		i;
	int		redir_index;
	int		len;

	len = command_line->number_of_pipes + 1;
	redirs = ft_calloc(len, sizeof(t_redir));
	if (!redirs)
		return (NULL);
	i = 0;
	redir_index = 0;
	while (splitted_line[i + 1])
	{
		if (ft_strcmp(splitted_line[i], "<<") == 0)
		{
			redirs[i].redirection_type = ft_strdup("<<");
			redirs[i].filename = ft_strdup(splitted_line[i + 1]);
		}
		else if (ft_strcmp(splitted_line[i], ">>") == 0)
		{
			redirs[i].redirection_type = ft_strdup(">>");
			redirs[i].filename = ft_strdup(splitted_line[i + 1]);
		}
		else if (ft_strcmp(splitted_line[i], ">") == 0)
		{
			redirs[i].redirection_type = ft_strdup(">");
			redirs[i].filename = ft_strdup(splitted_line[i + 1]);
		}
		else if (ft_strcmp(splitted_line[i], "<") == 0)
		{
			redirs[i].redirection_type = ft_strdup("<");
			redirs[i].filename = ft_strdup(splitted_line[i + 1]);
		}
		i++;
	}
	return (redirs);
}
