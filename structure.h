/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 22:48:52 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 22:56:26 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

//Liste chainée dans laquelle on sauvegarde le char **env
typedef struct s_env {
	char	*name;
	char	*value;
	void	*next;
}	t_env;

//Structure sauvegardant tous les éléments d'une ligne de commande
typedef struct s_command_line {
	char			*command_line;
	char			**splitted_command_line;
	t_first_command	command;
	int				number_of_pipes;
	t_pipe_command	*pipe_command;
	int				number_of_redirections;
	t_redir			*redirection;
}	t_command_line;

//Sous-structure de t_command_line,
//stocke la 1ère commande et ses arguments
typedef struct s_first_command {
	char	*command;
	char	**args;
}	t_first_command;

// Sous-structure de t_command_line,
// stocke, s'il y en a, la ou les commandes qui suivent un pipe
typedef struct s_pipe_command {
	char	*command;
	char	**args;
}	t_pipe_command;

// Sous-structure de t_command_line,
// stocke, s'il y en a, la ou les redirections à effectuer
// (on devra gérer aussi le cas heredoc, mais différemment)
typedef struct s_redir {
	char	*redirection_type;
	char	*filename;
}	t_redir;

//Structure principale
typedef struct s_shell {
	t_env			*env;
	char			*prompt;
	char			*line;
	int				number_of_command_lines;
	t_command_line	*command_line;
}	t_shell;

#endif
