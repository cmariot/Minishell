/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/07 17:58:53 by cmariot          ###   ########.fr       */
=======
/*   Updated: 2021/12/08 15:10:31 by cmariot          ###   ########.fr       */
>>>>>>> 817117ae0db16b021c495c6821c2c799ea9deb69
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
<<<<<<< HEAD
=======
# include <stdbool.h>

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
>>>>>>> 817117ae0db16b021c495c6821c2c799ea9deb69

typedef struct s_shell {
	char	**env;
	char	*line;
	char	*prompt;
	char	*pwd;
}	t_shell;

// get_env.c
char	*get_env(char *name, char **env);
char	*ft_readline(char *prompt);
char	**copy_array(char **array);

#endif
