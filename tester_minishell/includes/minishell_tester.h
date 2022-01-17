/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 23:34:42 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TESTER_H
# define MINISHELL_TESTER_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FALSE 0
# define TRUE 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

char		*gnl_without_bn(int fd);

char		*add_buf_to_str(char **str, char *buf);
char		*file_to_str(char *file);
int			check_diff(char *file_bash, char *file_minishell);
char		*execute_with_bash(char *commande, int number, char **env);
char		*execute_with_minishell(char *commande, int number, char **env);

int			fork_command(char *command, char **command_and_args, char **env);
int			fork_redirection(int fd_new_file, char *command_path,
				char **command_and_args, char **env);
int			print_final_result(int numero_du_test, int result,
				int file_descriptor);
void		test(int numero_du_test, char **test_line, char **env, int *result);
int			main(int argc, char **argv, char **env);

#endif
