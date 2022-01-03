/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:37:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/03 14:50:24 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tester.h"

int	fork_command(char *command, char **command_and_args, char **env)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error, fork failed\n", 2);
		return (-1);
	}
	else if (pid == 0)
	{
		execve(command, command_and_args, env);
		ft_putstr_fd("Command execution error\n", 2);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		usleep(10000);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
		else
			return (0);
	}
}

int	fork_redirection(int fd_new_file, char *command_path, char **command_and_args, char **env)
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
		exit(1);
	}
	else
	{
		waitpid(pid, &pid, 0);
		return (0);
	}
}

char	*execute_with_bash(char *commande, int number, char **env)
{
	char	*new_file;
	char	*tmp;
	int		fd_new_file;
	char	*command_and_args[4];

	tmp = ft_itoa(number);
	new_file = ft_strjoin(".test_bash_", tmp);
	free(tmp);
	fd_new_file = open(new_file, O_RDWR | O_CREAT, 0644);
	command_and_args[0] = "/bin/bash";
	command_and_args[1] = "-c";
	command_and_args[2] = commande;
	command_and_args[3] = NULL;
	fork_redirection(fd_new_file, "/bin/bash", command_and_args, env);
	close(fd_new_file);
	return (new_file);
}

char	*execute_with_minishell(char *commande, int number, char **env)
{
	char	*new_file;
	char	*tmp;
	int		fd_new_file;
	char	*command_and_args[4];

	tmp = ft_itoa(number);
	new_file = ft_strjoin(".test_minishell_", tmp);
	free(tmp);
	fd_new_file = open(new_file, O_RDWR | O_CREAT, 0644);
	command_and_args[0] = "../minishell";
	command_and_args[1] = "-c";
	command_and_args[2] = commande;
	command_and_args[3] = NULL;
	fork_redirection(fd_new_file, "../minishell", command_and_args, env);
	close(fd_new_file);
	return (new_file);
}

int	check_diff(char *file_bash, char *file_minishell)
{
	char	buf1[255];
	char	buf2[255];
	int		read_return;
	int		fd_bash;
	char	*bash_output;
	int		fd_minishell;
	char	*minishell_output;

	fd_bash = open(file_bash, O_RDONLY);
	read_return = read(fd_bash, buf1, 255);
	buf1[read_return] = '\0';
	bash_output = ft_strdup(buf1);
	close(fd_bash);
	unlink(file_bash);

	fd_minishell = open(file_minishell, O_RDONLY);
	read_return = read(fd_minishell, buf2, 255);
	buf2[read_return] = '\0';
	minishell_output = ft_strdup(buf2);
	close(fd_minishell);
	unlink(file_minishell);
	if (ft_strcmp(bash_output, minishell_output) == 0)
	{
		printf("OK\n");
		free(bash_output);
		free(minishell_output);
		return (0);
	}
	else
	{
		printf("\nKO\n\n");
		printf("bash_output =\n[%s]\n", bash_output);
		printf("\nminishell_output =\n[%s]\n\n", minishell_output);
		free(bash_output);
		free(minishell_output);
		return (1);
	}
}

/*
 * testeur pour minishell, va lire chaque ligne du fichier 'liste_tests.txt'
 * et execute la commande avec bash puis avec minishell, le resultat est stocké
 * dans un fichier et les fichiers sont comparés.
 * ce testeur fonctionne seulement pour les commandes affichant quelque chose sur la sortie standard.
 * Pour le lancer : make test */

int	main(int argc, char **argv, char **env)
{
	int		numero_du_test;
	int		file_descriptor;
	char	*test_line;
	char	*file_bash;
	char	*file_minishell;
	int		result;

	if (argc && argv)
	{
		file_descriptor = open("liste_tests.txt", O_RDONLY);
		if (file_descriptor == -1)
			printf("Erreur d'ouverture du fichier liste_tests.txt\n");
		numero_du_test = 0;
		result = 0;
		while (1)
		{
			test_line = gnl_without_bn(file_descriptor);
			if (test_line == NULL)
			{
				printf("RESULTAT : %d/%d OK\n", numero_du_test - result, numero_du_test);
				close(file_descriptor);
				return (0);
			}
			if (test_line[0] == '#')
				printf("%s\n", test_line + 1);
			else
			{
				printf("---------------------------------------\n");
				printf("test_%d : [%s]\n", numero_du_test, test_line);
				file_bash = execute_with_bash(test_line, numero_du_test, env);
				file_minishell = execute_with_minishell(test_line, numero_du_test, env);
				result += check_diff(file_bash, file_minishell);
				free(file_bash);
				free(file_minishell);
				free(test_line);
				numero_du_test++;
			}
		}
		free(file_bash);
		free(file_minishell);
		free(test_line);
		close(file_descriptor);
	}
	return (0);
}
