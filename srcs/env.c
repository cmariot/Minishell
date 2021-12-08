/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:04:13 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/08 15:13:36 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **array)
{
	char	**new;
	int		i;
	int		len;

	new = NULL;
	i = 0;
	len = 0;
	while (array[i++] != NULL)
		len++;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	printf("len = %d\n", len);
	return (new);
}
