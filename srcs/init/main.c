/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:25:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/17 18:37:27 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_new_str_len(char *sep, char **array)
{
	int		str_len;
	int		i;

	str_len = -ft_strlen(sep);
	i = 0;
	while (array[i] != NULL)
		str_len += ft_strlen(array[i++]) + ft_strlen(sep);
	return (str_len);
}

char	*join_array(char **array, char *sep)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	str = ft_calloc(get_new_str_len(sep, array) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (array[i] != NULL)
	{
		while (*array[i] != '\0')
			str[j++] = *(array[i])++;
		if (array[i + 1] == NULL)
			break ;
		k = 0;
		while (sep[k] != '\0')
			str[j++] = sep[k++];
		i++;
	}
	return (str);
}

/* Pour lancer minishell en mode non interactif :
 * ./minishell -c "commande a executer" */

void	non_interactive_mode(char **array, char **env)
{
	t_shell	minishell;

	init_minishell(&minishell, env);
	minishell.command_line.line = join_array(array, " ");
	if (minishell.command_line.line == NULL)
		return ;
	if (parse(&minishell.command_line, &minishell) == -1)
	{
		free_minishell(&minishell);
		return ;
	}
	execute(&minishell, &minishell.command_line);
	free_minishell(&minishell);
	return ;
}

/* En comportement interactif, un prompt est afiche et
 * on peut lancer des commandes */

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;

	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		non_interactive_mode(argv + 2, env);
	else
	{
		init_minishell(&minishell, env);
		while (1)
		{
			signal_catcher(0);
			get_command_line(&minishell, &minishell.command_line);
			if (parse(&minishell.command_line, &minishell) == -1)
			{
				reset_minishell(&minishell.command_line);
				continue ;
			}
			execute(&minishell, &minishell.command_line);
			reset_minishell(&minishell.command_line);
		}
	}
	return (0);
}
