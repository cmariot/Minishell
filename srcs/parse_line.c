/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/11 13:37:55 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to split with metacharacters :
// ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
int	parse_line(t_shell *ministruct, char *line)
{
	if (ministruct->command.line != NULL)
		free(ministruct->command.line);
	ministruct->command.line = ft_strdup(line);
	if (ministruct->command.line_splitted != NULL)
		ft_free_array(ministruct->command.line_splitted);
	if (line != NULL)
		ministruct->command.line_splitted = ft_split(line, ' ');
	return (0);
}
