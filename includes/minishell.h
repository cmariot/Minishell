/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/04 16:32:15 by cmariot          ###   ########.fr       */
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
# include <sys/types.h>
# include <time.h>

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
	size_t	number_of_redirections;
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
t_env			*env_cpy(t_env *env);

//builtin_echo.c
int				builtin_echo(char **command_and_args);

// array_utils.c
char			**join_array_that_follow(char **old, char *str);
char			**remove_str_from_array(char **old, char *str);

// env.c		
t_env			*save_env(char **array);
bool			contains_equal(char *str, t_env *env);

// get_command.c
void			get_command_line(t_shell *minishell,
					t_command_line *command_line);
char			*get_prompt(void);
char			*get_env_value(char *name, t_env *env);

// env_list_utils.c
t_env			*ft_lstnew_env(void *name, char *value);
void			ft_lstadd_back_env(t_env **alst, t_env *new);
void			ft_lstdelone_env(t_env *env, void (*del)(void *));
void			ft_lstclear_env(t_env **env, void (*del)(void *));
t_env			*ft_lstlast_env(t_env *lst);

// parse.c
int				parse(t_command_line *command_line, t_shell *minishell);
size_t			count_commands(char **splitted_line);

// parse_simple_commands.c
int				get_simple_commands(t_command_line *command_line,
					char **splitted_line, t_env *env);
// parse_redirections.c
int				parse_redirections(t_command_line *command_line);
int				is_redirection(char *element);

// print_structure.c
void			print_command_line(t_command_line *command_line);

// builtin.c
int				builtin(char *command, t_shell *minishell);

// env_builtin.c
int				builtin_env(t_env *env);
int				builtin_export(t_env *env, char **args);
t_env			*builtin_unset(t_env *env, char **names);
void			builtin_exit(t_shell *minishell, char **args);
void			add_to_env(t_env *env, char *name, char *value);

// pipielne.c
void			create_pipeline(t_command_line *command_line,
					t_shell *minishell);

// pwd_builtin.c
int				builtin_pwd(t_shell *minishell);

// split.c
char			**split_command_line(char *line);
char			**join_heredoc(char **array);
char			**ft_split_space(char **array);
int				ft_charset(char c, char *charset);

//execute.c
void			execute(t_shell *minishell, t_command_line *command_line);
void			search_exec(t_shell *minishell, t_command_line *command_line,
					size_t i);
char			**envlist_to_array(t_env *envlist);
void			make_pipe(t_shell *minishell, t_command_line *command_line);

// expand_env_variable.c
void			expand_env_variable(char **splitted_line, t_env *env);

// check quote
int				check_quote(char *line);

// handler signal
int				signal_catcher(void);
void			ft_handler(int sig, siginfo_t *info, void *secret);

// cd
int				builtin_cd(t_shell *minishell);

//remove_comments.c
char			**remove_comments(char **splitted_line);

size_t			ft_arraylen(char **array);
bool			ft_isadirectory(char *path);

int				return_global_exit_status(void);
void			change_global_exit_status(int new_value);

#endif
