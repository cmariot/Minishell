/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:31:41 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/22 14:28:29 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_in_redir_struct(char *redir_type, char *filename, t_redir *redir)
{
	redir->redirection_type = ft_strdup(redir_type);
	redir->filename = ft_strdup(filename);
}

t_redir	*put_in_redir(t_command_line *command_line,
		char **splitted_line)
{
	t_redir	*redirs;
	int		i;
	int		j;
	int		len;

	len = command_line->number_of_redirections + 1;
	redirs = ft_calloc(len, sizeof(t_redir));
	if (!redirs)
		return (NULL);
	i = 0;
	j = 0;
	while (splitted_line[i + 1])
	{
		if (ft_strcmp(splitted_line[i], "<<") == 0)
			put_in_redir_struct("<<", splitted_line[i + 1], &redirs[j++]);
		else if (ft_strcmp(splitted_line[i], ">>") == 0)
			put_in_redir_struct(">>", splitted_line[i + 1], &redirs[j++]);
		else if (ft_strcmp(splitted_line[i], ">") == 0)
			put_in_redir_struct(">", splitted_line[i + 1], &redirs[j++]);
		else if (ft_strcmp(splitted_line[i], "<") == 0)
			put_in_redir_struct("<", splitted_line[i + 1], &redirs[j++]);
		i++;
	}
	return (redirs);
}
