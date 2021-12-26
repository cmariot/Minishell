/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/26 16:08:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a new process in which the command is execute,
 * the parent process will wait the child exit to free command_path. */
int	fork_command(char **command_path, t_command_line *command_line,
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
		waitpid(-1, &pid, 0);
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
int	try_command(char **path_array, t_command_line *command_line,
	int command_index, char **env)
{
	char	*path_with_slash;
	char	*command_path;

	command_path
		= ft_strdup(command_line->command[command_index].command_and_args[0]);
	if (access(command_path, F_OK) == 0)
		if (access(command_path, X_OK) == 0)
			if (!fork_command(&command_path, command_line, command_index, env))
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
				if (!fork_command(&command_path, command_line,
						command_index, env))
					return (0);
		free(command_path);
		(path_array)++;
	}
	return (42);
}

// Return the size of the linked list env
int	ft_envlstsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

// Get a char **env copy from the t_env *env linked list
char	**envlist_to_array(t_env *envlist)
{
	char	**env;
	char	*tmp;
	int		len;
	int		i;

	len = ft_envlstsize(envlist);
	if (len == 0)
		return (NULL);
	env = ft_calloc(len, sizeof(char **));
	if (!env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp = ft_strjoin(envlist->name, "=");
		env[i] = ft_strjoin(tmp, envlist->value);
		free(tmp);
		i++;
		envlist = envlist->next;
	}
	return (env);
}

/* Get env as a char **, the line which contains all the path in env,
   (type env in a terminal to see the env array)
   Split this line with the ':' delimiter,
   Try the command in all the possible path. */

// a verifier : modifier le path dans une commande, puis appeler une commande,
// doit on mettre a jour path_array a chaque tour ?
void	execute(t_shell *minishell, t_command_line *command_line)
{
	char	*path_value;
	char	**path_array;
	char	**env;
	char	**env_cpy;
	size_t	i;

	i = 0;
	env = envlist_to_array(minishell->env);
	env_cpy = env;
	path_value = get_env_value("PATH", minishell->env);
	path_array = ft_split(path_value, ':');
	while (i < command_line->number_of_simple_commands)
	{
		if (try_command(path_array, command_line, i, env) == 42)
			printf("minishell: %s: command not found\n",
				command_line->command[i].command_and_args[0]);
		i++;
	}
	free(path_value);
	ft_free_array(path_array);
	ft_free_array(env_cpy);
	return ;
}
