/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 09:18:08 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <stdbool.h>

# define FALSE 0
# define TRUE 1

//Liste chainée dans laquelle on sauvegarde le char **env
typedef struct s_env {
	char	*name;
	char	*value;
	void	*next;
}	t_env;

// Sous-structure de t_command_line,
// stocke, s'il y en a, la ou les redirections à effectuer
// (on devra gérer aussi le cas heredoc, mais différemment)
typedef struct s_redir {
	char	*redirection_type;
	char	*filename;
}	t_redir;

// Sous-structure de t_command_line,
// stocke, s'il y en a, la ou les commandes qui suivent un pipe
typedef struct s_pipe_command {
	char	*command;
	char	**args;
}	t_pipe_command;

//Sous-structure de t_command_line,
//stocke la 1ère commande et ses arguments
typedef struct s_first_command {
	char	*command;
	char	**args;
}	t_first_command;

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

//Structure principale
typedef struct s_shell {
	t_env			*env;
	char			*prompt;
	char			*line;
	int				number_of_command_lines;
	t_command_line	*command_line;
}	t_shell;

// ministruct_utils.c
void	init_ministruct(t_shell *ministruct, char **env);
void	update_ministruct(t_shell *ministruct);
void	free_ministruct(t_shell *ministruct);
char	*get_env_value(char *name, t_env *env);

// list_t_env.c
t_env	*ft_lstnew_env(void *name, char *value);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lstdelone_env(t_env *env, void (*del)(void *));
void	ft_lstclear_env(t_env **env, void (*del)(void *));
t_env	*ft_lstlast_env(t_env *lst);

// env.c
t_env	*save_env(char **array);
void	print_env(t_env *env);
char	*get_name(char *env_line);
char	*get_value(char *env_line);

// setenv.c
void	ft_setenv(t_env *env, char *name, char *value);

// unsetenv.c
void	ft_unsetenv(t_env *env, char *name);

// prompt.c
char	*get_prompt(t_shell *ministruct);

// parse_line.c
//int		parse_line(t_command_table *command, char *line);

#endif
