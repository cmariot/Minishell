/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2022/02/06 12:47:22 by cmariot          ###   ########.fr       */
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

# define NO_SUCH_FILE 0
# define NOT_A_DIR 1 
# define PERMISSION 2
# define INVALID_OPTION 3

# define INTERACTIVE 0
# define COMMAND 1
# define HEREDOC 2

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
	int		pid;
	int		pipe_fd[2];
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
	char			**env_array;
	t_command_line	command_line;
}	t_shell;

// init_minishell.c
void	init_minishell(t_shell *ministruct, char **env);
void	reset_minishell(t_command_line *command_line, t_shell *minishell);
void	free_minishell(t_shell *ministruct);
t_env	*env_cpy(t_env *env);

// array_utils.c
char	**join_array_that_follow(char **old, char *str);
char	**remove_str_from_array(char **old, char *str);

// env.c
t_env	*save_env(char **array);
bool	contains_equal(char *str, t_env *env);

// get_command.c
void	get_command_line(t_shell *minishell,
			t_command_line *command_line);
char	*get_prompt(void);
char	*get_env_value(char *name, t_env *env);

//parse_command_and_args.c
int		get_command_and_args(t_command_line *command_line);

// env_list_utils.c
t_env	*ft_lstnew_env(void *name, char *value);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lstdelone_env(t_env *env, void (*del)(void *));
void	ft_lstclear_env(t_env **env, void (*del)(void *));
t_env	*ft_lstlast_env(t_env *lst);
char	**envlist_to_array(t_env *envlist);

// parse.c
int		parse(t_command_line *command_line, t_shell *minishell);
size_t	count_commands(char **splitted_line);

// parse_simple_commands.c
int		get_simple_commands(t_command_line *command_line,
			char **splitted_line);

// parse_redirections.c
int		parse_redirections(t_command_line *command_line, t_env *env);
int		is_redirection(char *element);

// print_structure.c
void	print_command_line(t_command_line *command_line);

// builtin.c
int		builtin(char *command, t_shell *minishell);
int		builtin_env(t_env *env, char *first_arg);
int		builtin_export(t_shell *minishell, char **args);
t_env	*builtin_unset(t_env *env, char **names);
void	builtin_exit(t_shell *minishell, char **args, int *backup_fd);
int		builtin_pwd(t_shell *minishell, char *first_arg);
int		builtin_cd(t_shell *minishell);
int		cd_error(int error_id, char *directory);
int		cdpath(t_env *env, char *dir);
int		builtin_echo(char **command_and_args);

// pipeline.c
void	create_pipeline(t_command_line *command_line,
			t_shell *minishell, int *backup_fd);

//execute.c
void	execute(t_shell *minishell, t_command_line *command_line);

//execute_builtin.c
int		command_is_builtin(t_shell **minishell, t_simple command,
			int *backup_fd);

//execute_simple_command.c
void	execute_simple_command(t_shell *minishell, t_simple command,
			int *backup_fd);

//execute_with_path.c
int		command_with_absolute_path(t_simple command, t_shell *minishell,
			int *backup_fd);

//execute_without_path.c

int		command_in_path(t_shell *minishell, t_simple command,
			int *backup_fd);

//execution.c
int		execution(char **command_path, t_simple command, t_shell *minishell,
			int *backup_fd);
int		file_redirection(t_simple command);
void	restore_file_redirection(t_simple command, int stdin_backup,
			int stdout_backup);

// check quote
int		check_quote(char *line);

//expansion.c
int		expansion(t_command_line *command_line, t_env *env);
int		expand_tilde(char **command_array, t_env *env);
int		expand_env_variable(char **splitted_line, t_env *env);
void	quotes_removal(char **array);

int		error_invalid_identifier(char **args, size_t i);
void	add_to_env(t_shell *minishell, t_env *env, char *name, char *value);
int		get_name_len(char **args, size_t i);

// signal.c
int		signal_catcher(int status);
void	ft_handler(int sig, siginfo_t *info, void *secret);

//	tokens_get.c / tokens_count.c / tokens_fill.c
int		get_tokens_array(char *line, char ***array);
size_t	count_number_of_tokens(char *line);
int		fill_tokens_array(char **array, char *line,
			size_t number_of_tokens);
bool	is_blank(char *line, size_t i);
bool	is_a_metacharacter(char *line, size_t *i, bool opt);
void	parse_word(char *line, size_t *i);

void	add_to_env(t_shell *minishell, t_env *env, char *name,
			char *value);

//global_exit_status.c
int		return_global_exit_status(void);
int		global_exit_status(int new_value);
int		expand_exit_status(char **str, size_t *i);

//str_and_array_modification.c
int		remove_name_from_str(char *name, char *str, size_t *i);
int		add_value_to_str(char **str, char *name, char *value,
			size_t *i);
int		remove_from_str(char **str, size_t *i, size_t name_len);
int		remove_from_array(char **splitted_line, int i);

//redirection.c
int		input_redirection(t_simple command);
int		output_redirection(t_simple command);

//heredoc.c
char	*new_heredoc_name(void);
int		create_heredoc(char *filename, char *limiter, t_env *env);
void	remove_heredocs(t_simple command);

int		catch_signal(int comportement);

void	rl_replace_line(const char *str, int nb);

int		search_dollar_in_str(char **str, t_env *env);
void	remove_quotes_in_str(char *str);
int		replace_tilde(char **str, char **home);
void	remove_quote(char *str, size_t j);
int		str_quotes_removal(char **str);
int		str_tilde_expansion(char **str, t_env *env);
int		command_and_args_expansion(t_command_line *command, t_env *env);
char	**command_split(char *s, char c);
int		filename_expansion(t_redir *redir, char **array,
			int array_index, t_env *env);
bool	contains_slash(char *command);
int		search_value(char **str, size_t *i, char **name, char **value);
void	line_expansion(char **line, t_env *env);
bool	need_to_expand_heredoc(char **limiter);
int		search_dollar_in_str2(char **str, t_env *env);

#endif
