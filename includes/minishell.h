/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 15:24:47 by cmariot          ###   ########.fr       */
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

typedef struct s_shell {
	t_list	*env;
	char	*line;
	char	*prompt;
	char	*pwd;
}	t_shell;

// env.c
char	*get_env_value(char *name, char **env);
t_list	*put_env_in_a_list(char **array);
bool	already_in_list(t_list *env, char *name);
void	change_value(t_list *env, char *name, char *value);
void	add_value(t_list **env, char *name, char *value);

// ministruct_utils.c
void	init_ministruct(t_shell *ministruct, char **env);
void	update_ministruct(char **env, t_shell *ministruct);
void	free_ministruct(t_shell *ministruct);

// prompt.c
char	*get_prompt(t_shell *ministruct);

#endif
