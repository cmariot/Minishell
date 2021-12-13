/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:48:25 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 14:37:13 by cmariot          ###   ########.fr       */
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
	printf("INPUT_REDIR (<) = %d\n", command->input_redir);
	printf("OUTPUT_REDIR (>) = %d\n", command->output_redir);
	printf("OUTPUT_REDIR_APPEND (>>) = %d\n", command->output_redir_append);
	printf("HEREDOC (<<) = %d w/ LIMITER = %s\n",
		command->heredoc, command->limiter);
}

void	get_booleans(char *splitted, t_command_table *command)
{
	if (ft_strnstr(splitted, "|", ft_strlen(splitted)) != 0)
		command->pipe = 1;
	else if (ft_strnstr(splitted, "<<", ft_strlen(splitted)) != 0)
		command->heredoc = 1;
	else if (ft_strnstr(splitted, ">>", ft_strlen(splitted)) != 0)
		command->output_redir_append = 1;
	else if (ft_strnstr(splitted, "<", ft_strlen(splitted)) != 0)
		command->input_redir = 1;
	else if (ft_strnstr(splitted, ">", ft_strlen(splitted)) != 0)
		command->output_redir = 1;
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
	{
		get_booleans(command->line_splitted[i], command);
		i++;
	}
	print_command_table(command);
	return (0);
}
