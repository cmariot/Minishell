/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:01:40 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/08 12:54:02 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>

typedef struct s_command_table {
	char	**splitted_line;
	char	*command;
	char	**args;
	bool	pipe;
	char	*command2;
	char	**args2;
	bool	redir_in;
	bool	redir_out;
	bool	heredoc;
	bool	redir_out_append;
	char	*filename;
}	t_command_table;

#endif
