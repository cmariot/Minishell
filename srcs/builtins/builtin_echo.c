/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:35:53 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/18 14:02:30 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arraylen(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}

bool	check_n_option(char *str_option, bool *n_option)
{
	size_t	i;

	i = 0;
	if (str_option[i] != '-')
		return (FALSE);
	i++;
	if (str_option[i] != 'n')
		return (FALSE);
	while (str_option[i])
	{
		if (str_option[i] != 'n')
			return (FALSE);
		i++;
	}
	*n_option = TRUE;
	return (TRUE);
}

int	print_backslash_n(void)
{
	ft_putchar('\n');
	return (0);
}

int	builtin_echo(char **command_and_args)
{
	size_t	i;
	bool	n_option;
	size_t	last_index;

	if (*command_and_args == NULL)
		return (global_exit_status(print_backslash_n()));
	n_option = FALSE;
	while (*command_and_args != NULL
		&& check_n_option(*command_and_args, &n_option) == TRUE)
		command_and_args++;
	last_index = ft_arraylen(command_and_args) - 1;
	i = 0;
	while (command_and_args[i] != NULL)
	{
		if (!(command_and_args[i][0] == 32 && command_and_args[i][1] == '\0'))
			ft_putstr(command_and_args[i]);
		if (i != last_index)
			ft_putchar(32);
		i++;
	}
	if (n_option == FALSE)
		ft_putchar('\n');
	return (global_exit_status(0));
}
