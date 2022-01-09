/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:37:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/08 18:42:14 by cmariot          ###   ########.fr       */
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

char	*execute_with_bash(char *commande, int number, char **env)
{
	char	*new_file;
	char	*tmp;
	int		fd_new_file;
	char	*command_and_args[4];

	tmp = ft_itoa(number);
	new_file = ft_strjoin("log_tests/test_", tmp);
	free(tmp);
	tmp = ft_strjoin(new_file, "_bash");
	free(new_file);
	new_file = tmp;
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
	new_file = ft_strjoin("log_tests/test_", tmp);
	free(tmp);
	tmp = ft_strjoin(new_file, "_minishell");
	free(new_file);
	new_file = tmp;
	fd_new_file = open(new_file, O_RDWR | O_CREAT, 0644);
	command_and_args[0] = "../minishell";
	command_and_args[1] = "-c";
	command_and_args[2] = commande;
	command_and_args[3] = NULL;
	fork_redirection(fd_new_file, "../minishell", command_and_args, env);
	close(fd_new_file);
	return (new_file);
}

char	*file_to_str(char *file)
{
	int		file_descriptor;
	int		read_return;
	char	buf[255];
	char	*str;
	char	*tmp;

	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor == -1)
	{
		ft_putstr_fd("Erreur, ouverture de fichier\n", 2);
		return (NULL);
	}
	str = NULL;
	while (1)
	{
		read_return = read(file_descriptor, buf, 255);
		if (read_return == -1)
		{
			ft_putstr_fd("Erreur, lecture de fichier\n", 2);
			return (NULL);
		}
		buf[read_return] = '\0';
		if (str == NULL)
			str = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(str, buf);
			free(str);
			str = tmp;
		}
		if (read_return == 0)
			break ;
	}
	close(file_descriptor);
	return (str);
}

int	check_diff(char *file_bash, char *file_minishell)
{
	char	*bash_output;
	char	*minishell_output;

	bash_output = file_to_str(file_bash);
	unlink(file_bash);

	minishell_output = file_to_str(file_minishell);
	unlink(file_minishell);
	if (ft_strcmp(bash_output, minishell_output) == 0)
	{
		printf("✅ OK\n");
		free(bash_output);
		free(minishell_output);
		return (0);
	}
	else
	{
		//Pour l'affichage des caracteres des output
		/*size_t i = 0;
		while (bash_output[i] != '\0' || minishell_output[i] != '\0')
		{
			if (bash_output[i] != '\0')
				printf("bash_output[%lu] = \t[%c]=[%d]\n", i, bash_output[i], bash_output[i]);
			if (minishell_output[i] != '\0')
				printf("minishell_output[%lu] = \t[%c]=[%d]\n\n", i, minishell_output[i], minishell_output[i]);
			i++;
		}*/
		printf("\n❌ KO\n\n");
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
				printf("\nRESULTAT : %d/%d OK\n\n", numero_du_test - result, numero_du_test);
				close(file_descriptor);
				return (0);
			}
			if (test_line[0] == '#')
				printf("\n\n🤖 %s\n", test_line + 1);
			else
			{
				printf("\n---------------------------------------\n\n");
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
