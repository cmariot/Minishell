/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/14 12:28:41 by cmariot          ###   ########.fr       */
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
	char			*line;
	char			**splitted_line;
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
	t_command_line	command_line;
}	t_shell;

// init_minishell.c
void	init_minishell(t_shell *ministruct, char **env);

// env.c
t_env	*save_env(char **array);
char	*get_env_value(char *name, t_env *env);

// get_command.c
void	get_command(t_shell *minishell, t_command_line *command_line);
char	*get_prompt(t_shell *ministruct);

// list_t_env.c
t_env	*ft_lstnew_env(void *name, char *value);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lstdelone_env(t_env *env, void (*del)(void *));
void	ft_lstclear_env(t_env **env, void (*del)(void *));
t_env	*ft_lstlast_env(t_env *lst);

// env_builtin.c
void	ft_env(t_env *env);
void	ft_setenv(t_env *env, char *name, char *value);
void	ft_unsetenv(t_env *env, char *name);

// parse_line.c
//int		parse_line(t_command_table *command, char *line);

#endif
