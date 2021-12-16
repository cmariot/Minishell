/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 14:16:54 by cmariot          ###   ########.fr       */
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
typedef struct s_main_command {
	char	*command;
	char	**args;
}	t_main_command;

//Structure sauvegardant tous les éléments d'une ligne de commande
typedef struct s_command_line {
	char			*line;
	char			**splitted_line;
	t_main_command	main;
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
void			init_minishell(t_shell *ministruct, char **env);
void			reset_minishell(t_command_line *command_line);
void			free_minishell(t_shell *ministruct);

// env.c		
t_env			*save_env(char **array);

// get_c		ommand.c
void			get_command_line(t_shell *minishell,
					t_command_line *command_line);
char			*get_prompt(t_shell *ministruct);
char			*get_env_value(char *name, t_env *env);

// env_l		ist_utils.c
t_env			*ft_lstnew_env(void *name, char *value);
void			ft_lstadd_back_env(t_env **alst, t_env *new);
void			ft_lstdelone_env(t_env *env, void (*del)(void *));
void			ft_lstclear_env(t_env **env, void (*del)(void *));
t_env			*ft_lstlast_env(t_env *lst);

// parse		.c
void			parse(t_command_line *command_line);

// built		in.c
int				builtin(char *command, t_shell *minishell);

// env_b		uiltin.c
void			env_builtin(t_env *env);
void			setenv_builtin(t_env *env, char *name, char *value);
void			unsetenv_builtin(t_env *env, char *name);

// pwd_b		uiltin.c
void			pwd_builtin(t_shell *minishell);

void			ft_putarray(char *name, char **array);

int				put_in_main(char **splitted_line, t_main_command *main);
void			print_command_line(t_command_line *command_line);
t_pipe_command	*put_in_pipe(t_command_line *command_line,
					char **splitted_line, int args_index);

//split.c
char			**split_minishell(char *str);

#endif
