/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:22:23 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/21 20:11:10 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///* Create a new process in which the command is execute,
// * the parent process will wait the child exit to free command_path. */
//int	fork_command(char **command_path, char **command_array, char **env)
//{
//	pid_t	pid;
//
//	pid = fork();
//	if (pid == -1)
//	{
//		ft_putstr_fd("Error, during fork in try_command()\n", 2);
//		return (-1);
//	}
//	else if (pid == 0)
//	{
//		execve(*command_path, command_array, env);
//		ft_putstr_fd("Command execution error\n", 2);
//		exit(-1);
//	}
//	else
//	{
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
//int	try_command(char **path_array, char **command_array, char **env)
//{
//	char	*path_with_slash;
//	char	*command_path;
//	int		i;
//
//	command_path = ft_strdup(command_array[0]);
//	if (access(command_path, F_OK) == 0)
//		if (access(command_path, X_OK) == 0)
//			if (fork_command(&command_path, command_array, env) == 0)
//				return (0);
//	free(command_path);
//	i = 0;
//	while (path_array[i])
//	{
//		path_with_slash = ft_strjoin(path_array[i], "/");
//		command_path = ft_strjoin(path_with_slash, command_array[0]);
//		free(path_with_slash);
//		if (access(command_path, F_OK) == 0)
//			if (access(command_path, X_OK) == 0)
//				if (fork_command(&command_path, command_array, env) == 0)
//					return (0);
//		free(command_path);
//		i++;
//	}
//	return (42);
//}
//
///* In the env array, check if the line begins by "PATH=",
//   if a line is found, get the line without it's 5 first characters.
//   Else, error. */
//char	*get_path_line_in_env(char **env)
//{
//	char	*path_line;
//	int		i;
//
//	i = 0;
//	path_line = NULL;
//	while (env[i])
//	{
//		if (ft_memcmp(env[i], "PATH=", 5) == 0)
//		{
//			path_line = ft_strdup(env[i] + 5);
//			break ;
//		}
//		i++;
//	}
//	if (path_line == NULL)
//	{
//		ft_putstr_fd("Path line not found in env\n", 2);
//		return (NULL);
//	}
//	return (path_line);
//}
//
//void	print_cmd_error(char **command_array)
//{
//	ft_putstr_fd("Error, command not found : ", 2);
//	ft_putstr_fd(command_array[0], 2);
//	ft_putstr_fd("\n", 2);
//}
//
///* Get the line which contains all the path in env,
//   (type env in a terminal to see the env array)
//   Split this line with the ':' delimiter,
//   Split the command with the ' ' dilimiter,
//   Try the command in all the possible path. */
//int	execute_cmd(char **command_array, char **env)
//{
//	int		ret;
//	char	*path_line;
//	char	**path_array;
//
//	path_line = get_path_line_in_env(env);
//	if (path_line == NULL)
//		return (-1);
//	path_array = ft_split(path_line, ':');
//	free(path_line);
//	if (path_array == NULL)
//		return (-1);
//	ret = try_command(path_array, command_array, env);
//	if (ret == 42)
//		print_cmd_error(command_array);
//	ft_free_array(path_array);
//	ft_free_array(command_array);
//	return (ret);
//}
//
//void	error(int error_number)
//{
//	if (error_number == 1)
//	{
//		ft_putstr_fd("Error, in the bonus pipe process\n", 2);
//		exit(EXIT_FAILURE);
//	}
//	else if (error_number == 2)
//	{
//		ft_putstr_fd("Error, in the bonus fork process\n", 2);
//		exit(EXIT_FAILURE);
//	}
//	else if (error_number == 3)
//	{
//		ft_putstr_fd("Error, the file1 does not exist.\n", 2);
//		exit(EXIT_FAILURE);
//	}
//	else
//		exit(EXIT_FAILURE);
//}
//
//void	execute_pipelines(char **cmd_array, char **env)
//{
//	pid_t	pid;
//	int		fd[2];
//	int		status;
//
//	if (pipe(fd) == -1)
//		error(1);
//	pid = fork();
//	if (pid == -1)
//		error(2);
//	else if (pid == 0)
//	{
//		close(fd[0]);
//		dup2(fd[1], STDOUT);
//		execute_cmd(cmd_array, env);
//		exit(EXIT_SUCCESS);
//	}
//	else
//	{
//		waitpid(pid, &status, 0);
//		close(fd[1]);
//		dup2(fd[0], STDIN);
//	}
//}
