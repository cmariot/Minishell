/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/11 12:55:54 by cmariot          ###   ########.fr       */
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
	bool	redir_in;
	bool	redir_out;
	bool	heredoc;
	bool	redir_out_append;
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

// env.c
t_env	*save_env(char **array);
void	print_env(t_env *env);
void	ft_lstclear_env(t_env **env, void (*del)(void *));

// ministruct_utils.c
void	init_ministruct(t_shell *ministruct, char **env);
void	update_ministruct(t_shell *ministruct);
void	free_ministruct(t_shell *ministruct);

// prompt.c
char	*get_prompt(t_shell *ministruct);

// parse_line.c
int		parse_line(t_shell *ministruct, char *line);

#endif
