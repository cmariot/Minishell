/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:42:04 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 17:34:45 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_redirection(t_simple command)
{
	if (command.number_of_redirections == 0)
		return (0);
	if (input_redirection(command) == 1)
		return (1);
	if (output_redirection(command) == 1)
		return (1);
	return (0);
}

void	restore_file_redirection(t_simple command, int stdin_backup,
		int stdout_backup)
{
	size_t	i;

	if (command.number_of_redirections == 0)
		return ;
	i = 0;
	while (i < command.number_of_redirections)
	{
		if (ft_strcmp(command.redir[i].redir_type, "<<") == 0)
			unlink(command.redir[i].filename);
		i++;
	}
	dup2(stdin_backup, STDIN);
	dup2(stdout_backup, STDOUT);
	close(stdin_backup);
	close(stdout_backup);
}
