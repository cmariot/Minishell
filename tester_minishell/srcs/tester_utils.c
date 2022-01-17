/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:28:41 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 23:33:04 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tester.h"

char	*add_buf_to_str(char **str, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(*str, buf);
	free(*str);
	return (tmp);
}

char	*file_to_str(char *file)
{
	int		file_descriptor;
	int		read_return;
	char	buf[10000];
	char	*str;

	file_descriptor = open(file, O_RDONLY);
	if (file_descriptor == -1)
		ft_putstr_fd("Error, open failed.\n", 2);
	str = NULL;
	read_return = 1;
	while (read_return)
	{
		read_return = read(file_descriptor, buf, 10000);
		if (read_return == -1)
			return (NULL);
		buf[read_return] = '\0';
		if (str == NULL)
			str = ft_strdup(buf);
		else
			str = add_buf_to_str(&str, buf);
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
		printf("\n❌ KO\n\n");
		printf("bash_output =\n[%s]\n", bash_output);
		printf("\nminishell_output =\n[%s]\n\n", minishell_output);
		free(bash_output);
		free(minishell_output);
		return (1);
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
	fd_new_file = open(new_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	fd_new_file = open(new_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	command_and_args[0] = "../minishell";
	command_and_args[1] = "-c";
	command_and_args[2] = commande;
	command_and_args[3] = NULL;
	fork_redirection(fd_new_file, "../minishell", command_and_args, env);
	close(fd_new_file);
	return (new_file);
}
