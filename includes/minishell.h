/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/25 15:35:29 by cmariot          ###   ########.fr       */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

//Liste chainée dans laquelle on sauvegarde le char **env
typedef struct s_env {
	char	*name;
	char	*value;
	void	*next;
}	t_env;

typedef struct s_redir {
	char	*redir_type;
	char	*filename;
}	t_redir;

typedef struct s_simple {
	char	**command_array;
	char	**command_and_args;
	t_redir	*redir;
}	t_simple;

//Structure sauvegardant tous les éléments d'une ligne de commande
typedef struct s_command_line {
	char			*line;
	char			**splitted_line;
	size_t			number_of_simple_commands;
	t_simple		*command;
}	t_command_line;

//Structure principale
typedef struct s_shell {
	t_env			*env;
	t_command_line	command_line;
}	t_shell;

// init_minishell.c
void			init_minishell(t_shell *ministruct, char **env);
void			reset_minishell(t_command_line *command_line);
void			free_minishell(t_shell *ministruct);

// array_utils.c
char			**join_array_that_follow(char **old, char *str);
char			**remove_str_from_array(char **old, char *str);

// env.c		
t_env			*save_env(char **array);

// get_command.c
void			get_command_line(t_shell *minishell,
					t_command_line *command_line);
char			*get_prompt(t_shell *ministruct);
char			*get_env_value(char *name, t_env *env);

// env_list_utils.c
t_env			*ft_lstnew_env(void *name, char *value);
void			ft_lstadd_back_env(t_env **alst, t_env *new);
void			ft_lstdelone_env(t_env *env, void (*del)(void *));
void			ft_lstclear_env(t_env **env, void (*del)(void *));
t_env			*ft_lstlast_env(t_env *lst);

// parse.c
int				parse(t_command_line *command_line, t_shell *minishell);

// parse_simple_commands.c
void			get_simple_commands(t_command_line *command_line,
					char **splitted_line);
// parse_redirections.c
int				parse_redirections(t_command_line *command_line);
int				is_redirection(char *element);

// print_structure.c
void			print_command_line(t_command_line *command_line);

// builtin.c
int				builtin(char *command, t_shell *minishell);

// env_builtin.c
void			env_builtin(t_env *env);
void			setenv_builtin(t_env *env, char *name, char *value);
void			unsetenv_builtin(t_env *env, char *name);

// pwd_builtin.c
void			pwd_builtin(t_shell *minishell);

// split.c
char			**split_command_line(char *line);
char			**join_heredoc(char **array);
char			**ft_split_space(char **array);
int				ft_charset(char c, char *charset);

//execute.c
void			execute(t_shell *minishell, t_command_line *command_line);
char			**envlist_to_array(t_env *envlist);

// expand_env_variable.c
void			expand_env_variable(char ***splitted_line, t_env *env);

// check quote
int				check_quote(char *line);

#endif
