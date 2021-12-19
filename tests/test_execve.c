/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:31:23 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/16 14:37:56 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

//cat-e test1.txt 
int	main(int argc, char **argv, char **env)
{
	char	*path;
	char	*args[5];
	int		ret;

	if (argc && argv)
	{
		path = "/bin/echo";
		args[0] = "-e";
		args[1] = " ";
		args[2] = "test1.txt";
		args[3] = " ";
		args[4] = NULL;
		ret = execve(path, args, env);
		printf("Retour execve = %d\n", ret);
	}
	return (0);
}
