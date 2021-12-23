/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:42:55 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/23 17:24:25 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///* Create a new process in which the command is execute,
// * the parent process will wait the child exit to free command_path. */
//int	fork_command(char **command_path, t_command_line *command_line, char **env)
//{
//	pid_t	pid;
//
//	pid = fork();
//	if (pid == -1)
//	{
//		ft_putstr_fd("Error, fork failed\n", 2);
//		return (-1);
//	}
//	else if (pid == 0)
//	{
//		execve(*command_path, command_line->main.args, env);
//		ft_putstr_fd("Command execution error\n", 2);
//		exit(-1);
//	}
//	else
//	{
//		waitpid(-1, &pid, 0);
//		if (*command_path != NULL)
//			free(*command_path);
//		return (0);
//	}
//}
//
///* For all the possible path of env,
//   Put a '/' and the command at the end of the path,
//   Check if the command exist and if it can be execute, if ok execute it.
//   If it's execute, the child process stops.
//   Else try the next path.  */
//
////erreur a gerer : dossier en tant que commande principale
//int	try_command(char **path_array, t_command_line *command_line, char **env)
//{
//	char	*path_with_slash;
//	char	*command_path;
//	int		i;
//
//	command_path = ft_strdup(command_line->main.command);
//	if (access(command_path, F_OK) == 0)
//		if (access(command_path, X_OK) == 0)
//			if (fork_command(&command_path, command_line, env) == 0)
//				return (0);
//	free(command_path);
//	i = 0;
//	while (path_array[i])
//	{
//		path_with_slash = ft_strjoin(path_array[i], "/");
//		command_path = ft_strjoin(path_with_slash, command_line->main.command);
//		free(path_with_slash);
//		if (access(command_path, F_OK) == 0)
//			if (access(command_path, X_OK) == 0)
//				if (fork_command(&command_path, command_line, env) == 0)
//					return (0);
//		free(command_path);
//		i++;
//	}
//	return (42);
//}
//
//// Return the size of the linked list env
//int	ft_envlstsize(t_env *env)
//{
//	int	size;
//
//	size = 0;
//	while (env)
//	{
//		env = env->next;
//		size++;
//	}
//	return (size);
//}
//
//// Get a char **env copy from the t_env *env linked list
//char	**envlist_to_array(t_env *envlist)
//{
//	char	**env;
//	char	*tmp;
//	int		len;
//	int		i;
//
//	len = ft_envlstsize(envlist);
//	env = ft_calloc(len + 1, sizeof(char **));
//	if (!env)
//		return (NULL);
//	i = 0;
//	while (envlist)
//	{
//		tmp = ft_strjoin(envlist->name, "=");
//		env[i] = ft_strjoin(tmp, envlist->value);
//		free(tmp);
//		envlist = envlist->next;
//		i++;
//	}
//	return (env);
//}
//
///* Get env as a char **, the line which contains all the path in env,
//   (type env in a terminal to see the env array)
//   Split this line with the ':' delimiter,
//   Try the command in all the possible path. */
//void	execute(t_shell *minishell, t_command_line *command_line)
//{
//	char	**env;
//	char	*path_value;
//	char	**path_array;
//
//	env = envlist_to_array(minishell->env);
//	path_value = get_env_value("PATH", minishell->env);
//	path_array = ft_split(path_value, ':');
//	if (try_command(path_array, command_line, env) == 42)
//		printf("minishell: %s: command not found\n", command_line->main.command);
//	ft_free_array(env);
//	free(path_value);
//	ft_free_array(path_array);
//	return ;
//}
