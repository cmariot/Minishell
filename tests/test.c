/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 00:31:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 00:39:14 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	size_t	i;
	char	**array;

	if (argc && *argv && *env)
	{
		i = 0;
		array = malloc(10 * sizeof(char *));
		printf("%lu\n", sizeof(char **));
	}
	return (0);
}
