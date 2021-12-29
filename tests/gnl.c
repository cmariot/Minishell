/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:19:44 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 13:20:29 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv, char **env)
{
	int		fd;
	char	*line;

	if (argc && *argv && *env)
	{
		fd = open(argv[1], O_RDONLY);
		while (1)
		{
			line = gnl_without_bn(fd);
			if (!line)
				break ;
			printf("LINE = [%s]\n", line);
			free(line);
		}
		close(fd);
	}
	return (0);
}
