/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:50:23 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/23 18:50:28 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	return_global_exit_status(void)
{
	return (g_exit_status);
}

int	global_exit_status(int new_value)
{
	g_exit_status = new_value;
	return (return_global_exit_status());
}

int	expand_exit_status(char **str, size_t *i)
{
	int		exit_status;
	char	*value;

	exit_status = return_global_exit_status();
	value = ft_itoa(exit_status);
	if (ft_strlen(*str) - 1 == 1)
	{
		free(*str);
		*str = ft_strdup(value);
	}
	else
		add_value_to_str(str, "?", value, i);
	free(value);
	return (0);
}
