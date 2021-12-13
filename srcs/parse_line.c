/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 09:37:00 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to split with metacharacters :
// ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
int	parse_line(t_command_table *command, char *line)
{
	if (command->line != NULL)
		free(command->line);
	command->line = ft_strdup(line);
	if (command->line_splitted != NULL)
		ft_free_array(command->line_splitted);
	if (line != NULL)
		command->line_splitted = ft_split(line, ' ');
	command->command1 = command->line_splitted[0];
	printf("exec %s\n", command->command1);
	return (0);
}
