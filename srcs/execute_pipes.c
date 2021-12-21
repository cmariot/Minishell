/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:22:23 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/21 13:54:57 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exectute_pipes(t_command_line *command_line, t_redir *redir)
{
	int	stdin_bckp;
	int	stdout_bckp;

	int	fd_in;
	int	fd_out;

	//backup stdin and stdout
	stdin_bckp = dup(STDIN);
	stdout_bckp = dup(STDOUT);
	
	//get the new stdin
	int		i;
	int		infile;

	infile = 0;
	//Dans le cas ou on a une redirection in
	if (command_line->number_of_redirections)
	{
		i = 0;
		while (redir[i].redirection_type)
		{
			if (ft_strcmp("<", redir[i].redirection_type))
			{
				if (redir[i].filename)
				{
					//verifier acces
					fd_in = open(redir[i].filename, O_RDONLY);
					infile = 1;
				}
				else
					ft_putstr_fd("Error, no filename for the < redirection.\n", 2);
			}
			i++;
		}
	}
	//Autrement on utilise STDIN
	if (!infile)
	{
		fd_in = dup(stdin_bckp);
	}


	//get the new stdout
	int	outfile;
	//int	i;

	i = 0;
	while (i < command_line->number_of_redirections)
	{
		//redirect input
		dup2(fd_in, 0);
		close(fd_in);
		//trouver l'output
		if (command_line->number_of_redirections)
		{
			i = 0;
			while (redir[i].redirection_type)
			{
				if (ft_strcmp(">", redir[i].redirection_type))
				{
					if (redir[i].filename)
					{
						//verifier acces
						fd_out = open(redir[i].filename, O_RDONLY);
						outfile = 1;
					}
					else
						ft_putstr_fd("Error, no filename for the > redirection.\n", 2);
				}
				i++;
			}
		}
		if (!fd_out)
		{
			fd_out = dup(stdout_bckp);
		}
		i++;
	}




}
