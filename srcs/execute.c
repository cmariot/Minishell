/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/15 18:16:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redirection(int *stdin_backup, int *stdout_backup,
		t_simple command, int fd_output)
{
	*stdin_backup = dup(STDIN);
	*stdout_backup = dup(STDOUT);
	input_redirection(command, FALSE);
	output_redirection(command, fd_output);
}

void	restore_file_redirection(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, 0);
	dup2(stdout_backup, 1);
	close(stdin_backup);
	close(stdout_backup);
}

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */
int	execute_cmnd(char **command_path, t_simple command, char **env,
	int fd_output)
{
	pid_t	pid;
	int		status;
	int		stdin_backup;
	int		stdout_backup;

	file_redirection(&stdin_backup, &stdout_backup, command, fd_output);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Error, fork() failed.\n", 2);
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		status = execve(*command_path,
				command.command_and_args, env);
		return (status);
	}
	waitpid(pid, &status, 0);
	restore_file_redirection(stdin_backup, stdout_backup);
	if (*command_path != NULL)
		free(*command_path);
	global_exit_status(0);
	if (WIFEXITED(status))
		global_exit_status(WEXITSTATUS(status));
	return (0);
}

int	execute_command_in_current_directory(char *command_path, t_simple command,
		char **env, int fd_output)
{
	if (access(command_path + 2, F_OK) == 0
		&& access(command_path + 2, X_OK) == 0)
		if (ft_isadirectory(command_path + 2) == FALSE)
			if (!execute_cmnd(&command_path,
					command, env, fd_output))
				return (0);
	return (1);
}

int	command_in_absolute_path(t_simple command, char **env, int fd_output)
{
	char	*command_path;
	size_t	len;

	command_path
		= ft_strdup(command.command_and_args[0]);
	len = 0;
	while (command_path[len] != '/' && command_path[len])
		len++;
	if (len == ft_strlen(command_path))
	{
		free(command_path);
		return (127);
	}
	if (ft_strlen(command_path) > 2 && command_path[0] == '.' && command_path[0] == '/')
	{
		if (!execute_command_in_current_directory(command_path,
				command, env, fd_output))
			return (0);
	}
	else
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
			if (ft_isadirectory(command_path) == FALSE)
				if (!execute_cmnd(&command_path,
						command, env, fd_output))
					return (0);
	if (command_path != NULL)
		free(command_path);
	return (127);
}

/* For all the possible path of env,
   Put a '/' and the command at the end of the path,
   Check if the command exist and if it can be execute, if ok execute it.
   If it's execute, the child process stops.
   Else try the next path.  */

int	try_command_with_path(char **path_array, t_simple command, char **env,
	int fd_output)
{
	char	*path_with_slash;
	char	*command_path;

	while (*path_array)
	{
		path_with_slash = ft_strjoin(*path_array, "/");
		command_path = ft_strjoin(path_with_slash,
				command.command_and_args[0]);
		if (path_with_slash != NULL)
			free(path_with_slash);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
			if (ft_isadirectory(command_path) == FALSE)
				if (execute_cmnd(&command_path, command, env, fd_output) == 0)
					return (0);
		if (command_path != NULL)
			free(command_path);
		(path_array)++;
	}
	return (127);
}

void	builtin_redirection(int *fd, int *fd_backup, t_simple command,
	int fd_output)
{
	fd_backup[0] = dup(fd[STDIN]);
	fd_backup[1] = dup(fd[STDOUT]);
	input_redirection(command, TRUE);
	output_redirection(command, fd_output);
}

void	restore_builtin_redirection(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, 0);
	dup2(stdout_backup, 1);
	close(stdin_backup);
	close(stdout_backup);
}

int	its_not_builtin(int *fd_backup)
{
	restore_builtin_redirection(fd_backup[0], fd_backup[1]);
	return (global_exit_status(127));
}

/* If the command is a builtin execute it and return 1,
 * if it's the exit builtin, return 2.
 * Else return 0. */
int	command_is_builtin(t_shell **minishell, t_simple command, int *fd,
	int fd_output)
{
	int		fd_backup[2];

	builtin_redirection(fd, fd_backup, command, fd_output);
	if (ft_strcmp(command.command_and_args[0], "cd") == 0)
		global_exit_status(builtin_cd(*minishell));
	else if (ft_strcmp(command.command_and_args[0], "echo") == 0)
		global_exit_status(builtin_echo(command.command_and_args + 1));
	else if (ft_strcmp(command.command_and_args[0], "exit") == 0)
		builtin_exit(*minishell, command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "pwd") == 0)
		global_exit_status(builtin_pwd(*minishell,
				command.command_and_args[1]));
	else if (ft_strcmp(command.command_and_args[0], "env") == 0)
		global_exit_status(builtin_env((*minishell)->env,
				command.command_and_args[1]));
	else if (ft_strcmp(command.command_and_args[0], "unset") == 0)
		(*minishell)->env = builtin_unset((*minishell)->env,
				command.command_and_args + 1);
	else if (ft_strcmp(command.command_and_args[0], "export") == 0)
		global_exit_status(builtin_export(*minishell,
				command.command_and_args + 1));
	else
		return (its_not_builtin(fd_backup));
	restore_builtin_redirection(fd_backup[0], fd_backup[1]);
	return (0);
}

char	**get_env_array(t_shell *minishell, t_simple command)
{
	char	**env_array;

	env_array = envlist_to_array(minishell->env);
	if (env_array == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command.command_and_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		global_exit_status(127);
		return (NULL);
	}
	return (env_array);
}

char	*get_path_value(t_shell *minishell, t_simple command, char **env_array)
{
	char	*path_value;

	if (env_array == NULL)
		return (NULL);
	path_value = get_env_value("PATH", minishell->env);
	if (path_value == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command.command_and_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		global_exit_status(127);
		free(env_array);
		return (NULL);
	}
	return (path_value);
}

// a verifier : modifier le path dans une commande, puis appeler une commande,
// doit on mettre a jour path_array a chaque tour ?
void	search_exec(t_shell *minishell, t_simple command, int *fd,
	int fd_output)
{
	char	*path_value;
	char	**path_array;
	char	**env_array;

	if (command.command_and_args == NULL)
		return ;
	if (command_is_builtin(&minishell, command, fd, fd_output)
		!= 127)
		return ;
	env_array = get_env_array(minishell, command);
	if (command_in_absolute_path(command, env_array, fd_output) == 0)
	{
		ft_free_array(env_array);
		return ;
	}
	path_value = get_path_value(minishell, command, env_array);
	path_array = ft_split(path_value, ':');
	if (path_array == NULL)
		return ;
	if (try_command_with_path(path_array, command, env_array, fd_output) == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command.command_and_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		global_exit_status(127);
	}
	if (path_array)
		free(path_value);
	ft_free_array(path_array);
	ft_free_array(env_array);
}

/* If only one simple command -> execute,
 * else, create a pipeline */
void	execute(t_shell *minishell, t_command_line *command_line)
{
	int	fd[2];

	fd[STDIN] = STDIN;
	fd[STDOUT] = STDOUT;
	signal_catcher(1);
	if (command_line->number_of_simple_commands == 1)
	{
		search_exec(minishell, command_line->command[0], fd, STDOUT);
	}
	else
	{
		create_pipeline(command_line, minishell, fd);
	}
	signal_catcher(0);
	return ;
}
