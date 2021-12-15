/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:31:23 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 14:19:11 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv, char **env)
{
	char	*path;
	char	*args[2];

	if (argc && argv)
	{
		path = "/usr/bin/ls";
		args[0] = "-l";
		args[1] = NULL;
		execve(path, args, env);
	}
	return (0);
}
