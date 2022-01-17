/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:37:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 23:34:18 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tester.h"

int	fork_command(char *command, char **command_and_args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
		return (-1);
	}
	else if (pid == 0)
	{
		status = execve(command, command_and_args, env);
		ft_putstr_fd("Command execution error\n", 2);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status));
		return (-1);
	}
}

int	fork_redirection(int fd_new_file, char *command_path,
	char **command_and_args, char **env)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
		return (-1);
	}
	else if (pid == 0)
	{
		dup2(fd_new_file, 1);
		exit_status = fork_command(command_path, command_and_args, env);
		printf("exit status = %d", exit_status);
		usleep(10000);
		if (command_and_args[2])
			free(command_and_args[2]);
		exit(1);
	}
	else
	{
		waitpid(pid, &pid, 0);
		usleep(10000);
		return (0);
	}
}

int	print_final_result(int numero_du_test, int result, int file_descriptor)
{
	printf("\nRESULTAT : %d/%d OK\n\n", numero_du_test - result,
		numero_du_test);
	close(file_descriptor);
	return (0);
}

void	test(int numero_du_test, char **test_line, char **env, int *result)
{
	char	*file_bash;
	char	*file_minishell;

	printf("\n---------------------------------------\n\n");
	printf("test_%d : [%s]\n", numero_du_test, *test_line);
	file_bash = execute_with_bash(*test_line, numero_du_test, env);
	file_minishell = execute_with_minishell(*test_line,
			numero_du_test, env);
	*result += check_diff(file_bash, file_minishell);
	free(file_bash);
	free(file_minishell);
	free(*test_line);
}

int	main(int argc, char **argv, char **env)
{
	int		file_descriptor;
	char	*test_line;
	int		numero_du_test;
	int		result;

	if (!argc || !argv)
		return (1);
	file_descriptor = open("liste_tests.txt", O_RDONLY);
	if (file_descriptor == -1)
		return (printf("Erreur d'ouverture du fichier liste_tests.txt\n"));
	numero_du_test = 0;
	result = 0;
	while (numero_du_test++ >= 0)
	{
		test_line = gnl_without_bn(file_descriptor);
		if (test_line == NULL)
			return (print_final_result(numero_du_test,
					result, file_descriptor));
		if (test_line[0] == '#')
			printf("\n\n🤖 %s\n", test_line + 1);
		else
			test(numero_du_test, &test_line, env, &result);
	}
	return (1);
}
