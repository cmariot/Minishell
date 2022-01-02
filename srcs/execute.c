/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/02 18:00:17 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */
int	execute_cmnd(char **command_path, t_command_line *command_line,
		size_t command_index, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
		return (-1);
	}
	else if (pid == 0)
	{
		execve(*command_path,
			command_line->command[command_index].command_and_args, env);
		ft_putstr_fd("Command execution error\n", 2);
		exit(-1);
	}
	else
	{
		waitpid(pid, &pid, 0);
		if (*command_path != NULL)
			free(*command_path);
		return (0);
	}
}

int	command_in_absolute_path(t_command_line *command_line, size_t command_index,
		char **env)
{
	char	*command_path;
	size_t	len;

	command_path
		= ft_strdup(command_line->command[command_index].command_and_args[0]);
	if (ft_strlen(command_path) > 2 && command_path[0] == '.'
		&& command_path[1] == '/')
	{
		if (access(command_path + 2, F_OK) == 0
			&& access(command_path + 2, X_OK) == 0)
			if (ft_isadirectory(command_path + 2) == FALSE)
				if (!execute_cmnd(&command_path, command_line,
						command_index, env))
					return (0);
	}
	else
	{
		//verifier cette partie pas sur que bash fonctionne reellement comme ca
		len = 0;
		while (command_path[len] != '/' && command_path[len])
			len++;
		if (len == ft_strlen(command_path))
			return (1);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
			if (ft_isadirectory(command_path) == FALSE)
				if (!execute_cmnd(&command_path, command_line,
						command_index, env))
					return (0);
	}
	if (command_path != NULL)
		free(command_path);
	return (1);
}

/* For all the possible path of env,
   Put a '/' and the command at the end of the path,
   Check if the command exist and if it can be execute, if ok execute it.
   If it's execute, the child process stops.
   Else try the next path.  */

int	try_command_with_path(char **path_array, t_command_line *command_line,
	int command_index, char **env)
{
	char	*path_with_slash;
	char	*command_path;

	if (command_in_absolute_path(command_line, command_index, env) == 0)
		return (0);
	while (*path_array)
	{
		path_with_slash = ft_strjoin(*path_array, "/");
		command_path = ft_strjoin(path_with_slash,
				command_line->command[command_index].command_and_args[0]);
		free(path_with_slash);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
			if (ft_isadirectory(command_path) == FALSE)
				if (!execute_cmnd(&command_path, command_line,
						command_index, env))
					return (0);
		free(command_path);
		(path_array)++;
	}
	return (42);
}

/* If the command is a builtin execute it and return 1,
 * if it's the exit builtin, return 2.
 * Else return 0. */
int	command_is_builtin(t_shell *minishell, char **command_and_args)
{
	if (ft_strcmp(command_and_args[0], "cd") == 0)
		do_cd(minishell);
	else if (ft_strcmp(command_and_args[0], "echo") == 0)
		builtin_echo(command_and_args + 1);
	else if (ft_strcmp(command_and_args[0], "exit") == 0)
	{
		free_minishell(minishell);
		exit(EXIT_SUCCESS);
	}
	else if (ft_strcmp(command_and_args[0], "pwd") == 0)
		pwd_builtin(minishell);
	else if (ft_strcmp(command_and_args[0], "env") == 0)
		env_builtin(minishell->env);
	else if (ft_strcmp(command_and_args[0], "unset") == 0)
		minishell->env = unset_builtin(minishell->env, command_and_args + 1);
	else if (ft_strcmp(command_and_args[0], "export") == 0)
		export_builtin(minishell->env, command_and_args + 1);
	else
		return (0);
	return (1);
}

// a verifier : modifier le path dans une commande, puis appeler une commande,
// doit on mettre a jour path_array a chaque tour ?
void	search_exec(t_shell *minishell, t_command_line *command_line, size_t i)
{
	char	*path_value;
	char	**path_array;
	char	**env_array;

	if (command_line->command[i].command_and_args == NULL)
		return ;
	if (command_is_builtin(minishell,
			command_line->command[i].command_and_args))
		return ;
	env_array = envlist_to_array(minishell->env);
	path_value = get_env_value("PATH", minishell->env);
	path_array = ft_split(path_value, ':');
	if (try_command_with_path(path_array, command_line, i, env_array) == 42)
		printf("minishell: %s: command not found\n",
			command_line->command[i].command_and_args[0]);
	if (path_value)
		free(path_value);
	ft_free_array(path_array);
	ft_free_array(env_array);
}

/* If only one simple command -> execute,
 * else, create a pipeline */
void	execute(t_shell *minishell, t_command_line *command_line)
{
	if (command_line->number_of_simple_commands == 1)
		search_exec(minishell, command_line, 0);
	else
		create_pipeline(command_line, minishell);
	return ;
}
