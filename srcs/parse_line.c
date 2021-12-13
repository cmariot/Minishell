/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 13:03:31 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_table(t_command_table *command)
{
	int	i;

	printf("LINE = %s\n", command->line);
	printf("LINE_SPLITTED =\n");
	i = 0;
	while (command->line_splitted[i])
	{
		printf("\tline_splitted[%d] = [%s]\n", i, command->line_splitted[i]);
		i++;
	}
	printf("PIPE = %d\n", command->pipe);
	printf("REDIR_IN (>) = %d\n", command->redir_in);
	printf("REDIR_OUT (<) = %d\n", command->redir_out);
	printf("HEREDOC (<<) = %d\n", command->heredoc);
	printf("REDIR_OUT_APPEND (>>) = %d\n", command->redir_out_append);
}

void	get_booleans(char *splitted, t_command_table *command)
{
	if (ft_strnstr(splitted, "|", 1) == 0)
		command->pipe = 1;
	else if (ft_strnstr(splitted, "<", 1) == 0)
		command->redir_in = 1;
	else if (ft_strnstr(splitted, ">", 1) == 0)
		command->redir_out = 1;
	else if (ft_strnstr(splitted, "<<", 2) == 0)
		command->heredoc = 1;
	else if (ft_strnstr(splitted, ">>", 2) == 0)
		command->redir_out_append = 1;
}

// need to split with metacharacters :
// ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
int	parse_line(t_command_table *command, char *line)
{
	int	i;

	if (command->line != NULL)
		free(command->line);
	command->line = ft_strdup(line);
	if (command->line_splitted != NULL)
		ft_free_array(command->line_splitted);
	if (line != NULL)
		command->line_splitted = ft_split(line, ' ');
	command->command1 = command->line_splitted[0];
	command->args1 = command->line_splitted + 1;
	i = 0;
	while (command->line_splitted[i] != NULL)
		get_booleans(command->line_splitted[i++], command);
	print_command_table(command);
	return (0);
}
