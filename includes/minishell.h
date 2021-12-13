/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/13 14:39:34 by cmariot          ###   ########.fr       */
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

typedef struct s_command_table {
	char	*line;
	char	**line_splitted;
	char	*command1;
	char	**args1;
	bool	pipe;
	char	*command2;
	char	**args2;
	bool	input_redir;
	bool	output_redir;
	bool	heredoc;
	char	*stop_heredoc;
	bool	output_redir_append;
	char	*limiter;
	char	*filename;
}	t_command_table;

typedef struct s_env {
	char	*name;
	char	*value;
	void	*next;
}	t_env;

typedef struct s_shell {
	char				*line;
	char				*prompt;
	char				*pwd;
	t_env				*env;
	t_command_table		command;
}	t_shell;

// ministruct_utils.c
void	init_ministruct(t_shell *ministruct, char **env);
void	update_ministruct(t_shell *ministruct);
void	free_ministruct(t_shell *ministruct);

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
int		parse_line(t_command_table *command, char *line);

#endif
