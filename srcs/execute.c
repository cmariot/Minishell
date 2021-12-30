/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/30 16:04:38 by cmariot          ###   ########.fr       */
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

/* For all the possible path of env,
   Put a '/' and the command at the end of the path,
   Check if the command exist and if it can be execute, if ok execute it.
   If it's execute, the child process stops.
   Else try the next path.  */

//erreur a gerer : dossier en tant que commande principale
int	try_command_with_path(char **path_array, t_command_line *command_line,
	int command_index, char **env)
{
	char	*path_with_slash;
	char	*command_path;

	command_path
		= ft_strdup(command_line->command[command_index].command_and_args[0]);
	if (access(command_path, F_OK) == 0)
		if (access(command_path, X_OK) == 0)
			if (!execute_cmnd(&command_path, command_line, command_index, env))
				return (0);
	free(command_path);
	while (*path_array)
	{
		path_with_slash = ft_strjoin(*path_array, "/");
		command_path = ft_strjoin(path_with_slash,
				command_line->command[command_index].command_and_args[0]);
		free(path_with_slash);
		if (access(command_path, F_OK) == 0)
			if (access(command_path, X_OK) == 0)
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
	if (ft_strcmp(command_and_args[0], "pwd") == 0)
		pwd_builtin(minishell);
	else if (ft_strcmp(command_and_args[0], "env") == 0)
		env_builtin(minishell->env);
	else if (ft_strcmp(command_and_args[0], "setenv") == 0)
		setenv_builtin(minishell->env, "PWD", "/test");
	else if (ft_strcmp(command_and_args[0], "unsetenv") == 0)
		unsetenv_builtin(minishell->env, "PWD");
	else if (ft_strcmp(command_and_args[0], "cd") == 0)
		do_cd(minishell);
	else if (ft_strcmp(command_and_args[0], "exit") == 0)
	{
		free_minishell(minishell);
		return (2);
	}
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
	int		builtin_ret;

	builtin_ret = command_is_builtin(minishell, command_line->command[i].command_and_args);
	if (builtin_ret)
	{
		if (builtin_ret == 2)
			exit(EXIT_SUCCESS);
	}
	else
	{
		env_array = envlist_to_array(minishell->env);
		path_value = get_env_value("PATH", minishell->env);
		path_array = ft_split(path_value, ':');
		if (try_command_with_path(path_array, command_line, i, env_array) == 42)
			printf("minishell: %s: command not found\n",
			   	command_line->command[i].command_and_args[0]);
		free(path_value);
		ft_free_array(path_array);
		ft_lstclear_env(&minishell->env, free);
		minishell->env = save_env(env_array);
		ft_free_array(env_array);
	}
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
