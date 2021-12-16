/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:31:23 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 11:33:33 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*path;
	char	*args[3];
	int		ret;

	if (argc && argv)
	{
		path = "/bin/cat";
		args[0] = "-e";
		args[1] = "test1.txt test2.txt";
		args[2] = NULL;
		ret = execve(path, args, env);
		printf("Retour execve = %d\n", ret);
	}
	return (0);
}
